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
public:
	~FontHandler();
	static FontHandler* GetFontHandler(const std::string pathToFontFiles, const std::string shaderPath);

	Text* AddText(std::string str);

	Text * AddText(std::string str, float depth);


	static void RenderAllFonts();
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

	FontHandler(const std::string pathToFontFile, const std::string shaderPath);
	void InsertText(Text *);

	void Render();


	GLuint vbo = 0, vao = 0;
	unsigned int totalCharNumber = 0;



	Character* characters[256];

	Shader* shader;
	Texture* texture;

	std::vector<Text*> texts;

	void AddQuadsForText(Text * txt);

	std::vector<float> vertexData;

private:
	friend class Text;
	bool rebuild = false;
};

