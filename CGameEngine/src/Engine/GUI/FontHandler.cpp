#include "FontHandler.h"
#include "GUIRenderer.h"

std::vector<FontHandler*> FontHandler::fonts = std::vector<FontHandler*>();

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
	for each (FontHandler* var in FontHandler::fonts)
	{
		var->Render();
	}
}

FontHandler::FontHandler(const std::string pathToFontFiles, const std::string shaderPath)
{
	FontHandler::fonts.push_back(this);

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
}

Text * FontHandler::AddText(std::string str)
{
	Text* txt = new Text(str);
	
	unsigned int index;
	for (index = 0; index < texts.size(); index++)
	{
		if (txt < texts[index])
		{
			texts.insert(texts.begin() + index, txt);
			break;
		}
	}

	if (index != texts.size())
		rebuild = true;

	return txt;
}


void FontHandler::Render()
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	if (rebuild) {
		std::sort(texts.begin(), texts.end());
		//TODO repush everything
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
