#include "Engine/Display.h"
#include <tchar.h>	//Other entry point for windows
#include "Engine/Mesh.h"
#include "Engine/Model.h"

using namespace ENGINE;

int _tmain(int argc, _TCHAR* argv[]) {
	Display* display = new Display(800, 600, "The C++ GameEngine by Peter Esser");
	display->SetClearColor(.2f, .4f, .8f);

	//TODO remove this
	//this is only for demonstrating the gameLoop
	float red = 0;

	Mesh *mesh = new Mesh();
	mesh->addPoint(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec2(0, 0), glm::vec4(1, 1, 1, 1));
	mesh->addPoint(glm::vec3(-1, 0, 0), glm::vec3(0, 0, -1), glm::vec2(0, 0), glm::vec4(1, 1, 1, 1));
	mesh->addPoint(glm::vec3(1, -1, 0), glm::vec3(0, 0, -1), glm::vec2(0, 0), glm::vec4(1, 1, 1, 1));

	mesh->addTriangle(0, 1, 2);

	Model* model = new Model(mesh);

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
		model->Render();

		//swap buffer
		display->SwapBuffer();
	}
	return 0;
}