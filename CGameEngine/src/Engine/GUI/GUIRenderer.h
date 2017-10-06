#pragma once
#include <vector>
#include <algorithm>
#include <GL/glew.h>


class GUIElement;
class GUIRenderer {
public:
	static GUIRenderer* GetInstance();
	void Render();

private:
	static GUIRenderer* instance;
	GUIRenderer();

	std::vector<GUIElement*> elements;

	GLuint vao, vbo;



private:
	friend class GUIElement;
	void RegisterGUIElement(GUIElement* element);
	void UnregisterGUIElement(GUIElement* element);
};