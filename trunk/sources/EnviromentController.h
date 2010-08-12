#ifndef _ENVIROMENTCONTROLLER_H_
#define _ENVIROMENTCONTROLLER_H_
#include "Camera.h"
#include "Landscape.h"
#include "Model.h"
#include "RenderController.h"
#include "Ocean.h"

namespace Enviroment
{
class EnviromentController
{
private :
	Camera* _camera;
	Landscape* _landscape;
	CModel *_mesh;
	COcean *_ocean;
public :
	EnviromentController();
	Landscape* LoadLandscape(char* filename, unsigned int width, unsigned int height);
	void Create();
	__forceinline Camera* GetCameraInstance() { return _camera; }
	__forceinline Landscape* GetLandscapeInstance() { return _landscape; }
	void Update(DWORD time);
	void Render(Video::CRenderController::ERenderTexture value);
};
};

#endif