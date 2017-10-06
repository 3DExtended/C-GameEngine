#pragma once
#include <string>
#include "GUIElement.h"
class Text{
public:
	void AddText(std::string appendText);
	void Substring(unsigned int start, unsigned int size);
	std::string GetString() const{ return text; }

	void SetDepth(float val) {
		if (val >= 0) {
			depth = val;
			//TODO say fonthandler to change its sorting
		}
		else
			std::cout << "The depth value of a GUIElement is caped to values greater then zero." << std::endl;
	}

	float GetDepth() { return depth; }

	bool Text::operator <(const Text &b) const {
		return this->depth < b.depth;
	}

private:
	friend class FontHandler;
	Text(std::string text);

	/// <summary>
	/// The depth value is used to order each GUI element to avoid transperency problems.
	/// The higher the number, the further away from the camera the GUIElement will be rendered.
	/// </summary>
	float depth = 0;
private:
	std::string text;

};