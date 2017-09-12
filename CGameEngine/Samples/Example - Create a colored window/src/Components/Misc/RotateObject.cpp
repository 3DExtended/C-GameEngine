#include "RotateObject.h"
#include "Engine/ComponentBased/GameObject.h"
void RotateObject::Update()
{
	GetCurrentGameObject()->transform.rotation.y += 0.01f;
}
