#include "GameObject.h"
#include "Component.h"

using namespace ENGINE;

GameObject* GameObject::currentGameObject = nullptr;

GameObject::GameObject()
{
	transform = Transform();
	transform.gameObject = this;
}

GameObject::GameObject(std::string name)
	:name(name)
{
	transform = Transform();
	transform.gameObject = this;
}

void GameObject::Awake()
{
	currentGameObject = this;
	for (Component* comp : components) {
		comp->Awake();
	}
	for (GameObject* child : childs) {
		child->Awake();
	}

	currentGameObject = nullptr;
}

void GameObject::Start()
{
	currentGameObject = this;

	for (Component* comp : components) {
		comp->Start();
	}
	for (GameObject* child : childs) {
		child->Start();
	}
	currentGameObject = nullptr;

}

void GameObject::Update()
{
	currentGameObject = this;

	for (Component* comp : components) {
		comp->Update();
	}
	for (GameObject* child : childs) {
		child->Update();
	}
	currentGameObject = nullptr;

}

void GameObject::LateUpdate()
{
	currentGameObject = this;

	for (Component* comp : components) {
		comp->LateUpdate();
	}
	for (GameObject* child : childs) {
		child->LateUpdate();
	}
	currentGameObject = nullptr;

}

void GameObject::Render()
{
	currentGameObject = this;

	for (Component* comp : components) {
		comp->Render();
	}
	for (GameObject* child : childs) {
		child->Render();
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
	for (GameObject* child : childs) {
		child->Destroy();
	}
	currentGameObject = nullptr;

}

void GameObject::AddComponent(Component* comp)
{
	components.push_back(comp);
	comp->gameObject = this;
}

GameObject * ENGINE::GameObject::GetParent() { 
	return this->parent; 
}

std::vector<GameObject*> ENGINE::GameObject::GetChilds()
{
	return childs;
}

void ENGINE::GameObject::SetParent(GameObject * obj)
{
	if (this->parent != nullptr) {
		std::cerr << "You are not supposed to have two parent!";
	}
	else {
		this->parent = obj;
		obj->childs.push_back(this);
	}
}

void GameObject::AddChild(GameObject * obj)
{
	if (obj->parent != nullptr) {
		std::cerr << "You are not supposed to have two parent!";
	}
	else {
		childs.push_back(obj);
		obj->parent = this;
	}
}
