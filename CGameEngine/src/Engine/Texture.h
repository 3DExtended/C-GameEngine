#pragma once
#include <string>
#include "Util/lodepng.h"
#include "Util/CmpStr.h"
#include "Util/FileSystem.h"
#include "Util/AutoUnbind.h"
#include <GL/glew.h>
#include <cassert>
#include <iostream>

using namespace ENGINE::UTIL;
namespace ENGINE {

	/// <summary>
	/// This class is a wrapper for using textures. 
	/// The implementation supports only "*.png" files.
	/// To use this wrapper:
	///		
	///		... //e.g. load texture 
	///		{
	///			Bind(shader);
	///			Bind(texture);
	///			//bind sampler to shader location
	///			glUniform1i(shader->getUniform("tex"), 0);	//only when the Sampler2D in the shader source code is called "tex"
	///			... //Render stuff
	///		} // Texture and Shader are unbound automatically
	/// 
	/// Use the SetActivationSlot(...) to set which texture slot you wanna use (GL_TEXTUREi, where i ranges from 0 to (GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - 1)).
	/// </summary>
	class Texture :public AutoUnbind {
	public:
		/// <summary>
		/// The constructor loads the image and pushes it to the GPU.
		/// Supported file extensions: .png
		/// </summary>
		/// <param name="path">Path to file (including file extension).</param>
		Texture(const std::string path);

		/// <summary>
		/// This method sets the slot where the texture is bound to.
		/// Valid input-range: GL_TEXTUREi, where i ranges from 0 to (GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS - 1)
		/// </summary>
		/// <param name="value">The slot you want to use.</param>
		void SetActivationSlot(unsigned int value) { numberOfTexture = value; };
	private:
		/// <summary>
		/// Used to bind the texture (using the BIND(...) macro defined in the AutoUnbind header.
		/// </summary>
		void _bind();

		/// <summary>
		/// Used to unbind the texture.
		/// This call is automated when the BIND(...) macro was used to bind this texture.
		/// </summary>
		void _unbind();

		//The texture handle needed for the texture
		GLuint textureID;

		//The slot set by SetActivationSlot(...)
		unsigned int numberOfTexture = GL_TEXTURE0;

	};
}