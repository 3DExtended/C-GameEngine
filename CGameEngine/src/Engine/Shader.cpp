#include "Shader.h"

Shader::Shader()
{
}

void Shader::_bind()
{
	std::cout << "Bound" << std::endl;
}

void Shader::_unbind()
{
	std::cout << "Unbound" << std::endl;
}
