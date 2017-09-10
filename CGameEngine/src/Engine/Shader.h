#pragma once
#include <string>
#include <GL/glew.h>
#include <map>
#include <vector>
#include <iostream>
#include <sstream>
#include "Util/CmpStr.h"
#include "Util/FileSystem.h"
using namespace ENGINE::UTIL;
class Shader {
public:
	Shader(const std::string path);
	~Shader();
	void Bind();
	void Unbind();


	GLint getUniform(std::string name);


private:
	GLuint programID;
	std::map<const std::string, GLint, CmpStr> uniforms;

	GLuint makeShaderFromSource(std::string source, GLuint shaderType);

	void RegisterAllUniforms(std::string shaderSource);
	void RegUniform(const std::string name);
	void RegUniformArray(const std::string name);
};