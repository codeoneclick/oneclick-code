#include "Ocean.h"
#include "Resource.h"
#include "Game.h"

using namespace Enviroment;

COcean::COcean()
{
	_width  = 256 * 4;
	_height = 256 * 4;
	m_vPosition.y = -64.0f;
}

void COcean::Load(std::string value)
{
	//_textures[0] = Resource::GetTextureControllerInstance()->Load("Content\\textures\\water.dds",type::STexture::_DDS);
	//_shader->Create("reflection");
}

void COcean::Update()
{
	Matrix();
}

void COcean::Render()
{
	bool _shaderRender = true;
	if(_shaderRender)
	{
		//_shader->Enable();
		//_shader->SetWVPMatrix(_mWorldViewProjection);
		//_shader->SetWMatrix(_mWorld);
		//_shader->SetTexture(0,Video::CRenderController::GetRenderTexture(Video::CRenderController::ERenderTexture::REFLECTION_TEXTURE));
		//_shader->SetTexture(2,Video::CRenderController::GetRenderTexture(Video::CRenderController::ERenderTexture::REFRACTION_TEXTURE));
		//_shader->SetTexture(1,_textures[0]->addr_ptr);
		// ***** DEBUG LIGHT ***** //
		math::Vector3d vCameraPosition = Game::GetEnviromentControllerInstance()->GetCameraInstance()->vPosition;
		static math::Vector4d vLightPosition;
		math::Vector3d vColor = math::Vector3d(1.0f,0.0f,0.0f);
		static float fAngle = 0.0f;
		fAngle += 0.01f;
		vLightPosition.x = vCameraPosition.x + cos(fAngle) * 32.0f;
		vLightPosition.y = vCameraPosition.y;
		vLightPosition.z = vCameraPosition.z + sin(fAngle) * 32.0f;
		vLightPosition.w = 32.0f;
		//_shader->SetLight_01(vLightPosition,vColor);
		//_shader->SetCamera(vCameraPosition);
		//_shader->UpdateTimer();
		// ***** DEBUG LIGHT ***** //
		glBegin(GL_QUADS);	
			glTexCoord2f ( 0.0f, 0.0f );
		    glVertex3f   ( 0.0f, 0.0f, static_cast<float>(_height) );

			glTexCoord2f ( 0.0f, 1.0f );
			glVertex3f   ( 0.0f, 0.0f, 0.0f );

			glTexCoord2f ( 1.0f, 1.0f );
			glVertex3f   ( static_cast<float>(_width), 0.0f, 0.0f );
			
			glTexCoord2f ( 1.0f, 0.0f );
			glVertex3f   ( static_cast<float>(_width), 0.0f, static_cast<float>(_height) );

		glEnd();
		//_shader->Disable();
	}
}