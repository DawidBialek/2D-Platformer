#include "../include/stdafx.h"
#include "../include/Button.h"

int Button::maxTextWidth = 0;
int Button::widestTextPosition = 90000;

Button::Button()
{
}

Button::Button(std::string str)
{
	text.setString(str);
}


Button::~Button()
{
}
