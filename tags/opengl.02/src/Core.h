#ifndef _CORE_H_
#define _CORE_H_
#include "Camera.h"
#include "GuiController.h"
#include "Resource.h"

class Core
{
	private:
		static Camera* _camera;
		static bool _cameraSingleFlag;

		static GuiController* _guiController;
		static bool _guiControllerSingleFlag;
	public:
		static Camera* GetCamera();
		static GuiController *GetGuiController();
};
#endif