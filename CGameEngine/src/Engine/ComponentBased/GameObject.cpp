#include "GameObject.h"
#include "Component.h"

using namespace ENGINE;

GameObject* GameObject::currentGameObject = nullptr;

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
	currentGameObject = this;
	for (Component* comp : components) {
		comp->Awake();
	}
	currentGameObject = nullptr;
}

void GameObject::Start()
{
	currentGameObject = this;

	for (Component* comp : components) {
		comp->Start();
	}
	currentGameObject = nullptr;

}

void GameObject::Update()
{
	currentGameObject = this;

	for (Component* comp : components) {
		comp->Update();
	}
	currentGameObject = nullptr;

}

void GameObject::LateUpdate()
{
	currentGameObject = this;

	for (Component* comp : components) {
		comp->LateUpdate();
	}
	currentGameObject = nullptr;

}

void GameObject::Render()
{
	currentGameObject = this;

	for (Component* comp : components) {
		comp->Render();
	}
	currentGameObject = nullptr;

}

void GameObject::Destroy()
{
	currentGameObject = this;

	//TODO remove all components
	for (Component* comp : components) {
		comp->Destroy();
	}
	currentGameObject = nullptr;

}

void GameObject::AddComponent(Component* comp)
{
	components.push_back(comp);
}
