#include <tchar.h>	//Other entry point for windows
#include <iostream>	
#include <GL/glew.h>
#include <SDL2/SDL.h>	//main file for sdl2

int _tmain(int argc, _TCHAR* argv[]) {
	
	glewExperimental = GL_TRUE;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cout << "Could not init SDL2. Received following error: " << SDL_GetError() << std::endl;
	}
	else {
		std::cout << "It works" << std::endl;
	}

	while (1) {}
	return 0;
}