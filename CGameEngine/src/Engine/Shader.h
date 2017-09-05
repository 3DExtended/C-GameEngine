#pragma once
#include "Util/AutoUnbind.h"
#include <iostream>
class Shader :public AutoUnbind {
public: 
	Shader();

	void _bind();
	void _unbind();
};