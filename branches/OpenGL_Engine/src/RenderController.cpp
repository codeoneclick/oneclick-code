#include "RenderController.h"

#include "Game.h"

RenderTexture RenderController::_simpleTexture = RenderTexture(0,SIMPLE_POST_TEXTURE_WIDTH,SIMPLE_POST_TEXTURE_HEIGHT,0,0);
RenderTexture RenderController::_shadowmapTexture = RenderTexture(0,SHADOWMAP_POST_TEXTURE_WIDTH,SHADOWMAP_POST_TEXTURE_HEIGHT,0,0);
RenderTexture RenderController::_reflectionTexture = RenderTexture(0,REFLECTION_POST_TEXTURE_WIDTH,REFLECTION_POST_TEXTURE_HEIGHT,0,0);
RenderTexture RenderController::_refractionTexture = RenderTexture(0,REFRACTION_POST_TEXTURE_WIDTH,REFRACTION_POST_TEXTURE_HEIGHT,0,0);

RenderScreenPlane RenderController::_renderScreenPlane = RenderScreenPlane();

void RenderController::Load()
{
	if(_simpleTexture.textureId == 0)
	{
		glGenTextures(1, &_simpleTexture.textureId);					
		glBindTexture(GL_TEXTURE_2D, _simpleTexture.textureId);		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, _simpleTexture.width, _simpleTexture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		FB::glCreateFB(1,&_simpleTexture.frameBufferId);
		FB::glCreateRB(1,&_simpleTexture.renderBufferId);
		FB::glBindRB(GL_RENDERBUFFER_EXT, _simpleTexture.renderBufferId);
		FB::glAllocRB(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, _simpleTexture.width, _simpleTexture.height);

		FB::glBindFB(GL_FRAMEBUFFER_EXT,_simpleTexture.frameBufferId);
		FB::glBindRB(GL_RENDERBUFFER_EXT,_simpleTexture.renderBufferId);
		FB::glSetRenderBufferFB(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, _simpleTexture.renderBufferId);    
		FB::glSetTextureFB(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, _simpleTexture.textureId, 0);
	}

	if(_reflectionTexture.textureId == 0)
	{
		glGenTextures(1, &_reflectionTexture.textureId);					
		glBindTexture(GL_TEXTURE_2D, _reflectionTexture.textureId);		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, _reflectionTexture.width, _reflectionTexture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		FB::glCreateFB(1,&_reflectionTexture.frameBufferId);
		FB::glCreateRB(1,&_reflectionTexture.renderBufferId);
		FB::glBindRB(GL_RENDERBUFFER_EXT, _reflectionTexture.renderBufferId);
		FB::glAllocRB(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, _reflectionTexture.width, _reflectionTexture.height);

		FB::glBindFB(GL_FRAMEBUFFER_EXT,_reflectionTexture.frameBufferId);
		FB::glBindRB(GL_RENDERBUFFER_EXT,_reflectionTexture.renderBufferId);
		FB::glSetRenderBufferFB(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, _reflectionTexture.renderBufferId);    
		FB::glSetTextureFB(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, _reflectionTexture.textureId, 0);
	}
	if(_refractionTexture.textureId == 0)
	{
		glGenTextures(1, &_refractionTexture.textureId);					
		glBindTexture(GL_TEXTURE_2D, _refractionTexture.textureId);		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, _refractionTexture.width, _refractionTexture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		FB::glCreateFB(1,&_refractionTexture.frameBufferId);
		FB::glCreateRB(1,&_refractionTexture.renderBufferId);
		FB::glBindRB(GL_RENDERBUFFER_EXT, _refractionTexture.renderBufferId);
		FB::glAllocRB(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, _refractionTexture.width, _refractionTexture.height);

		FB::glBindFB(GL_FRAMEBUFFER_EXT,_refractionTexture.frameBufferId);
		FB::glBindRB(GL_RENDERBUFFER_EXT,_refractionTexture.renderBufferId);
		FB::glSetRenderBufferFB(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, _refractionTexture.renderBufferId);    
		FB::glSetTextureFB(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, _refractionTexture.textureId, 0);
	}
	if(_shadowmapTexture.textureId == 0)
	{

	}
}

void RenderController::RenderToTexture(RenderTextureType _type)
{
	switch(_type)
	{
		case RENDER_SIMPLE_TEXTURE :
		{
			_EnableRenderToTexture(&_simpleTexture);
			_Render(RENDER_SIMPLE_TEXTURE);
			_DisableRenderToTexture();
		}
		break;
		case RENDER_REFLECTION_TEXTURE :
		{
			Vector3d vCameraPosition = Core::GetCamera()->vPosition;
			vCameraPosition.y = -Core::GetCamera()->vPosition.y + WATER_LEVEL * 2.0f + 1.5f;

			Vector3d vCameraLookAt = Core::GetCamera()->vLookAt;
			vCameraLookAt.y = -Core::GetCamera()->vLookAt.y + WATER_LEVEL * 2.0f + 1.5f;
		    Core::GetCamera()->mView = MatrixView(vCameraPosition, vCameraLookAt, Vector3d(0.0f,-1.0f,0.0f));

			_EnableRenderToTexture(&_reflectionTexture);
			_Render(RENDER_REFLECTION_TEXTURE);
			_DisableRenderToTexture();

			Core::GetCamera()->mView = MatrixView(Core::GetCamera()->vPosition,Core::GetCamera()->vLookAt,Vector3d(0.0f,1.0f,0.0f));
		}
		break;
		case RENDER_REFRACTION_TEXTURE :
		{
			_EnableRenderToTexture(&_refractionTexture);
			_Render(RENDER_REFRACTION_TEXTURE);
			_DisableRenderToTexture();
		}
		break;
		case RENDER_SHADOWMAP_TEXTURE :
		{
			
		}
		break;
	}
}

unsigned int RenderController::GetRenderTexture(RenderTextureType _type)
{
	switch(_type)
	{
		case RENDER_SIMPLE_TEXTURE :
			return _simpleTexture.textureId;
		break;
		case RENDER_SHADOWMAP_TEXTURE :
			return _shadowmapTexture.textureId;
		break;
		case RENDER_REFLECTION_TEXTURE :
			return _reflectionTexture.textureId;
		break;
	}
}

void RenderController::_OrthoEnable()
{
	glCullFace(GL_BACK);
	glMatrixMode(GL_PROJECTION);		
	glPushMatrix();						
	glLoadIdentity();							
	glOrtho( 0, Window::currentWidth, Window::currentHeight, 0, -1, 1 );		
	glMatrixMode(GL_MODELVIEW);						
	glPushMatrix();								
	glLoadIdentity();
	glDisable( GL_DEPTH_TEST );
	glDepthMask( GL_FALSE );
}

void RenderController::_OrthoDisable()
{
	glMatrixMode( GL_PROJECTION );							
	glPopMatrix();								
	glMatrixMode( GL_MODELVIEW );							
	glPopMatrix();
	glEnable( GL_DEPTH_TEST );
	glDepthMask( GL_TRUE );
}

void RenderController::_RenderScreenPlane(const RenderTexture *textureData)
{			
	_renderScreenPlane.Render();
}

void RenderController::Render(RenderType _type)
{
	switch(_type)
	{
		case RENDER_SIMPLE :
			Game::GetSceneInstance()->Render(RENDER_SIMPLE_TEXTURE);
		break;
		case RENDER_POST :
			_OrthoEnable();
			_RenderScreenPlane(&_simpleTexture);
			Core::GetGuiController()->Render();
			_OrthoDisable();
		break;
	}
}


void RenderController::_EnableRenderToTexture(RenderTexture *textureData)
{
	FB::glBindFB(GL_FRAMEBUFFER_EXT,textureData->frameBufferId);
	FB::glBindRB(GL_RENDERBUFFER_EXT,textureData->renderBufferId);

	glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);

	glClearColor(0.35f, 0.60f, 0.77f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0,0,textureData->width,textureData->height);
}

void RenderController::_EnableRenderToCubeTexture(RenderTexture *textureData, unsigned int cubeSurface)
{

}

void RenderController::_DisableRenderToTexture()
{
	FB::glBindFB(GL_FRAMEBUFFER_EXT,0);
	FB::glBindRB(GL_RENDERBUFFER_EXT,0);
	
	glDrawBuffer(GL_BACK);

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0,0,Window::currentWidth ,Window::currentHeight);
}

void RenderController::_Render(RenderTextureType _type)
{
	if(Game::GetSceneInstance() != NULL)
	{
		Game::GetSceneInstance()->Update(_type);
		Game::GetSceneInstance()->Render(_type);
	}
}