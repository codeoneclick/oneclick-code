#include "RenderController.h"
#include "../Game.h"

using namespace Video;

std::map<CRenderController::ERenderTexture,Core::ITexture*> CRenderController::m_RenderTargetTextureContainer;

void CRenderController::Init()
{
	m_RenderTargetTextureContainer[CRenderController::REFLECTION_TEXTURE] = Core::CGlobal::GetDevice()->CreateTexture();
	m_RenderTargetTextureContainer[CRenderController::REFLECTION_TEXTURE]->SetAsRenderTarget(512,512);
	m_RenderTargetTextureContainer[CRenderController::REFRACTION_TEXTURE] = Core::CGlobal::GetDevice()->CreateTexture();
	m_RenderTargetTextureContainer[CRenderController::REFRACTION_TEXTURE]->SetAsRenderTarget(512,512);
}

void CRenderController::TextureEnable()
{

}

void CRenderController::TextureDisable()
{

}

void CRenderController::Render2Texture(Video::CRenderController::ERenderTexture value)
{
	switch(value)
	{
		case CRenderController::SCREEN_TEXTURE :
		{
			
		}
		break;
		case CRenderController::REFLECTION_TEXTURE :
		{
			Core::CGlobal::GetDevice()->BeginRenderTarget(m_RenderTargetTextureContainer[value]);
			Game::GetEnviromentControllerInstance()->Update(1);
			Game::GetEnviromentControllerInstance()->Render(value);
			Core::CGlobal::GetDevice()->EndRenderTarget();

			//if( ::GetAsyncKeyState('T') & 0x8000f )
			//	D3DXSaveTextureToFile("C:\\temp.png",D3DXIFF_PNG,((Core::CTextureD3D*)m_RenderTargetTextureContainer[value])->m_addr,NULL);
		}
		break;
		case CRenderController::REFRACTION_TEXTURE :
		{
			Core::CGlobal::GetDevice()->BeginRenderTarget(m_RenderTargetTextureContainer[value]);
			Game::GetEnviromentControllerInstance()->Update(2);
			Game::GetEnviromentControllerInstance()->Render(value);
			Core::CGlobal::GetDevice()->EndRenderTarget();

			if( ::GetAsyncKeyState('T') & 0x8000f )
				D3DXSaveTextureToFile("C:\\temp.png",D3DXIFF_PNG,((Core::CTextureD3D*)m_RenderTargetTextureContainer[value])->m_addr,NULL);
		}
		break;
	}
}

void CRenderController::Render(Video::CRenderController::ERenderTexture value)
{
	Core::CGlobal::GetDevice()->BeginRender();
	Game::GetEnviromentControllerInstance()->Update(0);
	Game::GetEnviromentControllerInstance()->Render(value);
	Core::CGlobal::GetDevice()->EndRender();
}

void CRenderController::RenderPost()
{

}