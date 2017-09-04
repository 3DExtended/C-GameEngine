#include "Engine/Display.h"
#include <tchar.h>	//Other entry point for windows

using namespace ENGINE;

int _tmain(int argc, _TCHAR* argv[]) {
	Display* display = new Display(800, 600, "The C++ GameEngine by Peter Esser");
	

	while (1) {}
	return 0;
}