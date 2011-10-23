#include "m3_GUIService.h"

m3_GUIService::m3_GUIService()
{
}

void m3_GUIService::AddMenu(std::string _menuName, std::vector<m3_GUIEntity*> _GUIElementsContainer)
{
	std::map<std::string,std::vector<m3_GUIEntity*>>::iterator menuIterator = _GUIMenusContainer.find(_menuName);
	if(menuIterator == _GUIMenusContainer.end())
		_GUIMenusContainer[_menuName] = _GUIElementsContainer;
}

void m3_GUIService::Update()
{
	std::map<std::string,std::vector<m3_GUIEntity*>>::iterator menuIterator = _GUIMenusContainer.find(_currentMenu);
	if(menuIterator != _GUIMenusContainer.end())
	{
		std::vector<m3_GUIEntity*>::iterator _elementsIterator = menuIterator->second.begin();
		while(_elementsIterator != menuIterator->second.end())
		{
			(*_elementsIterator)->Update();
			_elementsIterator++;
		}
	}
}

void m3_GUIService::Render()
{
	std::map<std::string,std::vector<m3_GUIEntity*>>::iterator menuIterator = _GUIMenusContainer.find(_currentMenu);
	if(menuIterator != _GUIMenusContainer.end())
	{
		std::vector<m3_GUIEntity*>::iterator _elementsIterator = menuIterator->second.begin();
		while(_elementsIterator != menuIterator->second.end())
		{
			if((*_elementsIterator)->visible)
				(*_elementsIterator)->Render();
			_elementsIterator++;
		}
	}
}

void m3_GUIService::CheckCollision()
{
	std::map<std::string,std::vector<m3_GUIEntity*>>::iterator menuIterator = _GUIMenusContainer.find(_currentMenu);
	if(menuIterator != _GUIMenusContainer.end())
	{
		std::vector<m3_GUIEntity*>::iterator _elementsIterator = menuIterator->second.begin();
		while(_elementsIterator != menuIterator->second.end())
		{
			if((*_elementsIterator)->visible)
				if((*_elementsIterator)->CheckCollision(m3_Input::mCurrentPosition.x,m3_Input::mCurrentPosition.y,m3_Input::mLeftClick))
				{
					m3_Input::mLeftClick = false;
					_currentCommand = (*_elementsIterator)->command;
					return;
				}
			_elementsIterator++;
		}
	}
}