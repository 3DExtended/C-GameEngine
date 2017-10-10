#pragma once
#include <string>
#include "GUIElement.h"
#include "../Util/Rect.h"
using namespace ENGINE::UTIL;
namespace ENGINE {
	namespace GUI {
		class FontHandler;
		class Text {
		public:
			void AppendText(std::string appendText);
			std::string GetString() const { return text; }

			void SetDepth(float val) {
				if (val >= 0) {
					depth = val;
					//TODO say fonthandler to change its sorting
				}
				else
					std::cout << "The depth value of a GUIElement is caped to values greater then zero." << std::endl;
			}

			float GetDepth() { return depth; }

			void SetTextsize(float size);

			bool operator <(const Text &b) const {
				return this->depth < b.depth;
			}

			~Text();

		private:
			friend class FontHandler;
			Text(std::string text, FontHandler* fontHandler);

			/// <summary>
			/// The depth value is used to order each GUI element to avoid transperency problems.
			/// The higher the number, the further away from the camera the GUIElement will be rendered.
			/// </summary>
			float depth = 0;

			Rect* rect = new Rect(0, 0, 800, 600);

			float textHeightInPixel = 12.0f;
		private:
			std::string text;
			FontHandler* fontHandler = nullptr;
		};
	}
}