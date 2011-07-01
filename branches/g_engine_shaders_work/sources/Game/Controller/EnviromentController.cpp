#include "EnviromentController.h"
#include "../../Resource/Manager/Resource.h"

using namespace Enviroment;

EnviromentController::EnviromentController()
{
	m_Camera = NULL;
	m_Light = NULL;
	m_Character = NULL;
	m_Landscape = NULL;
	m_Grass = NULL;
	m_intersectController = NULL;
}

void EnviromentController::Load()
{
	m_CameraContainer["MainCamera"] = new Camera(); 
	m_Camera = m_CameraContainer["MainCamera"];

	m_LightContainer["MainLight"] = new CLight();
	m_Light = m_LightContainer["MainLight"];

	m_intersectController = new CIntersectController();

	std::vector<SResource> landscapeResourceContainer;
	SResource landscapeResource;
	landscapeResource.m_ResouceFile = "Content\\maps\\Kbsd_Heightmap_Example.raw";
	landscapeResource.m_ShaderFile = "Content\\shaders\\basic";
	landscapeResource.m_TextureFileList[0] = "Content\\textures\\sand.dds";
	landscapeResource.m_TextureFileList[1] = "Content\\textures\\road.dds";
	landscapeResource.m_TextureFileList[2] = "Content\\textures\\road.dds";
	landscapeResource.m_TextureFileList[3] = "Content\\textures\\sand_nh.dds";
	landscapeResource.m_TextureFileList[4] = "Content\\textures\\road_nh.dds";
	landscapeResource.m_TextureFileList[5] = "Content\\textures\\road_nh.dds";
	landscapeResource.m_TextureFileList[6] = "Content\\textures\\grid_mask.dds";
	landscapeResourceContainer.push_back(landscapeResource);

	m_LandscapeContainer["landscape_01"] = new CLandscape();	
	m_LandscapeContainer["landscape_01"]->Load(landscapeResourceContainer);
	m_Landscape = m_LandscapeContainer["landscape_01"];

	std::vector<SResource> oceanResourceContainer;
	m_OceanContainer["ocean_01"] = new COcean((CLandscape*)m_Landscape);
	m_OceanContainer["ocean_01"]->Load(oceanResourceContainer);
	m_Ocean = m_OceanContainer["ocean_01"];

	std::vector<SResource> grassResourceContainer;
	SResource grassResource;
	grassResource.m_ResouceFile = "Content\\maps\\Kbsd_Heightmap_Example.raw";
	grassResource.m_ShaderFile = "Content\\shaders\\grass";
	grassResource.m_TextureFileList[0] = "Content\\textures\\grass_v1_basic_tex.dds";
	grassResourceContainer.push_back(grassResource);
	m_Grass = new CGrass();
	m_Grass->Load(grassResourceContainer);

	std::vector<SResource> skyResourceContainer;
	SResource skyResource;
	skyResource.m_ShaderFile = "Content\\shaders\\sky";
	skyResource.m_TextureFileList[0] = "Content\\textures\\skyday.dds";
	skyResource.m_TextureFileList[1] = "Content\\textures\\skynight.dds";
	skyResource.m_TextureFileList[2] = "Content\\textures\\sunset.dds";
	skyResourceContainer.push_back(skyResource);
	m_Sky = new CSkyDome();
	m_Sky->Load(skyResourceContainer);

	std::vector<SResource> modelResourceContainer;
	SResource modelNodeResource;

	modelNodeResource.m_ResouceFile = "Content\\models\\Autoturret.m3";
	modelNodeResource.m_Extension = Core::CMesh::EXT_M3;
	modelNodeResource.m_ShaderFile = "Content\\shaders\\basic_02";
	modelNodeResource.m_TextureFileList[0] = "Content\\textures\\autoturret_diffuse.dds";
	modelNodeResource.m_TextureFileList[1] = "Content\\textures\\tank_diffuse_nh.dds";
	modelResourceContainer.push_back(modelNodeResource);

	m_ModelContainer["model_01"] = new CModel();
    m_ModelContainer["model_01"]->Load(modelResourceContainer);
	//m_ModelContainer["model_01"]->m_vRotation.x = -1.57f;
	m_ModelContainer["model_01"]->m_vScale = math::Vector3d(2.04f,2.04f,2.04f);

	m_Character = m_ModelContainer["model_01"];

	m_characterController = new CharacterController(m_Camera,m_Character,m_Landscape);

	CResource::Enable();
}

void EnviromentController::Update(Video::CRenderController::ERenderTexture _value)
{
	switch(_value)
	{
		case Video::CRenderController::SCREEN_TEXTURE :
		{
			m_Camera->Update();
			m_Light->Update();

			std::map<std::string,CDummy*>::iterator cOcean = m_OceanContainer.begin();
			while(cOcean != m_OceanContainer.end())
			{
				cOcean->second->Update();
				cOcean++;
			}

			m_Sky->m_vPosition = m_Camera->vPosition;
			m_Sky->m_vPosition.y = m_Camera->vPosition.y - ((CSkyDome*)m_Sky)->GetSkyHeight() - 0.17f;
			m_Sky->Update();

			m_characterController->Update(0);
			//m_intersectController->Update();
		}
		break;
		case Video::CRenderController::REFLECTION_TEXTURE :
		{
			math::Vector3d vCameraPosition = m_Camera->vPosition;
			math::Vector3d vCameraLookAt = m_Camera->vLookAt;
			vCameraPosition.y = -m_Camera->vPosition.y  + m_Ocean->m_vPosition.y * 2.0f + 0.16f;
			vCameraLookAt.y = -m_Camera->vLookAt.y + m_Ocean->m_vPosition.y * 2.0f + 0.16f;
			m_Camera->mView = math::MatrixView(vCameraPosition, vCameraLookAt, math::Vector3d(0.0f,-1.0f,0.0f));
			Core::CGlobal::GetDevice()->EnableClipPlane(0, math::Vector3d(0.0f,m_Ocean->m_vPosition.y,0.0f),math::Vector3d(0.0f,m_Ocean->m_vPosition.y,1.0f),math::Vector3d(1.0f,m_Ocean->m_vPosition.y,0.0f));
		}
		break;
		case Video::CRenderController::REFRACTION_TEXTURE :
		{
			float fOffset = 0.5f;
			Core::CGlobal::GetDevice()->EnableClipPlane(0,math::Vector3d(0.0f,m_Ocean->m_vPosition.y + fOffset,0.0f),math::Vector3d(1.0f,m_Ocean->m_vPosition.y + fOffset,0.0f),math::Vector3d(0.0f,m_Ocean->m_vPosition.y + fOffset,1.0f));
		}
		break;
	}

	std::map<std::string,CDummy*>::iterator cLandscape = m_LandscapeContainer.begin();
	while(cLandscape != m_LandscapeContainer.end())
	{
		cLandscape->second->Update();
		cLandscape++;
	}

	std::map<std::string,CDummy*>::iterator cModel = m_ModelContainer.begin();
	while(cModel != m_ModelContainer.end())
	{
		cModel->second->Update();
		cModel++;
	}

	m_Grass->Update();

	m_characterController->GetEditController()->GetBrush()->Update();

	switch(_value)
	{
		case Video::CRenderController::SCREEN_TEXTURE :
		{
			
		}
		break;
		case Video::CRenderController::REFLECTION_TEXTURE :
		{
			m_Camera->mView = math::MatrixView(m_Camera->vPosition,m_Camera->vLookAt,math::Vector3d(0.0f,1.0f,0.0f));
		}
		break;
		case Video::CRenderController::REFRACTION_TEXTURE :
		{
			
		}
		break;
	}
}


void EnviromentController::Render(Video::CRenderController::ERenderTexture value)
{
	switch(value)
	{
		case Video::CRenderController::SCREEN_TEXTURE :
		{
			m_Sky->Render();
			std::map<std::string,CDummy*>::iterator cOcean = m_OceanContainer.begin();
			while(cOcean != m_OceanContainer.end())
			{
				cOcean->second->Render();
				cOcean++;
			}

			std::map<std::string,CDummy*>::iterator cLandscape = m_LandscapeContainer.begin();
			while(cLandscape != m_LandscapeContainer.end())
			{
				cLandscape->second->Render();
				cLandscape++;
			}

			std::map<std::string,CDummy*>::iterator cModel = m_ModelContainer.begin();
			while(cModel != m_ModelContainer.end())
			{
				cModel->second->Render();
				cModel++;
			}
			m_characterController->GetEditController()->GetBrush()->Render();
			m_Grass->Render();	
		}
		break;
		case Video::CRenderController::REFLECTION_TEXTURE :
		{
			std::map<std::string,CDummy*>::iterator cLandscape = m_LandscapeContainer.begin();
			while(cLandscape != m_LandscapeContainer.end())
			{
				cLandscape->second->Render();
				cLandscape++;
			}

			/*std::map<std::string,CDummy*>::iterator cModel = m_ModelContainer.begin();
			while(cModel != m_ModelContainer.end())
			{
				cModel->second->Render();
				cModel++;
			}*/

			m_Grass->Render();
			
			Core::CGlobal::GetDevice()->DisableClipPlane(0);
		}
		break;
		case Video::CRenderController::REFRACTION_TEXTURE :
		{
			std::map<std::string,CDummy*>::iterator cLandscape = m_LandscapeContainer.begin();
			while(cLandscape != m_LandscapeContainer.end())
			{
				cLandscape->second->Render();
				cLandscape++;
			}

			std::map<std::string,CDummy*>::iterator cModel = m_ModelContainer.begin();
			while(cModel != m_ModelContainer.end())
			{
				cModel->second->Render();
				cModel++;
			}
			m_characterController->GetEditController()->GetBrush()->Render();
			m_Grass->Render();

			Core::CGlobal::GetDevice()->DisableClipPlane(0);
		}
		break;
	}
}
