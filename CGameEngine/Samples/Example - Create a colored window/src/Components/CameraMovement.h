#pragma once
#include "Engine/ComponentBased/Component.h"

using namespace ENGINE;
class CameraMovement : public Component {
public:
	void Start();
	void Update();

private:
	bool userInputEnabled = true;
	bool mouselock = false, esc = false;

	float currentMultiplier = 1.0f;
	float baseMultiplier = 1.0f;
	float sprintMultiplier = 3.0f;

	Camera* camera = nullptr;
};