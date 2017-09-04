#include "Display.h"

using namespace ENGINE;
Display::Display(int width, int height, const std::string title)
	: width(width), height(height)
{
	glewExperimental = GL_TRUE;
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		std::cerr << "Could not init SDL2. Received following error: " << SDL_GetError() << std::endl;
	}
	else {
		std::cout << "Successfully init SDL2" << std::endl;

		//Request modern OpenGL context and set important attributes for OpenGL
		SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
		SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

		//create window for rendering
		window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
		
		//create context for OpenGL
		glContext = SDL_GL_CreateContext(window);

		//init glew
		GLenum res = glewInit();
		if (res != GLEW_OK) {
			std::cerr << "Glew failed to init..." << std::endl;
		}
		else {
			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);


			//print OpenGL versions
			std::cout << "----------" << std::endl;
			std::cout << "OpenGL is loaded:" << std::endl;
			std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
			std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
			std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
			std::cout << "----------" << std::endl;
		}

	}
}

Display::~Display()
{
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Display::ClearBuffer()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::SwapBuffer()
{
	SDL_GL_SwapWindow(window);
}
