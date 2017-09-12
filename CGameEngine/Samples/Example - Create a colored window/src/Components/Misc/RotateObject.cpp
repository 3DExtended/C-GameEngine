#include "RotateObject.h"
#include "Engine/ComponentBased/GameObject.h"

using namespace ENGINE;
void RotateObject::Update()
{
	GetCurrentGameObject()->transform.rotation.y += 0.01f;
}
