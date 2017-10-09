#include "FontHandler.h"
#include "GUIRenderer.h"

using namespace ENGINE::GUI;

std::vector<FontHandler*> FontHandler::fonts = std::vector<FontHandler*>();

float getXOpenGL(float pixelValue)
{
	return ((float)pixelValue / 800.0f) * 2.0f - 1.0f;		//TODO replace by display.width
}

float getYOpenGL(float pixelValue)
{
	return -1.0f*((float)pixelValue / 600.0f) * 2.0f + 1.0f;	//TODO replace by display.height
}






FontHandler::Character::Character(int id, float xTextureCoord, float yTextureCoord, float xOffset, float yOffset, float sizeX, float sizeY, float xAdvance)
{
	this->id = id;
	this->xTextureCoord = xTextureCoord;
	this->yTextureCoord = yTextureCoord;
	this->xOffset = xOffset;
	this->yOffset = yOffset;
	this->sizeX = sizeX;
	this->sizeY = sizeY;
	this->xAdvance = xAdvance;
}

void FontHandler::RenderAllFonts()
{
	for (FontHandler* var : FontHandler::fonts)
	{
		var->Render();
	}
}

FontHandler::FontHandler(const std::string pathToFontFiles, const std::string shaderPath)
{
	//load font information
	//load fnt file with character info
	std::ifstream fin(pathToFontFiles + ".fnt");//"./res/Fonts/Candara.fnt");
	std::string str;
	while (std::getline(fin, str))
	{
		std::vector<std::string> part = ENGINE::UTIL::splitString(str, ' ');
		if (part.size() >= 1) {
			if (part[0].compare("char") == 0) {

				std::vector<std::string> equalsStr = ENGINE::UTIL::splitString(part[1], '=');
				int id = std::stoi(equalsStr[1]);

				//get next value
				int i = 2;
				while (!part[i].compare(""))
				{
					i++;
				}
				equalsStr = ENGINE::UTIL::splitString(part[i], '=');
				double x = std::stod(equalsStr[1]);

				i++;
				//get next value
				while (!part[i].compare(""))
				{
					i++;
				}
				equalsStr = ENGINE::UTIL::splitString(part[i], '=');
				double y = std::stod(equalsStr[1]);

				i++;
				//get next value
				while (!part[i].compare(""))
				{
					i++;
				}
				equalsStr = ENGINE::UTIL::splitString(part[i], '=');
				double width = std::stod(equalsStr[1]);

				i++;
				//get next value
				while (!part[i].compare(""))
				{
					i++;
				}
				equalsStr = ENGINE::UTIL::splitString(part[i], '=');
				double height = std::stod(equalsStr[1]);

				i++;
				//get next value
				while (!part[i].compare(""))
				{
					i++;
				}
				equalsStr = ENGINE::UTIL::splitString(part[i], '=');
				double xOffset = std::stod(equalsStr[1]);

				i++;
				//get next value
				while (!part[i].compare(""))
				{
					i++;
				}
				equalsStr = ENGINE::UTIL::splitString(part[i], '=');
				double yOffset = std::stod(equalsStr[1]);

				i++;
				//get next value
				while (!part[i].compare(""))
				{
					i++;
				}
				equalsStr = ENGINE::UTIL::splitString(part[i], '=');
				double xAdvance = std::stod(equalsStr[1]);

				characters[id] = new Character(id, (float)x, (float)y, (float)xOffset, (float)yOffset, (float)width, (float)height, (float)xAdvance);

			}
		}


	}

	texture = new Texture(pathToFontFiles + ".png");

	shader = new Shader(shaderPath);
}

FontHandler::~FontHandler()
{
	auto iterator = std::remove(FontHandler::fonts.begin(), FontHandler::fonts.end(), this);
	int index = std::distance(FontHandler::fonts.begin(), iterator);
	FontHandler::fonts.erase(iterator, FontHandler::fonts.end());

	for (unsigned int i = 0; i < texts.size(); i++)
	{
		delete texts[i];
	}

	//delete old buffer
	if (vbo != 0)
		glDeleteBuffers(1, &vbo);
	if (vao != 0)
		glDeleteVertexArrays(1, &vao);
}

FontHandler * FontHandler::GetFontHandler(const std::string pathToFontFiles, const std::string shaderPath)
{
	FontHandler * font = new FontHandler(pathToFontFiles, shaderPath);
	fonts.push_back(font);
	return font;
}

Text * FontHandler::AddText(std::string str)
{
	Text* txt = new Text(str,this);
	InsertText(txt);
	return txt;
}

Text * FontHandler::AddText(std::string str, float depth)
{
	Text* txt = new Text(str, this);
	txt->SetDepth(depth);
	InsertText(txt);
	return txt;
}

void FontHandler::InsertText(Text *txt)
{
	rebuild = true;
	if (texts.size() == 0) {
		texts.push_back(txt);
		return;
	}
	unsigned int index;
	for (index = 0; index < texts.size(); index++)
	{
		if (txt < texts[index])
		{
			texts.insert(texts.begin() + index, txt);
			break;
		}
	}

}

void FontHandler::Render()
{
	if (texts.size() == 0) {
		return;
	}

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	if (rebuild) {
		std::sort(texts.begin(), texts.end());
		vertexData.clear();
		totalCharNumber = 0;
		for (Text* txt : texts)
		{
			AddQuadsForText(txt);
		}

		//repush everything
		//delete old buffer
		if (vbo != 0)
			glDeleteBuffers(1, &vbo);
		if (vao != 0)
			glDeleteVertexArrays(1, &vao);

		//make quadbuffer
		// make and bind the VAO
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		// make and bind the VBO
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);

		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * totalCharNumber * 30, &vertexData.front(), GL_STATIC_DRAW);


		// connect the xyz to the "vert" attribute of the vertex shader
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);

		// connect the uv coords to the "vertTexCoord" attribute of the vertex shader
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(sizeof(float) * 3));

		// unbind the VAO
		glBindVertexArray(0);

	}

	//bind shader and texture
	Bind(shader);
	Bind(texture);
	glUniform1i(shader->getUniform("tex"), 0);

	// bind the VAO (the triangle)
	glBindVertexArray(vao);

	// draw the VAO
	glDrawArrays(GL_TRIANGLES, 0, 6 * totalCharNumber);

	glBindVertexArray(0);

	rebuild = false;

}

void FontHandler::AddQuadsForText(Text* txt) {
	txt->rect->toPixels();

	assert(characters[65] != 0);//this is a not valid font because there is no letter for 'A'

	float scaler = float((double)txt->textHeightInPixel / (characters[65]->getsizeY() + 2 * characters[103]->getyOffset()));

	float virtualCursorInPixel = txt->rect->x;
	Character *curChar;

	//TODO: load real texture size
	float globalTextureSizeX = 512;
	float globalTextureSizeY = 512;



	float zHeight = 0.0;

	int lengthCounter = 0;
	for (unsigned int i = 0; i < txt->text.size(); i++)
	{
		txt->rect->toPixels();

		lengthCounter++;
		curChar = characters[(int)txt->text[i]];
		//add coords for vertecies 
		//oben links
		{
			vertexData.push_back(getXOpenGL(virtualCursorInPixel + scaler * curChar->getxOffset()));
			vertexData.push_back(getYOpenGL(txt->rect->y + scaler*curChar->getyOffset() + scaler*curChar->getsizeY()));
			vertexData.push_back(zHeight);
			//oben links
			vertexData.push_back((curChar->getxTextureCoord()) / globalTextureSizeX);
			vertexData.push_back((curChar->getsizeY() + curChar->getyTextureCoord()) / globalTextureSizeY);
		}

		//unten links
		{
			vertexData.push_back(getXOpenGL(virtualCursorInPixel + scaler * (float)curChar->getxOffset()));
			vertexData.push_back(getYOpenGL(txt->rect->y + scaler * (float)curChar->getyOffset()));
			vertexData.push_back(zHeight);
			//unten links
			vertexData.push_back(((float)curChar->getxTextureCoord()) / globalTextureSizeX);
			vertexData.push_back(((float)curChar->getyTextureCoord()) / globalTextureSizeY);
		}

		//unten rechts
		{
			vertexData.push_back(getXOpenGL(virtualCursorInPixel + scaler * (curChar->getxOffset() + curChar->getsizeX())));
			vertexData.push_back(getYOpenGL(txt->rect->y + scaler*curChar->getyOffset()));
			vertexData.push_back(zHeight);
			//unten rechts
			vertexData.push_back((curChar->getsizeX() + curChar->getxTextureCoord()) / globalTextureSizeX);
			vertexData.push_back((curChar->getyTextureCoord()) / globalTextureSizeY);
		}

		//oben links
		{
			vertexData.push_back(getXOpenGL(virtualCursorInPixel + scaler * curChar->getxOffset()));
			vertexData.push_back(getYOpenGL(txt->rect->y + scaler*curChar->getyOffset() + scaler*curChar->getsizeY()));
			vertexData.push_back(zHeight);
			//oben links
			vertexData.push_back((curChar->getxTextureCoord()) / globalTextureSizeX);
			vertexData.push_back((curChar->getsizeY() + curChar->getyTextureCoord()) / globalTextureSizeY);
		}

		//oben rechts
		{
			vertexData.push_back(getXOpenGL(virtualCursorInPixel + scaler * (curChar->getxOffset() + curChar->getsizeX())));
			vertexData.push_back(getYOpenGL(txt->rect->y + scaler*curChar->getyOffset() + scaler*curChar->getsizeY()));
			vertexData.push_back(zHeight);
			//oben rechts
			vertexData.push_back((curChar->getsizeX() + curChar->getxTextureCoord()) / globalTextureSizeX);
			vertexData.push_back((curChar->getsizeY() + curChar->getyTextureCoord()) / globalTextureSizeY);
		}

		//unten rechts
		{
			vertexData.push_back(getXOpenGL(virtualCursorInPixel + scaler * (curChar->getxOffset() + curChar->getsizeX())));
			vertexData.push_back(getYOpenGL(txt->rect->y + scaler*curChar->getyOffset()));
			vertexData.push_back(zHeight);
			//unten rechts
			vertexData.push_back((curChar->getsizeX() + curChar->getxTextureCoord()) / globalTextureSizeX);
			vertexData.push_back((curChar->getyTextureCoord()) / globalTextureSizeY);
		}

		//update cursor
		virtualCursorInPixel += scaler * curChar->getxAdvance();

		txt->rect->toPixels();
		if (virtualCursorInPixel >= txt->rect->x + txt->rect->width)
		{
			//erase last added char from text and break loop
			for (int j = 0; j < 30; j++)
			{
				vertexData.erase(vertexData.end() - 1);
			}
			lengthCounter--;
			break;
		}

	}

	totalCharNumber += lengthCounter;
	assert(vertexData.size() % 30 == 0); //6 Vertecies are needed each char, every vertex needs 5 floats: glm::vec3 pos + glm::vec2 uv

}