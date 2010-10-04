#include "RenderController.h"
#include "Game.h"
#include "FBExtension.h"

using namespace Video;

CRenderController::SRenderTexture CRenderController::_screenTexture = CRenderController::SRenderTexture(0,0,0,SCREEN_TEXTURE_WIDTH,SCREEN_TEXTURE_HEIGHT);
CRenderController::SRenderTexture CRenderController::_reflectionTexture = CRenderController::SRenderTexture(0,0,0,REFLECTION_TEXTURE_WIDTH,REFLECTION_TEXTURE_HEIGHT);
CRenderController::SRenderTexture CRenderController::_refractionTexture = CRenderController::SRenderTexture(0,0,0,REFRACTION_TEXTURE_WIDTH,REFRACTION_TEXTURE_HEIGHT);
CRenderController::SClipSetting   CRenderController::clipSetting;

void CRenderController::Load()
{
	if(Core::CDevice::GetDeviceType() != Core::CDevice::OGL) return;
	if(_screenTexture.texture_addr == 0)
	{
		glGenTextures(1, &_screenTexture.texture_addr);					
		glBindTexture(GL_TEXTURE_2D, _screenTexture.texture_addr);		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, _screenTexture.width, _screenTexture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		
		Extension::FBExtension::glGenFramebuffersEXT(1,&_screenTexture.frame_buffer_addr);
		Extension::FBExtension::glGenRenderbuffersEXT(1,&_screenTexture.render_buffer_addr);
		Extension::FBExtension::glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, _screenTexture.render_buffer_addr);
		Extension::FBExtension::glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, _screenTexture.width, _screenTexture.height);

		Extension::FBExtension::glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,_screenTexture.frame_buffer_addr);
		Extension::FBExtension::glBindRenderbufferEXT(GL_RENDERBUFFER_EXT,_screenTexture.render_buffer_addr);
		Extension::FBExtension::glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, _screenTexture.render_buffer_addr);    
		Extension::FBExtension::glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, _screenTexture.texture_addr, 0);
	}

	if(_reflectionTexture.texture_addr == 0)
	{
		glGenTextures(1, &_reflectionTexture.texture_addr);					
		glBindTexture(GL_TEXTURE_2D, _reflectionTexture.texture_addr);		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, _reflectionTexture.width, _reflectionTexture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		
		Extension::FBExtension::glGenFramebuffersEXT(1,&_reflectionTexture.frame_buffer_addr);
		Extension::FBExtension::glGenRenderbuffersEXT(1,&_reflectionTexture.render_buffer_addr);
		Extension::FBExtension::glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, _reflectionTexture.render_buffer_addr);
		Extension::FBExtension::glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, _reflectionTexture.width, _reflectionTexture.height);

		Extension::FBExtension::glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,_reflectionTexture.frame_buffer_addr);
		Extension::FBExtension::glBindRenderbufferEXT(GL_RENDERBUFFER_EXT,_reflectionTexture.render_buffer_addr);
		Extension::FBExtension::glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, _reflectionTexture.render_buffer_addr);    
		Extension::FBExtension::glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, _reflectionTexture.texture_addr, 0);
	}

	if(_refractionTexture.texture_addr == 0)
	{
		glGenTextures(1, &_refractionTexture.texture_addr);					
		glBindTexture(GL_TEXTURE_2D, _refractionTexture.texture_addr);		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, _refractionTexture.width, _refractionTexture.height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		
		Extension::FBExtension::glGenFramebuffersEXT(1,&_refractionTexture.frame_buffer_addr);
		Extension::FBExtension::glGenRenderbuffersEXT(1,&_refractionTexture.render_buffer_addr);
		Extension::FBExtension::glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, _refractionTexture.render_buffer_addr);
		Extension::FBExtension::glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, _refractionTexture.width, _refractionTexture.height);

		Extension::FBExtension::glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,_refractionTexture.frame_buffer_addr);
		Extension::FBExtension::glBindRenderbufferEXT(GL_RENDERBUFFER_EXT,_refractionTexture.render_buffer_addr);
		Extension::FBExtension::glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, _refractionTexture.render_buffer_addr);    
		Extension::FBExtension::glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, _refractionTexture.texture_addr, 0);
	}

	clipSetting.fClipInc = 0.0f;
	clipSetting.fClipHeight = 0.0f;

	Extension::FBExtension::glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,0);
	Extension::FBExtension::glBindRenderbufferEXT(GL_RENDERBUFFER_EXT,0);
}

void CRenderController::_TextureEnable(Video::CRenderController::SRenderTexture *texture)
{
	Extension::FBExtension::glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,texture->frame_buffer_addr);
	Extension::FBExtension::glBindRenderbufferEXT(GL_RENDERBUFFER_EXT,texture->render_buffer_addr);
	glDrawBuffer(GL_COLOR_ATTACHMENT0_EXT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0,0,texture->width,texture->height);
}

void CRenderController::_TextureDisable()
{
	Extension::FBExtension::glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,0);
	Extension::FBExtension::glBindRenderbufferEXT(GL_RENDERBUFFER_EXT,0);
	glDrawBuffer(GL_BACK);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0,0,Core::CWindow::m_Width ,Core::CWindow::m_Height);
}

void CRenderController::Render2Texture(Video::CRenderController::ERenderTexture value)
{
	switch(value)
	{
		case CRenderController::SCREEN_TEXTURE :
		{
			//clipSetting.fClipInc = 0.0f;
			//clipSetting.fClipHeight = 0.0f;

			//_TextureEnable(&_screenTexture);
			Game::GetEnviromentControllerInstance()->Update(0);
			Game::GetEnviromentControllerInstance()->Render(value);
			//_TextureDisable();
		}
		break;
		case CRenderController::REFLECTION_TEXTURE :
		{
			clipSetting.fClipInc = -1.0f;
			clipSetting.fClipHeight = -64.0f;
			float waterLevel = -64.0f;
			Enviroment::Camera *cameraPtr = Game::GetEnviromentControllerInstance()->GetCameraInstance();

			math::Vector3d vCameraPosition = cameraPtr->vPosition;
			vCameraPosition.y = -cameraPtr->vPosition.y + waterLevel * 2.0f;

			math::Vector3d vCameraLookAt = cameraPtr->vLookAt;
			vCameraLookAt.y = -cameraPtr->vLookAt.y + waterLevel * 2.0f;
			cameraPtr->mView = math::MatrixView(vCameraPosition, vCameraLookAt, math::Vector3d(0.0f,-1.0f,0.0f));

			_TextureEnable(&_reflectionTexture);
			Game::GetEnviromentControllerInstance()->Update(1);
			Game::GetEnviromentControllerInstance()->Render(value);
			_TextureDisable();

			cameraPtr->mView = math::MatrixView(cameraPtr->vPosition,cameraPtr->vLookAt, math::Vector3d(0.0f,1.0f,0.0f));
		}
		break;
		case CRenderController::REFRACTION_TEXTURE :
		{
			clipSetting.fClipInc = 1.0f;
			clipSetting.fClipHeight = -64.0f;

			_TextureEnable(&_refractionTexture);
			Game::GetEnviromentControllerInstance()->Update(1);
			Game::GetEnviromentControllerInstance()->Render(value);
			_TextureDisable();
		}
		break;
	}
}

const unsigned int CRenderController::GetRenderTexture(Video::CRenderController::ERenderTexture value)
{
	switch(value)
	{
		case CRenderController::SCREEN_TEXTURE :
		{
			return _screenTexture.texture_addr;
		}
		break;
		case CRenderController::REFLECTION_TEXTURE :
		{
			return _reflectionTexture.texture_addr;
		}
		break;
		case CRenderController::REFRACTION_TEXTURE :
		{
			return _refractionTexture.texture_addr;
		}
		break;
	}
	return NULL;
}

void CRenderController::Render()
{
	glMatrixMode(GL_PROJECTION);						
	glLoadIdentity();							
	glOrtho( 0, Core::CWindow::m_Width, Core::CWindow::m_Height, 0, -1, 1 );		
	glMatrixMode(GL_MODELVIEW);												
	glLoadIdentity();
	glDisable( GL_DEPTH_TEST );
	glEnable(GL_TEXTURE_2D);	
	glBindTexture(GL_TEXTURE_2D,_screenTexture.texture_addr);	
	glBegin(GL_QUADS);	

		glTexCoord2f ( 0.0f, 1.0f );
        glVertex2f   ( 0.0f, 0.0f );

        glTexCoord2f ( 0.0f, 0.0f );
        glVertex2f   ( 0.0f, static_cast<float>(Core::CWindow::m_Height) );

        glTexCoord2f ( 1.0f, 0.0f );
        glVertex2f   ( static_cast<float>(Core::CWindow::m_Width), static_cast<float>(Core::CWindow::m_Height) );

        glTexCoord2f ( 1.0f, 1.0f );
        glVertex2f   ( static_cast<float>(Core::CWindow::m_Width), 0.0f);

	glEnd();
	glEnable( GL_DEPTH_TEST );
}