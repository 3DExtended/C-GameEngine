#include "Shader.h"

using namespace ENGINE;

Shader::Shader(const std::string path)
{
	std::string vertContent = FileSystem::LoadFile(path + ".vert");
	std::string fragContent = FileSystem::LoadFile(path + ".frag");

	//create shaders
	GLuint vertexID = makeShaderFromSource(vertContent, GL_VERTEX_SHADER);
	GLuint fragID = makeShaderFromSource(fragContent, GL_FRAGMENT_SHADER);

	//make combined shader program
	//link program
	programID = glCreateProgram();
	glAttachShader(programID, vertexID);
	glAttachShader(programID, fragID);
	glLinkProgram(programID);

	GLint Result = GL_FALSE;
	int infoLogLength;
	//check if program is valid
	glGetProgramiv(programID, GL_LINK_STATUS, &Result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 1) {
		//we could not bundle the two shaders
		std::vector<char> programErrorMessage(infoLogLength + 1);
		glGetProgramInfoLog(programID, infoLogLength, NULL, &programErrorMessage[0]);
		printf("Shader link failed. \n %s \n", &programErrorMessage[0]);
		std::cerr << "Shader link failed. TODO: Handle Event." << std::endl;
	}

	//Detach Shaders
	glDetachShader(programID, vertexID);
	glDetachShader(programID, fragID);

	//Delete shaders since program is enough information
	glDeleteShader(vertexID);
	glDeleteShader(fragID);

	//register uniforms
	RegisterAllUniforms(vertContent);
	RegisterAllUniforms(fragContent);

}

Shader::~Shader()
{
	//delete shader program
	glDeleteProgram(programID);
}

void Shader::_bind()
{
	//Start using the shader program
	glUseProgram(programID);
}

void Shader::_unbind()
{
	//stop using shader program
	glUseProgram(0);
}

void Shader::RegisterAllUniforms(std::string shaderSource)
{
	//search for "unifrom" in source code
	std::string buf;
	std::stringstream ss(shaderSource);

	while (ss >> buf) { //read word by word (and remove new line character)
		if (buf == "uniform") {
			if (ss >> buf) {	//read type of unifom
				if (ss >> buf) {	//read name of uniform
					RegUniform(buf);	//register uniform with that name
				}
			}
		}
	}
}

void Shader::RegUniform(const std::string name)
{
	std::map<const std::string, GLint>::iterator it = uniforms.find(name.c_str());
	
	if (it == uniforms.end()) {
		GLint id = glGetUniformLocation(programID, name.c_str());
		uniforms.insert(std::make_pair(name.c_str(), id));
	}
}

void Shader::RegUniformArray(const std::string name)
{
	//TODO
}

GLint Shader::getUniform(std::string name)
{
	std::map<const std::string, GLint>::iterator it = uniforms.find(name.c_str());
	return it->second;
}

GLuint Shader::makeShaderFromSource(std::string source, GLuint shaderType)
{
	GLuint shaderID = glCreateShader(shaderType);;
	const char * sourcePointer = source.c_str();

	glShaderSource(shaderID, 1, &sourcePointer, NULL);
	glCompileShader(shaderID);

	//Check for errors
	GLint result = GL_FALSE;
	int infoLogLength;
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

	if (infoLogLength > 1) {
		//the shader did not compile...
		std::vector<char> vertexShaderErrorMessage(infoLogLength + 1);
		glGetShaderInfoLog(shaderID, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
		printf("Shader Compile Error: \n %s\n", &vertexShaderErrorMessage[0]);

		//Error handling..
		std::cerr << "Error was detected..." << std::endl;
	}
	return shaderID;
}
