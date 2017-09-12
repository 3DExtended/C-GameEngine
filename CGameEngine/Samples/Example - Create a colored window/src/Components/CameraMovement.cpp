#include "CameraMovement.h"
using namespace ENGINE;

void CameraMovement::Start()
{
	camera = GetCurrentCamera();
	camera->yaw = -2.59f;
	camera->pitch = -6.2f;
}

void CameraMovement::Update()
{
	if (userInputEnabled) {
		glm::vec2 mouse = Input::GetMousePosition();

		//TODO move this width and heigt to config file
		float dx = 800 / 2 - mouse.x; 
		float dy = 600 / 2 - mouse.y;

		if (mouselock) {
			SetMousePosition(800/2,600/2);
			camera->yaw -= dx / 5.0f;
			camera->yaw = (float)fmod(camera->yaw, 360);
			camera->pitch += dy / 5.0f;
			if (camera->pitch > 89)camera->pitch = 89;
			if (camera->pitch < -89)camera->pitch = -89;
			if (Input::IsKeyDown(Input::SCANCODE_LSHIFT))
			{
				currentMultiplier = sprintMultiplier;
			}
			else
			{
				currentMultiplier = baseMultiplier;
			}
			if (Input::IsKeyDown(Input::SCANCODE_S))
			{
				camera->pos -= currentMultiplier*0.02f * camera->forward;
			}
			if (Input::IsKeyDown(Input::SCANCODE_W))
			{
				camera->pos += currentMultiplier*0.02f * camera->forward;
			}
			if (Input::IsKeyDown(Input::SCANCODE_Q))
			{
				camera->pos -= currentMultiplier*0.02f * camera->up;
			}
			if (Input::IsKeyDown(Input::SCANCODE_E))
			{
				camera->pos += currentMultiplier*0.02f * camera->up;
			}
			glm::vec3 left = glm::normalize(glm::cross(camera->forward, camera->up));
			if (Input::IsKeyDown(Input::SCANCODE_A))
			{
				camera->pos -= currentMultiplier*0.02f * left;
			}
			if (Input::IsKeyDown(Input::SCANCODE_D))
			{
				camera->pos += currentMultiplier*0.02f * left;
			}
		}

		if (Input::IsKeyDown(Input::SCANCODE_ESCAPE)) {
			if (!esc) {
				mouselock = !mouselock;
				esc = true;
				if (mouselock) {
					ShowMouse(false);
					SetMousePosition(800 / 2, 600 / 2);
				}
				else {
					ShowMouse(true);
				}
			}
		}
		else {
			esc = false;
		}
	}
	else
	{
		SetMousePosition(800 / 2, 600 / 2);
	}

	/******************
	* RotationMatrix *
	*  Code'n'Stuff  *
	******************/
	camera->forward = glm::vec3(sinf(camera->yaw*(float)PI / 180)*cosf(camera->pitch*(float)PI / 180), sinf(camera->pitch*(float)PI / 180), -cosf(camera->yaw*(float)PI / 180)*cosf(camera->pitch*(float)PI / 180));
	camera->up = glm::vec3(sinf(camera->yaw*(float)PI / 180)*cosf((camera->pitch + 90)*(float)PI / 180), sinf((camera->pitch + 90)*(float)PI / 180), -cosf(camera->yaw*(float)PI / 180)*cosf((camera->pitch + 90)*(float)PI / 180));



}
