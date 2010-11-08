#include "RenderController.h"
#include "Game.h"
#include "Core/CGlobal.h"

using namespace Video;

std::map<CRenderController::E_VIEWPORT,Enviroment::Camera*> CRenderController::m_Camera;
std::map<CRenderController::E_VIEWPORT,CRenderController::SViewportSetting*> CRenderController::m_ViewportSetting;

void CRenderController::Init()
{
	SViewportSetting *topSetting = new SViewportSetting();
	topSetting->m_X = 0;
	topSetting->m_Y = 0;
	topSetting->m_Width = 400;
	topSetting->m_Height = 300;
	topSetting->m_FillMode = CRenderController::E_FILLMODE::MODE_WIREFRAME;

	SViewportSetting *frontSetting = new SViewportSetting();
	frontSetting->m_X = 400;
	frontSetting->m_Y = 0;
	frontSetting->m_Width = 400;
	frontSetting->m_Height = 300;
	frontSetting->m_FillMode = CRenderController::E_FILLMODE::MODE_WIREFRAME;

	SViewportSetting *leftSetting = new SViewportSetting();
	leftSetting->m_X = 0;
	leftSetting->m_Y = 300;
	leftSetting->m_Width = 400;
	leftSetting->m_Height = 300;
	leftSetting->m_FillMode = CRenderController::E_FILLMODE::MODE_WIREFRAME;

	SViewportSetting *perspectiveSetting = new SViewportSetting();
	perspectiveSetting->m_X = 400;
	perspectiveSetting->m_Y = 300;
	perspectiveSetting->m_Width = 400;
	perspectiveSetting->m_Height = 300;
	perspectiveSetting->m_FillMode = CRenderController::E_FILLMODE::MODE_SOLID;

	m_ViewportSetting[E_VIEWPORT::VIEWPORT_TOP] = topSetting;
	m_ViewportSetting[E_VIEWPORT::VIEWPORT_LEFT] = leftSetting;
	m_ViewportSetting[E_VIEWPORT::VIEWPORT_FRONT] = frontSetting;
	m_ViewportSetting[E_VIEWPORT::VIEWPORT_PERSPECTIVE] = perspectiveSetting;
}

void CRenderController::TextureEnable()
{

}

void CRenderController::TextureDisable()
{

}

void CRenderController::RenderViewport(E_VIEWPORT _value)
{
	int x = m_ViewportSetting[_value]->m_X;
	int y = m_ViewportSetting[_value]->m_Y;
	unsigned int width  = m_ViewportSetting[_value]->m_Width;
	unsigned int height = m_ViewportSetting[_value]->m_Height;
	Core::CGlobal::GetDevice()->SetViewport(x,y,width,height);
	switch(m_ViewportSetting[_value]->m_FillMode)
	{
		case CRenderController::E_FILLMODE::MODE_SOLID :
			Core::CGlobal::GetDevice()->Ref()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);	
		break;
		case CRenderController::E_FILLMODE::MODE_WIREFRAME :
			Core::CGlobal::GetDevice()->Ref()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);	
		break;
	}
	Game::GetEnviromentControllerInstance()->Update(0);
	Game::GetEnviromentControllerInstance()->Render();
}

void CRenderController::Render2Texture()
{
	
}

void CRenderController::Render()
{
	RenderViewport(E_VIEWPORT::VIEWPORT_TOP);
	RenderViewport(E_VIEWPORT::VIEWPORT_LEFT);
	RenderViewport(E_VIEWPORT::VIEWPORT_FRONT);
	RenderViewport(E_VIEWPORT::VIEWPORT_PERSPECTIVE);
}