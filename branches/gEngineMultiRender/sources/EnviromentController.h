#ifndef ENVIROMENTCONTROLLER_H
#define ENVIROMENTCONTROLLER_H
#include "Camera.h"
#include "Landscape.h"
#include "Model.h"
#include "RenderController.h"
#include "Ocean.h"
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
    std::map<std::string,CDummy*> m_ModelContainer;
	Camera* m_Camera;
	CDummy* m_CharacterControl;
	CDummy* m_Landscape;
	float GetLandscapeHeight(float _positionX,float _positionZ);
	math::Vector3d GetLandscapeRotation(math::Vector3d vPosition);
	float GetRotationFromNormal(math::Vector3d vPosition_01,math::Vector3d vPosition_02);
public :
	EnviromentController();
	void Load();
	__forceinline Camera* GetCameraInstance() { return m_Camera; }
	void Update(DWORD time);
	void Render(Video::CRenderController::ERenderTexture value);
};
};

#endif