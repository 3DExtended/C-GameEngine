#include "Input.h"
using namespace ENGINE;

bool Input::keyIsDown[1024];
bool Input::buttonIsDown[256];
int Input::mousePosX = 0;
int Input::mousePosY = 0;

bool Input::IsKeyDown(int scanCode) { 
	return keyIsDown[scanCode];
}

void Input::SetKeyState(int scanCode, bool isDown) {
	keyIsDown[scanCode] = isDown; 
}

bool Input::IsButtonDown(int scanCode) { 
	return buttonIsDown[scanCode]; 
}

void Input::SetButtonState(int scanCode, bool isDown) { 
	buttonIsDown[scanCode] = isDown;
}

glm::vec2 Input::GetMousePosition() { 
	return glm::vec2(mousePosX,mousePosY);
}

void Input::SetMousePosition(int x, int y) { 
	mousePosX = x;
	mousePosY = y;
}
