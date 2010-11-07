#ifndef _ENVIROMENTCONTROLLER_H_
#define _ENVIROMENTCONTROLLER_H_
#include "Camera.h"
#include "Model.h"
#include "RenderController.h"
#include "Ocean.h"
#include "SoaringIsland.h"

namespace Enviroment
{
class EnviromentController
{
private :
	Camera* _camera;
	CDummy* m_Island;
	CModel *_mesh;
	COcean *_ocean;
public :
	EnviromentController();
	void Create();
	__forceinline Camera* GetCameraInstance() { return _camera; }
	void Update(DWORD time);
	void Render(Video::CRenderController::ERenderTexture value);
};
};

#endif