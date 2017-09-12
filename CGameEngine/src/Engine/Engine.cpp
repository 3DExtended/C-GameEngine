#include "Engine.h"
#include "Display.h"
#include "Mesh.h"
#include "Model.h"
#include "Shader.h"
#include "SceneHandler.h"
#include "Input.h"

using namespace ENGINE;
using namespace ENGINE::UTIL;

void ENGINE::EngineClass::RunEngine(int indexOfStartScene)
{

	//Move those values into config file
	Display* display = new Display(800, 600, "The C++ GameEngine by Peter Esser");
	display->SetClearColor(.2f, .4f, .8f);


	SceneHandler* sceneHandler = SceneHandler::getInstance();
	sceneHandler->SwitchScene(indexOfStartScene);


	bool isRunning = true;
	SDL_Event e;

	//main loop of gameengine
	while (isRunning) {
		//pull sdl events (Key and mouse events, quit event etc.)
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {	//Quit event is triggered after hitting the red X in the upper right corner
				isRunning = false;
			}
			else if (e.type == SDL_KEYDOWN) {
				Input::SetKeyState(e.key.keysym.scancode, true);
			}
			else if (e.type == SDL_KEYUP) {
				Input::SetKeyState(e.key.keysym.scancode, false);
			}
			else if (e.type == SDL_MOUSEBUTTONUP) {
				Input::SetButtonState(e.button.button, false);
			}
			else if (e.type == SDL_MOUSEBUTTONDOWN) {
				Input::SetButtonState(e.button.button, true);
			}
			else if (e.type == SDL_MOUSEMOTION) {
				int x, y;
				SDL_GetMouseState(&x, &y);
				Input::SetMousePosition(x,y);
			}
		}

		//Update gameState
		sceneHandler->Update();

		//clear old buffer so we can render on it
		display->ClearBuffer();
	
		//Render Game
		sceneHandler->Render();

		//swap buffer
		display->SwapBuffer();
	}
}

