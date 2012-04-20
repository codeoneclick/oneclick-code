//
//  IGameUnit.cpp
//  iGaia
//
//  Created by sergey.sergeev on 2/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "ICharacterController.h"
#include "CSceneMgr.h"

ICharacterController::ICharacterController(void)
{
    time_t seconds;
    seconds = time (NULL);
}

ICharacterController::~ICharacterController(void)
{
    
}

float ICharacterController::_Get_RotationForPlane(glm::vec3 _vPoint_01, glm::vec3 _vPoint_02, glm::vec3 _vPoint_03)
{
    float fVectorLength_01 = sqrt(pow(_vPoint_02.x - _vPoint_01.x,2) + pow(_vPoint_02.y - _vPoint_01.y,2) + pow(_vPoint_02.z - _vPoint_01.z,2));
    float fVectorLength_02 = sqrt(pow(_vPoint_03.x - _vPoint_01.x,2) + pow(_vPoint_03.y - _vPoint_01.y,2) + pow(_vPoint_03.z - _vPoint_01.z,2));
    float fScalar = (_vPoint_02.x - _vPoint_01.x)*(_vPoint_03.x - _vPoint_01.x) + (_vPoint_02.y - _vPoint_01.y)*(_vPoint_03.y - _vPoint_01.y) + (_vPoint_02.z - _vPoint_01.z)*(_vPoint_03.z - _vPoint_01.z);
    return fScalar / (fVectorLength_01 * fVectorLength_02);
}

glm::vec2 ICharacterController::_Get_RotationOnHeightmap(glm::vec3 _vPosition)
{
    glm::vec3 vPoint_01 = _vPosition;
    glm::vec3 vPoint_02 = glm::vec3(_vPosition.x, _vPosition.y + 0.1f, _vPosition.z);
    float fHeight = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_HeightValueAtPoint(_vPosition.x + 0.1f, _vPosition.z);
    glm::vec3 vPoint_03 = glm::vec3(_vPosition.x + 0.1f, fHeight, _vPosition.z);
    fHeight = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_HeightValueAtPoint(_vPosition.x, _vPosition.z + 0.1f);
    glm::vec3 vPoint_04 = glm::vec3(_vPosition.x, fHeight, _vPosition.z + 0.1f);
    
    float fAngle_01 = _Get_RotationForPlane(vPoint_01, vPoint_02, vPoint_03);
    float fAngle_02 = _Get_RotationForPlane(vPoint_01, vPoint_02, vPoint_04);
    
    return glm::vec2(-acos(fAngle_02) + 1.57f, -acos(fAngle_01) + 1.57f);
}

float ICharacterController::_GetRotationBetweenPoints(glm::vec3 _vPoint_01, glm::vec3 _vPoint_02)
{
    float fVectorLength = sqrt(pow(_vPoint_02.x - _vPoint_01.x, 2) + pow(_vPoint_02.z - _vPoint_01.z, 2));
    float fAngle_01 = 3.14f * (_vPoint_02.x - _vPoint_01.x) / fVectorLength;
    float fAngle_02 = 3.14f * (_vPoint_02.z - _vPoint_01.z) / fVectorLength;
    float fAngle_03 = 0.0f;
    if (fAngle_01 > 0) 
        fAngle_03 = fAngle_02 / 2.0f;
    if (fAngle_01 < 0) 
        fAngle_03 = -fAngle_02 / 2.0f - 3.14f;
    return  -fAngle_03;
}


void ICharacterController::MoveForward(void)
{
    m_vPosition.x += sinf(glm::radians(m_vRotation.y)) * m_fMoveSpeed;
    m_vPosition.z += cosf(glm::radians(m_vRotation.y)) * m_fMoveSpeed;
    Set_Position(m_vPosition);
}

void ICharacterController::MoveBackward(void)
{
    m_vPosition.x -= sinf(glm::radians(m_vRotation.y)) * m_fMoveSpeed;
    m_vPosition.z -= cosf(glm::radians(m_vRotation.y)) * m_fMoveSpeed;
    Set_Position(m_vPosition);
}

void ICharacterController::SteerRight(void)
{
    m_vRotation.y -= m_fSteerSpeed;
    Set_Rotation(m_vRotation);
}

void ICharacterController::SteerLeft(void)
{
    m_vRotation.y += m_fSteerSpeed;
    Set_Rotation(m_vRotation);
}





