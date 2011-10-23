#ifndef ENVIROMENTCONTROLLER_H
#define ENVIROMENTCONTROLLER_H

#include "../../Core/Camera.h"
#include "../../Core/CLight.h"
#include "../Enviroment/Landscape.h"
#include "../Enviroment/Model.h"
#include "../Enviroment/Ocean.h"
#include "../Enviroment/Grass.h"
#include "../Enviroment/CSkyDome.h"
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
    std::map<std::string, Camera*> m_CameraContainer;
	std::map<std::string, CLight*> m_LightContainer;
    std::map<std::string, CDummy*> m_LandscapeContainer;
	std::map<std::string, CDummy*> m_OceanContainer;
    std::map<std::string, CDummy*> m_ModelContainer;
	CharacterController* m_characterController;
	Camera* m_Camera;
	CLight* m_Light;
	CDummy* m_Character;
	CDummy* m_Landscape;
	CDummy* m_Ocean;
	CDummy* m_Grass;
	CDummy* m_Sky;
public :
	EnviromentController();
	void Load();
	__forceinline Camera* GetCameraInstance() { return m_Camera; }
	__forceinline CLight* GetLightInstance() { return m_Light; }
	void Update(DWORD time);
	void Render(Video::CRenderController::ERenderTexture _value);
};
};

#endif