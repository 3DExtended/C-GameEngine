#include "Rect.h"

void Rect::toPixels()
{
	if (this->inScreenCoords == false)
		return;

	float displayWidth = float(800);	//TODO replace by display.width
	float displayHeight = float(600);	//TODO replace by display.height

	int newX = int((this->x + 1.0f) / 2.0f * displayWidth);
	int newY = int(-1.0f * ((this->y + 1.0) / 2.0f * displayHeight - displayHeight));

	int newWidth = int(this->width / 2.0f * displayWidth);
	int newHeight = int(this->height / 2.0f * displayHeight);

	this->x = (float)newX;
	this->y = (float)newY;
	this->width = (float)newWidth;
	this->height = (float)newHeight;

	this->inScreenCoords = false;

}

void Rect::fromPixels()
{
	if (this->inScreenCoords == true)
		return;

	float displayWidth = float(800);	//TODO replace by display.width
	float displayHeight = float(600);	//TODO replace by display.height

	float newX = this->x / (float)displayWidth * 2.0f - 1.0f;
	float newY = (float(displayHeight) - this->y) / (float)displayHeight * 2.0f - 1.0f;

	float newWidth = this->width / (float)displayWidth * 2.0f;
	float newHeight = this->height / (float)displayHeight * 2.0f;

	this->x = newX;
	this->y = newY;
	this->width = newWidth;
	this->height = newHeight;

	this->inScreenCoords = true;
}

bool Rect::MouseInRect(glm::vec2 mousePos) {
	return MouseInRect(int(mousePos.x), int(mousePos.y));
}

bool Rect::MouseInRect(int mouseX, int mouseY) {
	bool isinScreenCoords = inScreenCoords;
	toPixels();
	if (mouseX >= this->x) {
		if (mouseX <= this->x + this->width) {
			if (mouseY >= this->y) {
				if (mouseY <= this->y + this->height) {
					if (isinScreenCoords) {
						fromPixels();
					}
					return true;
				}
			}
		}
	}

	if (isinScreenCoords) {
		fromPixels();
	}
	return false;
}