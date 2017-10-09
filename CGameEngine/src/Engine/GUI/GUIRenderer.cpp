#include "GUIRenderer.h"
using namespace ENGINE::GUI;

GUIRenderer* GUIRenderer::instance = nullptr;

GUIRenderer * GUIRenderer::GetInstance() { 
	if (instance == nullptr) {
		instance = new GUIRenderer();
	}
	return instance; 
}

void GUIRenderer::RegisterGUIElement(GUIElement * element)
{
	//TODO optimize this structure!
	unsigned int index;
	for (index = 0; index < elements.size(); index++)
	{
		if (element < elements[index])
		{
			elements.insert(elements.begin() + index, element);
			break;
		}
	}

	//TODO handle subbuffering
}

void GUIRenderer::UnregisterGUIElement(GUIElement * element)
{
	auto iterator = std::remove(elements.begin(), elements.end(), element);
	int index = std::distance(elements.begin(), iterator);
	elements.erase(iterator, elements.end());

	//TODO handle subbuffering

}
