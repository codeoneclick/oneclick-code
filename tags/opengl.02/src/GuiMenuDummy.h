#ifndef _GUIMENUDUMMY_H_
#define _GUIMENUDUMMY_H_

#include <vector>
#include "GuiElementDummy.h"
#include "GuiElementButton.h"

class GuiMenuDummy
{
protected :

public :
	std::vector<GuiElementDummy*> _elementsContainer;
	GuiMenuDummy();
	virtual void Load(std::string name) = 0;
	virtual void OnEvent() = 0;
};

#endif