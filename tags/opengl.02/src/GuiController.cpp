#include "GuiController.h"
#include "Input.h"

GuiController::GuiController()
{

}

void GuiController::AddMenu(std::string _menuName, GuiMenuDummy *_menu)
{
	std::map<std::string,GuiMenuDummy*>::iterator menuIterator = _menusContainer.find(_menuName);
	if(menuIterator == _menusContainer.end())
		_menusContainer[_menuName] = _menu;
}

void GuiController::Update()
{
	std::map<std::string, GuiMenuDummy*>::iterator menuIterator = _menusContainer.find(_currentMenu);
	if(menuIterator != _menusContainer.end())
	{
		(*menuIterator).second->OnEvent();
		std::vector<GuiElementDummy*>::iterator _elementsIterator = menuIterator->second->_elementsContainer.begin();
		while(_elementsIterator != menuIterator->second->_elementsContainer.end())
		{
			if((*_elementsIterator)->visible == true)
				(*_elementsIterator)->Update();
			_elementsIterator++;
		}
	}
}

void GuiController::Render()
{
	std::map<std::string, GuiMenuDummy*>::iterator menuIterator = _menusContainer.find(_currentMenu);
	if(menuIterator != _menusContainer.end())
	{
		std::vector<GuiElementDummy*>::iterator _elementsIterator = menuIterator->second->_elementsContainer.begin();
		while(_elementsIterator != menuIterator->second->_elementsContainer.end())
		{
			if((*_elementsIterator)->visible == true)
				(*_elementsIterator)->Render();
			_elementsIterator++;
		}
	}
}

void GuiController::Resize()
{
	std::map<std::string, GuiMenuDummy*>::iterator menuIterator = _menusContainer.find(_currentMenu);
	if(menuIterator != _menusContainer.end())
	{
		std::vector<GuiElementDummy*>::iterator _elementsIterator = menuIterator->second->_elementsContainer.begin();
		while(_elementsIterator != menuIterator->second->_elementsContainer.end())
		{
			if((*_elementsIterator)->visible == true)
				(*_elementsIterator)->UpdateResizer();
			_elementsIterator++;
		}
	}
}

void GuiController::CheckCollision()
{
	std::map<std::string, GuiMenuDummy*>::iterator menuIterator = _menusContainer.find(_currentMenu);
	if(menuIterator != _menusContainer.end())
	{
		std::vector<GuiElementDummy*>::iterator _elementsIterator = menuIterator->second->_elementsContainer.begin();
		while(_elementsIterator != menuIterator->second->_elementsContainer.end())
		{
			if((*_elementsIterator)->visible)
				if((*_elementsIterator)->CheckCollision(Input::mCurrentPosition.x,Input::mCurrentPosition.y,Input::mLeftClick))
				{
					Input::mLeftClick = false;
					_currentCommand = (*_elementsIterator)->command;
					return;
				}
			_elementsIterator++;
		}
	}
}

void GuiController::ShowControl(std::string _name, SlideState _state)
{
	std::map<std::string, GuiMenuDummy*>::iterator menuIterator = _menusContainer.find(_currentMenu);
	if(menuIterator != _menusContainer.end())
	{
		std::vector<GuiElementDummy*>::iterator _elementsIterator = menuIterator->second->_elementsContainer.begin();
		while(_elementsIterator != menuIterator->second->_elementsContainer.end())
		{
			if((*_elementsIterator)->command == _name)
			{
				(*_elementsIterator)->visible = true;
				(*_elementsIterator)->Show(_state);
				return;
			}
			_elementsIterator++;
		}
	}
}

void GuiController::HideControl(std::string _name)
{
	std::map<std::string, GuiMenuDummy*>::iterator menuIterator = _menusContainer.find(_currentMenu);
	if(menuIterator != _menusContainer.end())
	{
		std::vector<GuiElementDummy*>::iterator _elementsIterator = menuIterator->second->_elementsContainer.begin();
		while(_elementsIterator != menuIterator->second->_elementsContainer.end())
		{
			if((*_elementsIterator)->command == _name)
			{
				(*_elementsIterator)->Hide();
				return;
			}
			_elementsIterator++;
		}
	}
} 

void GuiController::HideAllControl()
{
	std::map<std::string, GuiMenuDummy*>::iterator menuIterator = _menusContainer.find(_currentMenu);
	if(menuIterator != _menusContainer.end())
	{
		std::vector<GuiElementDummy*>::iterator _elementsIterator = menuIterator->second->_elementsContainer.begin();
		while(_elementsIterator != menuIterator->second->_elementsContainer.end())
		{
			(*_elementsIterator)->Hide();
			_elementsIterator++;
		}
	}
} 