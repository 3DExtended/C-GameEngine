#pragma once
#include <string>
#include <vector>
#include <GL/glew.h>
#include <fstream>
#include <streambuf>
#include "../Util/Util.h"
#include "../Shader.h"
#include "../Texture.h"
#include "Text.h"

using namespace ENGINE;
using namespace ENGINE::UTIL;
class FontHandler {
	static void RenderAllFonts();
	FontHandler(const std::string pathToFontFile, const std::string shaderPath);
	~FontHandler();


	Text* AddText(std::string str);


private:
	/// <summary>
	/// A helper class which symbols the a char from a font file
	/// </summary>
	class Character
	{
	public:
		Character() {};
		~Character() {};

		Character(int id,
			float xTextureCoord,
			float yTextureCoord,
			float xOffset,
			float yOffset,
			float sizeX,
			float sizeY,
			float xAdvance);

		int getID() { return id; }
		float getxTextureCoord() { return xTextureCoord; }
		float getyTextureCoord() { return yTextureCoord; }
		float getxOffset() { return xOffset; }
		float getyOffset() { return yOffset; }
		float getsizeX() { return sizeX; }
		float getsizeY() { return sizeY; }
		float getxAdvance() { return xAdvance; }


	private:
		int id;
		float xTextureCoord;
		float yTextureCoord;
		float xOffset;
		float yOffset;
		float sizeX;
		float sizeY;
		float xAdvance;
	};


private:
	static std::vector<FontHandler*> fonts;

	void Render();

	GLuint vbo, vao;
	unsigned int totalCharNumber = 0;


	bool rebuild = false;

	Character* characters[256];

	Shader* shader;
	Texture* texture;

	std::vector<Text*> texts;

};