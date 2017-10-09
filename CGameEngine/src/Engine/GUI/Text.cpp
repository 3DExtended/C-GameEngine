#include "Text.h"
#include "FontHandler.h"
using namespace ENGINE::GUI;

void Text::AppendText(std::string appendText)
{
	text.append(appendText);
	fontHandler->rebuild = true;
}

void Text::SetTextsize(float size) 
{ 
	textHeightInPixel = size; 
	fontHandler->rebuild = true; 
}

Text::~Text()
{
	delete rect;
}

Text::Text(std::string text, FontHandler * fontHandler)
{
	this->fontHandler = fontHandler;
	this->text = text;
}
