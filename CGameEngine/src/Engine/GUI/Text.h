#pragma once
#include <string>
#include "GUIElement.h"
#include "../Util/Rect.h"
using namespace ENGINE::UTIL;
namespace ENGINE {
	namespace GUI {
		class FontHandler;

		/// <summary>
		/// This class is used to handle text on screen.
		/// In particular this class is a wrapper to a std::string instance which is than rendered to the screen.
		/// Note that this class does not have a public constructor since it has to be initialized using a FontHandler instance. 
		/// </summary>
		class Text {
		public:
			/// <summary>
			/// This methods adds a string ("appendText") to the string of this class-instance 
			/// </summary>
			/// <param name="appendText">The text you want to append</param>
			void AppendText(std::string appendText);

			/// <summary>
			/// This methode returns the string represented by this class 
			/// </summary>
			/// <returns>The string used in this class</returns>
			std::string GetString() const { return text; }

			/// <summary>
			/// The depth of this component is used to move a text before or behind another GUI item. 
			/// </summary>
			/// <param name="val">The new depth for this instance</param>
			void SetDepth(float val) {	//TODO move this into Text.cpp
				if (val >= 0) {
					depth = val;
					//TODO say fonthandler to change its sorting
				}
				else
					std::cout << "The depth value of a GUIElement is caped to values greater then zero." << std::endl;
			}

			/// <summary>
			/// This returns the current depth for this item (See also SetDepth for more detail). 
			/// </summary>
			/// <returns>returns the current depth</returns>
			float GetDepth() { return depth; }

			/// <summary>
			/// This sets the textsize using pixels.
			/// </summary>
			/// <remarks>
			/// Note that the pixel size can vary from screen to screen
			/// </remarks>
			/// <param name="size">The new text size</param>
			void SetTextsize(float size);

			/// <summary>
			/// This operator is used to order the text elements by their depth.
			/// The text instance with the smaller depth value wins this comparison.
			/// </summary>
			/// <param name="b">The text you want to compare against</param>
			/// <returns>True, if the left text element has a smaller depth value. Else false</returns>
			bool operator <(const Text &b) const {
				return this->depth < b.depth;
			}

			/// <summary>
			/// The deconstructor for this class.
			/// Destroys a text component. 
			/// </summary>
			~Text();

		private:
			friend class FontHandler;	//Used so the FontHandler can access the constructor to create a new text component.
			
			/// <summary>
			/// The constructor of this class.
			/// You need to pass the string you want to get rendered and an valid 
			/// instance of a FontHandler to indicate the font the text gets rendered in. 
			/// </summary>
			/// <param name="text">The string that gets represented</param>
			/// <param name="fontHandler">The font handler that creates this text element</param>
			Text(std::string text, FontHandler* fontHandler);

			// The depth value is used to order each GUI element to avoid transperency problems.
			// The higher the number, the further away from the camera the GUIElement will be rendered.
			float depth = 0;

			// The rect is a component representing the place and the size of the text. 
			Rect* rect = new Rect(0, 0, 800, 600);

			// The height of the text in pixel
			float textHeightInPixel = 12.0f;
		private:
			// The string that is represented
			std::string text;

			// A pointer to the corresponding handler that created this text instance
			FontHandler* fontHandler = nullptr;
		};
	}
}