#pragma once
#include <iostream>
class GUIElement {
public:
	void SetDepth(float val) {
		if (val >= 0)
			depth = val;
		else
			std::cout << "The depth value of a GUIElement is caped to values greater then zero." << std::endl;
	}

	float GetDepth() { return depth; }

	bool operator <(const GUIElement &b) const {
		return this->depth < b.depth;
	}

private:
	friend class GUIRenderer;
	/// <summary>
	/// The depth value is used to order each GUI element to avoid transperency problems.
	/// The higher the number, the further away from the camera the GUIElement will be rendered.
	/// </summary>
	float depth = 0;
};