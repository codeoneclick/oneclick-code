#ifndef ENVIROMENTCONTROLLER_H
#define ENVIROMENTCONTROLLER_H

#include "../../Core/Camera.h"
#include "../Enviroment/Landscape.h"
#include "../Enviroment/Model.h"
#include "../Enviroment/Ocean.h"
#include "../Enviroment/Grass.h"
#include "../Enviroment/SkySphere.h"
#include "RenderController.h"
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
	Camera* m_Camera;
	CDummy* m_CharacterControl;
	CDummy* m_Landscape;
	CDummy* m_Ocean;
	CDummy* m_Grass;
	CDummy* m_Sky;
	float GetLandscapeHeight(float _fPosition_x,float _fPosition_z);
	math::Vector3d GetLandscapeRotation(math::Vector3d _vPosition);
	float GetRotationFromNormal(math::Vector3d _vPosition_01,math::Vector3d _vPosition_02);
public :
	EnviromentController();
	void Load();
	__forceinline Camera* GetCameraInstance() { return m_Camera; }
	void Update(DWORD time);
	void Render(Video::CRenderController::ERenderTexture _value);
};
};

#endif