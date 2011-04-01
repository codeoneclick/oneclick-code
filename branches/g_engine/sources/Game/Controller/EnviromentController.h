#ifndef ENVIROMENTCONTROLLER_H
#define ENVIROMENTCONTROLLER_H

#include "../../Core/Camera.h"
#include "../Enviroment/Landscape.h"
#include "../Enviroment/Model.h"
#include "../Enviroment/Ocean.h"
#include "../Enviroment/Grass.h"
#include "../Enviroment/SkySphere.h"
#include "RenderController.h"
#include "CharacterController.h"
#include <stdlib.h>
#include <string>
#include <map>

namespace Enviroment
{
class EnviromentController
{
private :
    std::map<std::string,Camera*> m_CameraContainer;
    std::map<std::string,CDummy*> m_LandscapeContainer;
	std::map<std::string,CDummy*> m_OceanContainer;
    std::map<std::string,CDummy*> m_ModelContainer;
	CharacterController* m_characterController;
	Camera* m_Camera;
	CDummy* m_Character;
	CDummy* m_Landscape;
	CDummy* m_Ocean;
	CDummy* m_Grass;
	CDummy* m_Sky;
public :
	EnviromentController();
	void Load();
	__forceinline Camera* GetCameraInstance() { return m_Camera; }
	void Update(DWORD time);
	void Render(Video::CRenderController::ERenderTexture _value);
};
};

#endif