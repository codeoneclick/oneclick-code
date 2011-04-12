#include "CharacterController.h"
#include "../../Core/Input.h"

//#define EDITOR_ENABLE 1

using namespace Enviroment;

CharacterController::CharacterController(Camera* _camera, CDummy* _character, CDummy* _landscape)
{
	m_camera = _camera;
	m_character = _character;
	m_landscape = _landscape;
#ifdef EDITOR_ENABLE
	m_currentMoveSpeed = 2.5f;
	m_rotationSpeed = 2.5f;
#else
	m_currentMoveSpeed = 0.0f;
	m_rotationSpeed = 0.5f;
#endif

	m_minMoveSpeed = 0.0f;
	m_maxForwardMoveSpeed = 0.5f;
	m_maxBackwardMoveSpeed = -0.25f;
	m_moveAcceleration = 0.001f;
	m_dragFactor = 5.0f;

	m_character->m_vScale = math::Vector3d(0.01f,0.01f,0.01f);
	_camera->SetTarget(_character);
	_camera->SetDistanceToTarget(4.0f);
	m_cameraHeightUnderTarget = 4.0f;

	m_cEditController = new EditorController(m_landscape);
}

float CharacterController::GetLandscapeHeight(float _fPosition_x,float _fPosition_z)
{
	float** landscapeData = ((CLandscape*)m_landscape)->GetHeightData();
	unsigned int landscapeWidth = ((CLandscape*)m_landscape)->GetWidth();
	unsigned int landscapeHeight = ((CLandscape*)m_landscape)->GetHeight();
	float landscapeHeightFactor = ((CLandscape*)m_landscape)->GetHeightFactor();
    int roundPositionX = (int) _fPosition_x;
    int roundPositionZ = (int) _fPosition_z;

    float remainPositionX = _fPosition_x - roundPositionX;
    float remainPositionZ = _fPosition_z - roundPositionZ;

    if((roundPositionX < 0) || (roundPositionZ < 0) || (roundPositionX >= (landscapeWidth - 1)) || (roundPositionZ > (landscapeHeight - 1)))
       return 0.0f;
        
    float height_11 = landscapeData[roundPositionX][roundPositionZ] * landscapeHeightFactor;
    float height_12 = landscapeData[roundPositionX][roundPositionZ + 1] * landscapeHeightFactor;
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

float CharacterController::GetRotationFromNormal(math::Vector3d _vPosition_01,math::Vector3d _vPosition_02)
{
	float fGipotenuzeLength = sqrt(pow(_vPosition_02.x - _vPosition_01.x,2) + pow(_vPosition_02.y - _vPosition_01.y,2) + pow(_vPosition_02.z - _vPosition_01.z,2));
	float fKatetLength = _vPosition_02.y - _vPosition_01.y;
	return fKatetLength / fGipotenuzeLength;
}


math::Vector3d CharacterController::GetLandscapeRotation(math::Vector3d _vPosition)
{
	math::Vector3d vPoint_01 = _vPosition;
	math::Vector3d vPoint_02 = math::Vector3d(_vPosition.x + 1.0f,GetLandscapeHeight(_vPosition.x + 1.0f,_vPosition.z),_vPosition.z);
	math::Vector3d vPoint_03 = math::Vector3d(_vPosition.x,GetLandscapeHeight(_vPosition.x,_vPosition.z + 1.0f),_vPosition.z + 1.0f);

	float fAngle_01 = GetRotationFromNormal(vPoint_01, vPoint_02);
	float fAngle_02 = GetRotationFromNormal(vPoint_01, vPoint_03);

	return math::Vector3d(asin(fAngle_02),0.0f,asin(fAngle_01));
}

void CharacterController::Update(DWORD _time)
{
#ifdef EDITOR_ENABLE
	MouseControl();
	EditorUpdate();
	m_cEditController->SetWorkingPosition(m_vPosition);
	((CBrush*)m_cEditController->GetBrush())->Set2DPosition(math::Vector2d(m_vPosition.x,m_vPosition.z));
	m_cEditController->SetWorkingArea(16.0f);
	m_cEditController->Update();
#else
	KeyboardControl();
	CharacterUpdate();
#endif
}

void CharacterController::CharacterUpdate()
{
	m_vPosition.y = GetLandscapeHeight(m_vPosition.x, m_vPosition.z);
	m_camera->vPosition.y = GetLandscapeHeight(m_camera->vPosition.x,m_camera->vPosition.z) + 2.0f;
	m_character->m_vPosition = m_vPosition;

	m_character->m_vRotation.x = -GetLandscapeRotation(m_vPosition).x;
	m_character->m_vRotation.z = GetLandscapeRotation(m_vPosition).z;
	m_character->m_vRotation.y = m_vRotation.y * TO_RAD;
	
	m_camera->vRotation.y = m_vRotation.y * TO_RAD;
}

void CharacterController::EditorUpdate()
{
	m_vPosition.y = GetLandscapeHeight(m_vPosition.x, m_vPosition.z);
	m_camera->vPosition.y = 32.0f;//GetLandscapeHeight(m_vPosition.x,m_vPosition.z) + m_cameraHeightUnderTarget;
	m_character->m_vPosition = m_vPosition;
	
	m_camera->vRotation.y = m_vRotation.y * TO_RAD;
}

void CharacterController::KeyboardControl()
{
	if(core::Input::keys[VK_LEFT])
		RotateLeft();

	if(core::Input::keys[VK_RIGHT])
		RotateRight();

	int moveKeyDownCount = 0;

	if(core::Input::keys[VK_UP])
	{
		if(m_currentMoveSpeed < m_maxForwardMoveSpeed)
		{
			if(m_currentMoveSpeed < m_minMoveSpeed)
			{
				m_currentMoveSpeed += m_moveAcceleration * m_dragFactor;
			}
			else
			{
				m_currentMoveSpeed += m_moveAcceleration;
			}
		}
		moveKeyDownCount++;
	}

	if(core::Input::keys[VK_DOWN])
	{
		if(m_currentMoveSpeed > m_maxBackwardMoveSpeed)
		{
			if(m_currentMoveSpeed > m_minMoveSpeed)
			{
				m_currentMoveSpeed -= m_moveAcceleration * m_dragFactor;
			}
			else
			{
				m_currentMoveSpeed -= m_moveAcceleration;
			}
		}
		moveKeyDownCount++;
	}

	if(moveKeyDownCount == 0)
	{
		if(m_currentMoveSpeed > m_minMoveSpeed)
		{
			m_currentMoveSpeed -= m_moveAcceleration * m_dragFactor;
		}
		else
		{
			m_currentMoveSpeed += m_moveAcceleration * m_dragFactor;
		}
	}

	m_vPosition.x += (float)sin(m_vRotation.y * TO_RAD) * m_currentMoveSpeed;
    m_vPosition.z += (float)cos(m_vRotation.y * TO_RAD) * m_currentMoveSpeed;
}

void CharacterController::MouseControl()
{
	if( core::Input::mouseR )
	{
		int diffx = core::Input::currentMousePosition.x - core::Input::oldMousePosition.x; 
		int diffy = core::Input::currentMousePosition.y - core::Input::oldMousePosition.y; 

		core::Input::oldMousePosition.x = core::Input::currentMousePosition.x;
		core::Input::oldMousePosition.y = core::Input::currentMousePosition.y;
		
		if(diffx < 0)
			MoveRight();
		if(diffx > 0)
			MoveLeft();
		if(diffy > 0)
			MoveForward();
		if(diffy < 0)
			MoveBackward();
	}

	if( core::Input::mouseL )
	{
		int diffx = core::Input::currentMousePosition.x - core::Input::oldMousePosition.x; 
		int diffy = core::Input::currentMousePosition.y - core::Input::oldMousePosition.y; 

		core::Input::oldMousePosition.x = core::Input::currentMousePosition.x;
		core::Input::oldMousePosition.y = core::Input::currentMousePosition.y;

		if(diffx < 0)
			RotateLeft();
		if(diffx > 0)
			RotateRight();
	}
}

void CharacterController::MoveForward()
{
	m_vPosition.x += (float)sin(m_vRotation.y * TO_RAD) * m_currentMoveSpeed;
    m_vPosition.z += (float)cos(m_vRotation.y * TO_RAD) * m_currentMoveSpeed;
}

void CharacterController::MoveBackward()
{
    m_vPosition.x  -= (float)sin(m_vRotation.y * TO_RAD) * m_currentMoveSpeed;
    m_vPosition.z  -= (float)cos(m_vRotation.y * TO_RAD) * m_currentMoveSpeed;
}

void CharacterController::MoveRight()
{
    m_vPosition.x += (float)cos(-m_vRotation.y * TO_RAD) * m_currentMoveSpeed;
    m_vPosition.z += (float)sin(-m_vRotation.y * TO_RAD) * m_currentMoveSpeed;
}

void CharacterController::MoveLeft()
{
    m_vPosition.x  -= (float)cos(-m_vRotation.y * TO_RAD) * m_currentMoveSpeed;
    m_vPosition.z  -= (float)sin(-m_vRotation.y * TO_RAD) * m_currentMoveSpeed;
}

void CharacterController::RotateLeft()
{
     m_vRotation.y -= m_rotationSpeed;
}

void CharacterController::RotateRight()
{
     m_vRotation.y += m_rotationSpeed;
}

bool CharacterController::IsReadyForUpdate()
{  
    static DWORD lastTime = 0;       
    DWORD currentTime = GetTickCount();

    if(currentTime - lastTime > UPDATE_INTERVAL )
    {
        lastTime = currentTime;
		return true;
    }
	return false;
}