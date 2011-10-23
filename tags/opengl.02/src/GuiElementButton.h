#ifndef _GUIELEMENTBUTTON_H_
#define _GUIELEMENTBUTTON_H_

#define BUTTONPRESSDELAY_FPS 15

#include "GuiElementDummy.h"

enum BtnState { BUTTON_NONE = 0, BUTTON_ON_MOUSE, BUTTON_PRESS, BUTTON_DISABLE };

class GuiElementButton : public GuiElementDummy
{
	private:
		unsigned int _buttonDelay;
		BtnState     _buttonFlag;
	public:
		GuiElementButton();
		virtual void UpdateResizer();
		virtual bool CheckCollision(float mouseX, float mouseY, bool press);
};

#endif