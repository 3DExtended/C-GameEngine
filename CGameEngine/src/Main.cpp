#include "Engine/Display.h"
#include <tchar.h>	//Other entry point for windows
#include "Engine/Shader.h"
using namespace ENGINE;

int _tmain(int argc, _TCHAR* argv[]) {
	Display* display = new Display(800, 600, "The C++ GameEngine by Peter Esser");

	Shader* shader = new Shader();
	{
		Bind(shader);
	
		std::cout << "Test " << std::endl;

	}



	while (1) {}
	return 0;
}