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
	class Texture :public AutoUnbind {
	public:
		Texture(const std::string);

		void SetActivationSlot(unsigned int value) { numberOfTexture = value; };
	private:
		void _bind();
		void _unbind();


		GLuint textureID;

		unsigned int numberOfTexture = GL_TEXTURE0;

	};
}