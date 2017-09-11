#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::GameObject(const std::string name)
	:name(name)
{
}

GameObject::~GameObject()
{
}

void GameObject::Awake()
{
	for (Component* comp : components) {
		comp->Awake();
	}
}

void GameObject::Start()
{
	for (Component* comp : components) {
		comp->Start();
	}
}

void GameObject::Update()
{
	for (Component* comp : components) {
		comp->Update();
	}
}

void GameObject::LateUpdate()
{
	for (Component* comp : components) {
		comp->LateUpdate();
	}
}

void GameObject::Render()
{
	for (Component* comp : components) {
		comp->Render();
	}
}

void GameObject::Destroy()
{
	//TODO remove all components
	for (Component* comp : components) {
		comp->Destroy();
	}
}

void GameObject::AddComponent(Component* comp)
{
	components.push_back(comp);
}
