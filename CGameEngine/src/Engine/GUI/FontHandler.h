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

namespace ENGINE {
	namespace GUI {
		/// <summary>
		/// This class is used to represent one font on the screen.
		/// It handles the render call that renders every text element on the screen and also is able
		/// to return a Text object to represent one text. 
		/// This class is implemented using the singleton pattern.
		/// </summary>
		class FontHandler {
		public:
			/// <summary>
			/// The deconstructor of this class deletes all text components since they are not 
			/// valid without their renderer 
			/// </summary>
			~FontHandler();

			/// <summary>
			/// The singleton getter of this class.
			/// This call is used to get the fonthandler used for a specified font (by fontfiles and shader) 
			/// </summary>
			/// <param name="pathToFontFiles">
			/// This call expects to find an .png image containing the letters and also 
			/// the .fnt file which holds detailed information about each char on that image 
			/// </param>
			/// <param name="shaderPath">The path to the shader files used for rendering text</param>
			/// <returns>A pointer to the FontHandler used to render texts in this font-shader combination</returns>
			static FontHandler* GetFontHandler(const std::string pathToFontFiles, const std::string shaderPath);

			/// <summary>
			/// This method creates a new text by specifying a std::string. 
			/// </summary>
			/// <param name="str">The text you want to add to the render list</param>
			/// <returns>The Text handler for that str and font-shader combination symbolized with this class</returns>
			Text* AddText(std::string str);

			/// <summary>
			/// This method creates a new text by specifying a std::string and the depth of the text. 
			/// </summary>
			/// <param name="str">The text you want to add to the render list</param>
			/// <param name="depth">The depth for the new text</param>
			/// <returns>The Text handler for that str and font-shader combination symbolized with this class</returns>
			Text * AddText(std::string str, float depth);

			/// <summary>
			/// This call renders every font stored in the "fonts" vector
			/// </summary>
			static void RenderAllFonts();
		private:
			/// <summary>
			/// A helper class which symbols a character from a font file
			/// </summary>
			class Character
			{
			public:
				/// <summary>
				/// Default constructor. 
				/// </summary>
				Character() {};

				/// <summary>
				/// A constructor that creates a character instance with its specified attributes
				/// </summary>
				/// <param name="id">The id of this char (normally ascii representation of char)</param>
				/// <param name="xTextureCoord">X component of the upper left corner of this char on its font-texture</param>
				/// <param name="yTextureCoord">Y component of the upper left corner of this char on its font-texture</param>
				/// <param name="xOffset">A virtual cursor will be used. This value specifies where to locate this chars vertex depending on the x-offset</param>
				/// <param name="yOffset">A virtual cursor will be used. This value specifies where to locate this chars vertex depending on the y-offset</param>
				/// <param name="sizeX">The width of this character</param>
				/// <param name="sizeY">The height of this character</param>
				/// <param name="xAdvance">Which offset receives the virtual cursor after writing this letter</param>
				Character(int id,
					float xTextureCoord,
					float yTextureCoord,
					float xOffset,
					float yOffset,
					float sizeX,
					float sizeY,
					float xAdvance);

				/// <summary>
				/// Getter for the ID attribute 
				/// </summary>
				/// <returns>The ID</returns>
				int getID() { return id; }

				/// <summary>
				/// Getter for the xTextureCoord attribute 
				/// </summary>
				/// <returns>The xTextureCoord</returns>
				float getxTextureCoord() { return xTextureCoord; }

				/// <summary>
				/// Getter for the yTextureCoord attribute 
				/// </summary>
				/// <returns>The yTextureCoord</returns>
				float getyTextureCoord() { return yTextureCoord; }
				
				/// <summary>
				/// Getter for the xOffset attribute 
				/// </summary>
				/// <returns>The xOffset</returns>
				float getxOffset() { return xOffset; }

				/// <summary>
				/// Getter for the yOffset attribute 
				/// </summary>
				/// <returns>The yOffset</returns>
				float getyOffset() { return yOffset; }

				/// <summary>
				/// Getter for the sizeX attribute 
				/// </summary>
				/// <returns>The sizeX</returns>
				float getsizeX() { return sizeX; }

				/// <summary>
				/// Getter for the sizeY attribute 
				/// </summary>
				/// <returns>The sizeY</returns>
				float getsizeY() { return sizeY; }

				/// <summary>
				/// Getter for the xAdvance attribute 
				/// </summary>
				/// <returns>The xAdvance</returns>
				float getxAdvance() { return xAdvance; }


			private:
				// The ascii representation of this letter
				int id;

				// The x position of this letter in the texture of the font
				float xTextureCoord;

				// The y position of this letter in the texture of the font
				float yTextureCoord;

				// The x-offset from the virtual cursor that has to be used
				float xOffset;

				// The y-offset from the virtual cursor that has to be used
				float yOffset;

				// The width of this letter
				float sizeX;

				// The height of this letter
				float sizeY;

				// How far to the right do you want to move the virtual cursor after drawing this letter
				float xAdvance;
			};


		private:
			// A list containing all the font handlers that have been created (so that we can render them with one call to this class)
			static std::vector<FontHandler*> fonts;

			// The private constructor of this class.
			// The resulting instance symilizes a font-shader combination which can be used to create text handlers which than can be rendered. 
			// <param name="pathToFontFile">The path to the folder with an appended "/<name>" that contains a .fnt and a .png file with the "<name>" as name.</param>
			// <param name="shaderPath">A path to the shader you want to use</param>
			FontHandler(const std::string pathToFontFile, const std::string shaderPath);
			
			// Inserts a text instance into the texts vector (which is sorted by the depth values)
			void InsertText(Text *);

			// This function renders every text entry in the texts vector for this font
			void Render();

			//OpenGL handlers for the vao and vbo of the texts
			GLuint vbo = 0, vao = 0;

			// how many chars are we displaying with this font
			unsigned int totalCharNumber = 0;

			// An array containing the different supported chars of a font
			Character* characters[256];

			// The shader that will be used to render this font
			Shader* shader;

			// The texture of this font
			Texture* texture;

			// A sorted (by depth values) list containing every text instances for this font 
			std::vector<Text*> texts;

			// Adds quads to the vertexData list for a passed text instance
			void AddQuadsForText(Text * txt);

			// The list of floats that represents the vertex floats needed for every text (3D Position and 2D UV)
			std::vector<float> vertexData;

		private:
			friend class Text;	//When ever a text instance is modified we have to set the rebuild option on its font to rebuild the vao before rendering again
			
			// Has the vao and vbo to get rebuild?
			bool rebuild = false;
		};

	}
}