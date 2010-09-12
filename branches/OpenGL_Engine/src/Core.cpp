#include "Core.h"

Camera* Core::_camera = 0;
bool Core::_cameraSingleFlag = false;

Camera* Core::GetCamera()
{
	if(!_cameraSingleFlag)
	{
		_camera = new Camera();
		_cameraSingleFlag = true;
		return _camera;
	}
	else
		return _camera;
}

GuiController* Core::_guiController = NULL;
bool Core::_guiControllerSingleFlag = false;

GuiController* Core::GetGuiController()
{
	if(!_guiControllerSingleFlag)
	{
		_guiController = new GuiController();
		_guiControllerSingleFlag = true;
		return _guiController;
	}
	else
		return _guiController;
}