#include "Engine/Display.h"
#include <tchar.h>	//Other entry point for windows

using namespace ENGINE;

int _tmain(int argc, _TCHAR* argv[]) {
	Display* display = new Display(800, 600, "The C++ GameEngine by Peter Esser");
	display->SetClearColor(.2f, .4f, .8f);

	//TODO remove this
	//this is only for demonstrating the gameLoop
	float red = 0;

	//main loop of gameengine
	while (1) {
		//Update gameState
		
		//TODO remove this
		display->SetClearColor(red, .4f, .8f);
		red += 0.01f;
		if (red > 1.0f) {
			red = 0;
		}



		//clear old buffer so we can render on it
		display->ClearBuffer();

		//Render game

		//swap buffer
		display->SwapBuffer();
	}
	return 0;
}