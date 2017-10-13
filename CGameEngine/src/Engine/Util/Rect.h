#pragma once
#include <glm/glm.hpp>
#include "../Display.h"

namespace ENGINE {
	namespace UTIL {

		/// <summary>
		/// A rect providing info about a 2D-position and width and height 
		/// either in pixels or in screen location (-1 to 1 on the x- and y-axis) 
		/// </summary>
		class Rect {
		public:
			/// <summary>
			/// Creates a new Rect where every component (x, y, width, height) is initialized with 0. 
			/// </summary>
			Rect() {};
			~Rect() {};

			/// <summary>
			/// creates a new rect with given parameters 
			/// </summary>
			/// <param name="x">the x position</param>
			/// <param name="y">the y position</param>
			/// <param name="width">the width for the rect</param>
			/// <param name="height">the height for the rect</param>
			/// <param name="inScreenCoords">are the passed values in a coord system from -1 to 1</param>
			Rect(float x, float y, float width, float height, bool inScreenCoords = false) {
				this->x = x;
				this->y = y;
				this->width = width;
				this->height = height;
				this->inScreenCoords = inScreenCoords;
			};

			float x = 0.0f;
			float y = 0.0f;
			float width = 0.0f;
			float height = 0.0f;

			/// <summary>
			/// Converts this rect from Screen-Coordinats into Pixel-Coordinats based on the current display dimensions 
			/// </summary>
			void toPixels();

			/// <summary>
			/// converts this rect from pixel coords into screen coords based on the current display dimensions 
			/// </summary>
			void fromPixels();
			bool MouseInRect(glm::vec2 mousePos);
			bool MouseInRect(int mouseX, int mouseY);
		private:
			//is this rect in screen coords
			bool inScreenCoords;

		};
	}
}