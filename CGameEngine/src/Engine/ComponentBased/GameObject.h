#pragma once
#include <vector>
#include <string>
#include "Component.h"
class GameObject {
public:
	GameObject();
	GameObject(const std::string name);
	
	~GameObject();

	void AddComponent(Component* comp);

private:
	std::vector<Component*> components;

	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void Render();
	void Destroy();

	const std::string name = "";
};