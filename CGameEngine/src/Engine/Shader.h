#pragma once
#include <string>
#include <GL/glew.h>
#include <map>
#include <vector>
#include <iostream>
#include <sstream>
#include "Util/CmpStr.h"
#include "Util/FileSystem.h"
#include "Util/AutoUnbind.h"

using namespace ENGINE::UTIL;
namespace ENGINE {
	class Shader :public AutoUnbind {
	public:
		Shader(const std::string path);
		~Shader();

		GLint getUniform(std::string name);

		static Shader* getShader(const std::string name);

	private:
		void _bind();
		void _unbind();

		GLuint programID;
		std::map<const std::string, GLint, CmpStr> uniforms;

		GLuint makeShaderFromSource(std::string source, GLuint shaderType);

		void RegisterAllUniforms(std::string shaderSource);
		void RegUniform(const std::string name);
		void RegUniformArray(const std::string name);

		static std::map<const std::string, Shader*, CmpStr> allShaders;

	private: 
		friend class SceneHandler;
		static void dropAllShaders();

	};
}