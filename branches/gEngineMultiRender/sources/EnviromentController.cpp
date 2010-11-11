#include "EnviromentController.h"
#include "Resource.h"

using namespace Enviroment;

EnviromentController::EnviromentController()
{
	m_Camera = NULL;
	m_CharacterControl = NULL;
	m_Landscape = NULL;
}

void EnviromentController::Load()
{
	m_CameraContainer["MainCamera"] = new Camera(); 
	m_Camera = m_CameraContainer["MainCamera"];

	m_LandscapeContainer["landscape_01"] = new CLandscape();
	m_LandscapeContainer["landscape_01"]->Load("Content\\maps\\map.raw");

	m_Landscape = m_LandscapeContainer["landscape_01"];

	m_ModelContainer["model_01"] = new CModel();
    m_ModelContainer["model_01"]->Load("Content\\models\\tank.3ds");
	m_ModelContainer["model_01"]->m_vRotation.x = -1.57f;
	m_ModelContainer["model_01"]->m_vScale = math::Vector3d(0.04f,0.04f,0.04f);

	m_CharacterControl = m_ModelContainer["model_01"];

	CResource::Enable();
}

float EnviromentController::GetLandscapeHeight(float _positionX,float _positionZ)
{
	float** landscapeData = ((CLandscape*)m_Landscape)->GetHeightData();
	unsigned int landscapeWidth = ((CLandscape*)m_Landscape)->GetWidth();
	unsigned int landscapeHeight = ((CLandscape*)m_Landscape)->GetHeight();
    int roundPositionX = (int) _positionX;
    int roundPositionZ = (int) _positionZ;

    float remainPositionX = _positionX - roundPositionX;
    float remainPositionZ = _positionZ - roundPositionZ;

    if((roundPositionX < 0) || (roundPositionZ < 0) || (roundPositionX >= (landscapeWidth - 1)) || (roundPositionZ > (landscapeHeight - 1)))
       return 0.0f;
        
    float height_11 = landscapeData[roundPositionX][roundPositionZ]*0.1f;
    float height_12 = landscapeData[roundPositionX][roundPositionZ +1]*0.1f;
    float height_21 = landscapeData[roundPositionX + 1][roundPositionZ]*0.1f;
    float height_22 = landscapeData[roundPositionX + 1][roundPositionZ + 1]*0.1f;
    float mainHeight;

    if( remainPositionX > remainPositionZ )
        {
                mainHeight = height_11 + (height_22 - height_21)*remainPositionZ + (height_21 - height_11)*remainPositionX;
        }
        else
        {
                mainHeight = height_11 + (height_22 - height_12)*remainPositionX + (height_12 - height_11)*remainPositionZ;
        }

        float height = (1 - remainPositionX) * ((1 - remainPositionZ) * height_11 + remainPositionZ * height_12) + remainPositionX * ((1 - remainPositionZ) * height_21 + remainPositionZ * height_22);
        return height;
}

float EnviromentController::GetRotationFromNormal(math::Vector3d vPosition_01,math::Vector3d vPosition_02)
{
	float fGipotenuzeLength = sqrt(pow(vPosition_02.x - vPosition_01.x,2) + pow(vPosition_02.y - vPosition_01.y,2) + pow(vPosition_02.z - vPosition_01.z,2));
	float fKatetLength = vPosition_02.y - vPosition_01.y;
	return fKatetLength / fGipotenuzeLength;
}


math::Vector3d EnviromentController::GetLandscapeRotation(math::Vector3d vPosition)
{
	math::Vector3d vPoint_01 = vPosition;
	math::Vector3d vPoint_02 = math::Vector3d(vPosition.x + 1.0f,GetLandscapeHeight(vPosition.x + 1.0f,vPosition.z),vPosition.z);
	math::Vector3d vPoint_03 = math::Vector3d(vPosition.x,GetLandscapeHeight(vPosition.x,vPosition.z + 1.0f),vPosition.z + 1.0f);

	float fAngle_01 = GetRotationFromNormal(vPoint_01, vPoint_02);
	float fAngle_02 = GetRotationFromNormal(vPoint_01, vPoint_03);

	return math::Vector3d(asin(fAngle_02),0.0f,asin(fAngle_01));
}

void EnviromentController::Update(DWORD time)
{
    m_Camera->Update();

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

	m_Camera->vLookAt.y = GetLandscapeHeight(m_Camera->vLookAt.x,m_Camera->vLookAt.z);
	m_CharacterControl->m_vPosition = m_Camera->vLookAt;

	m_CharacterControl->m_vRotation.x = -GetLandscapeRotation(m_CharacterControl->m_vPosition).x;
	m_CharacterControl->m_vRotation.z = GetLandscapeRotation(m_CharacterControl->m_vPosition).z;
	m_CharacterControl->m_vRotation.y = m_Camera->vRotation.y;
	
	CResource::WorkInMainTread();
}

void EnviromentController::Render(Video::CRenderController::ERenderTexture value)
{
	switch(value)
	{
		case Video::CRenderController::SCREEN_TEXTURE :
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
		}
		break;
		case Video::CRenderController::REFLECTION_TEXTURE :
		{

		}
		break;
		case Video::CRenderController::REFRACTION_TEXTURE :
		{

		}
		break;
	}
}
