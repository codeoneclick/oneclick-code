#include "RenderController.h"
#include "Game.h"
#include "FBExtension.h"

using namespace Video;


void CRenderController::Init()
{
	
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
	}
}

void CRenderController::Render(Video::CRenderController::ERenderTexture value)
{
	Game::GetEnviromentControllerInstance()->Update(0);
	Game::GetEnviromentControllerInstance()->Render(value);
}

void CRenderController::RenderPost()
{

}