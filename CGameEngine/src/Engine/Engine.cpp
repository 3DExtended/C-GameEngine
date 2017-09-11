#include "Engine.h"
#include "Display.h"
#include "Mesh.h"
#include "Model.h"
#include "Shader.h"

using namespace ENGINE;
using namespace ENGINE::UTIL;

void ENGINE::RunEngine()
{
	Display* display = new Display(800, 600, "The C++ GameEngine by Peter Esser");
	display->SetClearColor(.2f, .4f, .8f);

	Mesh *mesh = new Mesh();
	mesh->addPoint(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec2(0, 0), glm::vec4(1, 0, 0, 1));
	mesh->addPoint(glm::vec3(-1, 0, 0), glm::vec3(0, 0, -1), glm::vec2(0, 0), glm::vec4(0, 1, 0, 1));
	mesh->addPoint(glm::vec3(1, -1, 0), glm::vec3(0, 0, -1), glm::vec2(0, 0), glm::vec4(0, 0, 1, 1));

	mesh->addTriangle(0, 1, 2);

	Model* model = new Model(mesh);

	//Load Shader
	Shader* shader = new Shader(FileSystem::resFolderPrefix + "res/shader/diffuseShader");



	bool isRunning = true;
	SDL_Event e;

	//main loop of gameengine
	while (isRunning) {
		//pull sdl events (Key and mouse events, quit event etc.)
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {	//Quit event is triggered after hitting the red X in the upper right corner
				isRunning = false;
			}
			//TODO handle key events
		}

		//Update gameState

		//clear old buffer so we can render on it
		display->ClearBuffer();

		//Render game
		Bind(shader);

		model->Render();


		//swap buffer
		display->SwapBuffer();
	}
}
