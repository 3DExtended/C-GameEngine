#pragma once
#include "Engine/Scene.h"

using namespace ENGINE;

class MainScene : public Scene {
	void Start();
	void LoadShaders();
	void Update();
	void Destroy();
};