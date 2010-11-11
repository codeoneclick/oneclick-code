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

	m_OceanContainer["ocean_01"] = new COcean();
	m_OceanContainer["ocean_01"]->Load("none");
	m_Ocean = m_OceanContainer["ocean_01"];

	m_ModelContainer["model_01"] = new CModel();
    m_ModelContainer["model_01"]->Load("Content\\models\\tank.3ds");
	m_ModelContainer["model_01"]->m_vRotation.x = -1.57f;
	m_ModelContainer["model_01"]->m_vScale = math::Vector3d(0.04f,0.04f,0.04f);

	m_CharacterControl = m_ModelContainer["model_01"];

	CResource::Enable();
}

float EnviromentController::GetLandscapeHeight(float _fPosition_x,float _fPosition_z)
{
	float** landscapeData = ((CLandscape*)m_Landscape)->GetHeightData();
	unsigned int landscapeWidth = ((CLandscape*)m_Landscape)->GetWidth();
	unsigned int landscapeHeight = ((CLandscape*)m_Landscape)->GetHeight();
	float landscapeHeightFactor = ((CLandscape*)m_Landscape)->GetHeightFactor();
    int roundPositionX = (int) _fPosition_x;
    int roundPositionZ = (int) _fPosition_z;

    float remainPositionX = _fPosition_x - roundPositionX;
    float remainPositionZ = _fPosition_z - roundPositionZ;

    if((roundPositionX < 0) || (roundPositionZ < 0) || (roundPositionX >= (landscapeWidth - 1)) || (roundPositionZ > (landscapeHeight - 1)))
       return 0.0f;
        
    float height_11 = landscapeData[roundPositionX][roundPositionZ] * landscapeHeightFactor;
    float height_12 = landscapeData[roundPositionX][roundPositionZ +1] * landscapeHeightFactor;
    float height_21 = landscapeData[roundPositionX + 1][roundPositionZ] * landscapeHeightFactor;
    float height_22 = landscapeData[roundPositionX + 1][roundPositionZ + 1] * landscapeHeightFactor;
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

float EnviromentController::GetRotationFromNormal(math::Vector3d _vPosition_01,math::Vector3d _vPosition_02)
{
	float fGipotenuzeLength = sqrt(pow(_vPosition_02.x - _vPosition_01.x,2) + pow(_vPosition_02.y - _vPosition_01.y,2) + pow(_vPosition_02.z - _vPosition_01.z,2));
	float fKatetLength = _vPosition_02.y - _vPosition_01.y;
	return fKatetLength / fGipotenuzeLength;
}


math::Vector3d EnviromentController::GetLandscapeRotation(math::Vector3d _vPosition)
{
	math::Vector3d vPoint_01 = _vPosition;
	math::Vector3d vPoint_02 = math::Vector3d(_vPosition.x + 1.0f,GetLandscapeHeight(_vPosition.x + 1.0f,_vPosition.z),_vPosition.z);
	math::Vector3d vPoint_03 = math::Vector3d(_vPosition.x,GetLandscapeHeight(_vPosition.x,_vPosition.z + 1.0f),_vPosition.z + 1.0f);

	float fAngle_01 = GetRotationFromNormal(vPoint_01, vPoint_02);
	float fAngle_02 = GetRotationFromNormal(vPoint_01, vPoint_03);

	return math::Vector3d(asin(fAngle_02),0.0f,asin(fAngle_01));
}

void EnviromentController::Update(DWORD time)
{
	if(time == 0)
		m_Camera->Update();

	math::Vector3d vCameraPosition = m_Camera->vPosition;
	math::Vector3d vCameraLookAt = m_Camera->vLookAt;
	if(time  == 1)
	{
		vCameraPosition.y = -m_Camera->vPosition.y  + m_Ocean->m_vPosition.y * 2.0f;
		vCameraLookAt.y = -m_Camera->vLookAt.y + m_Ocean->m_vPosition.y * 2.0f;
		m_Camera->mView = math::MatrixView(vCameraPosition, vCameraLookAt, math::Vector3d(0.0f,-1.0f,0.0f));

		D3DXPLANE clipPlane;
		D3DXPlaneFromPoints(&clipPlane,&D3DXVECTOR3(0.0f,m_Ocean->m_vPosition.y,0.0f),&D3DXVECTOR3(0.0f,m_Ocean->m_vPosition.y,1.0f),&D3DXVECTOR3(1.0f,m_Ocean->m_vPosition.y,0.0f));
		Core::CGlobal::GetDevice()->Ref()->SetRenderState(D3DRS_CLIPPLANEENABLE, D3DCLIPPLANE0);
		D3DXVECTOR4 clipVector = D3DXVECTOR4(clipPlane.a,clipPlane.b,clipPlane.c,clipPlane.d);
		math::Matrix4x4 mClipPlane = m_Camera->mView * m_Camera->mProjection;
		D3DXMATRIX clipMatrix;
		memcpy(clipMatrix.m,mClipPlane.m,16 * sizeof(float));
		D3DXMatrixTranspose(&clipMatrix,&clipMatrix);
		D3DXMatrixInverse(&clipMatrix,NULL,&clipMatrix);
		D3DXVec4Transform(&clipVector,&clipVector,&clipMatrix);

		clipPlane.a = clipVector.x;
		clipPlane.b = clipVector.y;
		clipPlane.c = clipVector.z;
		clipPlane.d = clipVector.w;

		Core::CGlobal::GetDevice()->Ref()->SetClipPlane(0, clipPlane);
	}

	std::map<std::string,CDummy*>::iterator cOcean = m_OceanContainer.begin();
	while(cOcean != m_OceanContainer.end())
	{
		cOcean->second->Update();
		cOcean++;
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

	if(time  == 1)
	{
		//m_Camera->vPosition.y = -vCameraPosition.y;
		//m_Camera->vLookAt.y = -vCameraLookAt.y;
		//
		m_Camera->mView = math::MatrixView(m_Camera->vPosition,m_Camera->vLookAt,math::Vector3d(0.0f,1.0f,0.0f));
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

			std::map<std::string,CDummy*>::iterator cModel = m_ModelContainer.begin();
			while(cModel != m_ModelContainer.end())
			{
				cModel->second->Render();
				cModel++;
			}
			Core::CGlobal::GetDevice()->Ref()->SetRenderState(D3DRS_CLIPPLANEENABLE, FALSE);
		}
		break;
		case Video::CRenderController::REFRACTION_TEXTURE :
		{

		}
		break;
	}
}
