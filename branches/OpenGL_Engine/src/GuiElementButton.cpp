#include "GuiElementButton.h"

#include "Window.h"

GuiElementButton::GuiElementButton()
{
	_buttonDelay = BUTTONPRESSDELAY_FPS;
	_buttonFlag = BUTTON_NONE;
}

bool GuiElementButton::CheckCollision(float mouseX, float mouseY, bool press)
{
	switch(_buttonFlag)
	{
		case BUTTON_ON_MOUSE:
			_buttonDelay--;
			if(_buttonDelay == 0)
				_buttonFlag = BUTTON_NONE;
		break;
		case BUTTON_PRESS:
			_buttonDelay--;
			if(_buttonDelay == 0)
				_buttonFlag = BUTTON_NONE;
		break;
	}

	if(mouseX > x)
		if(mouseX < (x + width))
			if(mouseY > y)
				if(mouseY < (y + height))
				{
					if(press)
					{
						_buttonFlag = BUTTON_PRESS;
						_buttonDelay = BUTTONPRESSDELAY_FPS;
						_colors[0] = 0.1f; _colors[1] = 0.5f; _colors[2] = 0.1f;
						return true;
					}

					if(!press && _buttonFlag != BUTTON_PRESS)
					{
						_buttonFlag = BUTTON_ON_MOUSE;
						_buttonDelay = BUTTONPRESSDELAY_FPS/BUTTONPRESSDELAY_FPS;
					}
				}	
	switch(_buttonFlag)
	{
		case BUTTON_NONE:
			_colors[0] = 1.0f; _colors[1] = 1.0f; _colors[2] = 1.0f;
			return false;
		break;
		case BUTTON_ON_MOUSE:
			_colors[0] = 0.5f; _colors[1] = 0.1f; _colors[2] = 0.1f;
			return false;
		break;
		case BUTTON_DISABLE:
			_colors[0] = 0.2f; _colors[1] = 0.2f; _colors[2] = 0.2f;
			return false;
		break;
	}

	return false;
}

void GuiElementButton::UpdateResizer()
{
	float deltaResolutionWidth  = (float)Window::currentWidth / (float)Window::lastWidth;
	float deltaResolutionHeight = (float)Window::currentHeight / (float)Window::lastHeight;
	width  *= deltaResolutionWidth;
	height *= deltaResolutionHeight;
	x *= deltaResolutionWidth;
	y *= deltaResolutionHeight;
	
	//int deltaLocalWidth  = deltaResolutionWidth  * (float)width;// - width; 
	//int deltaLocalHeight = deltaResolutionHeight * (float)height;// - height; 

	//x = deltaResolutionWidth * x + deltaLocalWidth;
	//y = deltaResolutionHeight * y + deltaLocalHeight;
}		