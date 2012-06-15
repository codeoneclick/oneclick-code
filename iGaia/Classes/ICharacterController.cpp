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

#define M_PI 3.14159265358979323846264338327950288

ICharacterController::ICharacterController(void)
{
    m_eMoveState = E_CHARACTER_CONTROLLER_MOVE_STATE_NONE;
    m_eSteerState = E_CHARACTER_CONTROLLER_STEER_STATE_NONE;
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
    glm::vec3 vPoint_02 = glm::vec3(_vPosition.x, _vPosition.y + 0.25f, _vPosition.z);
    float fHeight = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_HeightValue(_vPosition.x + 0.25f, _vPosition.z);
    glm::vec3 vPoint_03 = glm::vec3(_vPosition.x + 0.25f, fHeight, _vPosition.z);
    fHeight = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_HeightValue(_vPosition.x, _vPosition.z + 0.25f);
    glm::vec3 vPoint_04 = glm::vec3(_vPosition.x, fHeight, _vPosition.z + 0.25f);
    
    float fAngle_01 = _Get_RotationForPlane(vPoint_01, vPoint_02, vPoint_03);
    float fAngle_02 = _Get_RotationForPlane(vPoint_01, vPoint_02, vPoint_04);
    
    return glm::vec2(-acos(fAngle_02) + 1.57f, -acos(fAngle_01) + 1.57f);
}

float ICharacterController::_GetRotationBetweenPoints(glm::vec3 _vPoint_01, glm::vec3 _vPoint_02)
{
    float fVectorLength = sqrtf(pow(_vPoint_02.x - _vPoint_01.x, 2) + pow(_vPoint_02.z - _vPoint_01.z, 2));
    float fAngle_01 = M_PI * (_vPoint_02.x - _vPoint_01.x) / fVectorLength;
    float fAngle_02 = M_PI * (_vPoint_02.z - _vPoint_01.z) / fVectorLength;
    float fAngle_03 = 0.0f;
    if (fAngle_01 > 0.0f)
        fAngle_03 =  fAngle_02 / 2.0f;
    if (fAngle_01 < 0.0f)
        fAngle_03 = -fAngle_02 / 2.0f - M_PI;
    return -fAngle_03;
}


bool ICharacterController::MoveForward(void)
{
    float fHeight = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_HeightValue(m_vPosition.x + sinf(glm::radians(m_vRotation.y)) * m_fMoveSpeed, m_vPosition.z + cosf(glm::radians(m_vRotation.y)) * m_fMoveSpeed);
    if(fHeight < k_MIN_HEIGHTMAP_VALUE)
    {
        return false;
    }
    m_vPosition.x += sinf(glm::radians(m_vRotation.y)) * m_fMoveSpeed;
    m_vPosition.z += cosf(glm::radians(m_vRotation.y)) * m_fMoveSpeed;
    Set_Position(m_vPosition);
    return true;
}

bool ICharacterController::MoveBackward(void)
{
    float fHeight = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_HeightValue(m_vPosition.x - sinf(glm::radians(m_vRotation.y)) * m_fMoveSpeed, m_vPosition.z - cosf(glm::radians(m_vRotation.y)) * m_fMoveSpeed);
    if(fHeight < k_MIN_HEIGHTMAP_VALUE)
    {
        return false;
    }
    m_vPosition.x -= sinf(glm::radians(m_vRotation.y)) * m_fMoveSpeed;
    m_vPosition.z -= cosf(glm::radians(m_vRotation.y)) * m_fMoveSpeed;
    Set_Position(m_vPosition);
    return true;
}

bool ICharacterController::SteerRight(void)
{
    m_vRotation.y -= m_fSteerSpeed;
    Set_Rotation(m_vRotation);
    return true;
}

bool ICharacterController::SteerLeft(void)
{
    m_vRotation.y += m_fSteerSpeed;
    Set_Rotation(m_vRotation);
    return true;
}


void ICharacterController::Set_Position(const glm::vec3 &_vPosition)
{
    if(m_pBodyModel != NULL)
    {
        m_pBodyModel->Set_Position(_vPosition);
    }
    if(m_pTowerModel != NULL)
    {
        m_pTowerModel->Set_Position(_vPosition);
    }
    if(m_pLeftTrackModel != NULL)
    {
        m_pLeftTrackModel->Set_Position(_vPosition);
    }
    if(m_pRightTrackModel != NULL)
    {
        m_pRightTrackModel->Set_Position(_vPosition);
    }
    
    
    if(m_pShadowDecal != NULL)
    {
        m_pShadowDecal->Set_Position(glm::vec3(_vPosition.x, 0.0f, _vPosition.z));
    }
    if(m_pLeftExhaustSmokeEmitter != NULL)
    {
        m_vTowerEmitterNodePosition = m_pBodyModel->Get_BoundingBox()->Get_Center();
        m_vTransformHelper = glm::vec4(m_vTowerEmitterNodePosition.x + k_EXHAUST_EMITTER_OFFSET_X, m_vTowerEmitterNodePosition.y, m_vTowerEmitterNodePosition.z - k_EXHAUST_EMITTER_OFFSET_Z, 1.0f);
        m_mRotationHelper = glm::rotate(glm::mat4(1.0f),   m_vRotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        m_mRotationHelper = glm::rotate(m_mRotationHelper, m_vRotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
        m_mRotationHelper = glm::rotate(m_mRotationHelper, m_vRotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
        m_vTransformHelper = m_mRotationHelper * m_vTransformHelper;
        m_pLeftExhaustSmokeEmitter->Set_Position(glm::vec3(_vPosition.x + m_vTransformHelper.x, _vPosition.y + m_vTransformHelper.y + k_EXHAUST_EMITTER_HEIGHT, _vPosition.z + m_vTransformHelper.z));
    }
    if(m_pRightExhaustSmokeEmitter != NULL)
    {
        m_vTowerEmitterNodePosition = m_pBodyModel->Get_BoundingBox()->Get_Center();
        m_vTransformHelper = glm::vec4(m_vTowerEmitterNodePosition.x - k_EXHAUST_EMITTER_OFFSET_X, m_vTowerEmitterNodePosition.y + k_EXHAUST_EMITTER_HEIGHT, m_vTowerEmitterNodePosition.z - k_EXHAUST_EMITTER_OFFSET_Z, 1.0f);
        m_mRotationHelper = glm::rotate(glm::mat4(1.0f),   m_vRotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        m_mRotationHelper = glm::rotate(m_mRotationHelper, m_vRotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
        m_mRotationHelper = glm::rotate(m_mRotationHelper, m_vRotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
        m_vTransformHelper = m_mRotationHelper * m_vTransformHelper;
        m_pRightExhaustSmokeEmitter->Set_Position(glm::vec3(_vPosition.x + m_vTransformHelper.x, _vPosition.y + m_vTransformHelper.y, _vPosition.z + m_vTransformHelper.z));
    }
    if(m_pFireCross != NULL)
    {
        m_vTowerEmitterNodePosition = m_pBodyModel->Get_BoundingBox()->Get_Center();
        m_vTransformHelper = glm::vec4(m_vTowerEmitterNodePosition.x, m_vTowerEmitterNodePosition.y + k_CROSS_FIRE_HEIGHT, m_vTowerEmitterNodePosition.z + k_CROSS_FIRE_OFFSET, 1.0f);
        m_mRotationHelper = glm::rotate(glm::mat4(1.0f),   m_vRotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        m_mRotationHelper = glm::rotate(m_mRotationHelper, m_vRotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
        m_mRotationHelper = glm::rotate(m_mRotationHelper, m_fTowerRotationY, glm::vec3(0.0f, 1.0f, 0.0f));
        m_vTransformHelper = m_mRotationHelper * m_vTransformHelper;
        m_pFireCross->Set_Position(glm::vec3(_vPosition.x + m_vTransformHelper.x, _vPosition.y + m_vTransformHelper.y, _vPosition.z + m_vTransformHelper.z));
    }
    if(m_pLeftTrackFireEmitter != NULL)
    {
        m_vLeftTrackEmitterNodePosition = m_pLeftTrackModel->Get_BoundingBox()->Get_Center();
        m_vTransformHelper = glm::vec4(m_vLeftTrackEmitterNodePosition.x, m_vLeftTrackEmitterNodePosition.y + k_TRACK_EMITTER_HEIGHT, m_vLeftTrackEmitterNodePosition.z, 1.0f);
        m_mRotationHelper = glm::rotate(glm::mat4(1.0f),   m_vRotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        m_mRotationHelper = glm::rotate(m_mRotationHelper, m_vRotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
        m_mRotationHelper = glm::rotate(m_mRotationHelper, m_vRotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
        m_vTransformHelper = m_mRotationHelper * m_vTransformHelper;
        m_pLeftTrackFireEmitter->Set_Position(glm::vec3(_vPosition.x + m_vTransformHelper.x, _vPosition.y + m_vTransformHelper.y, _vPosition.z + m_vTransformHelper.z));
    }
    if(m_pRightTrackFireEmitter != NULL)
    {
        m_vRightTrackEmitterNodePosition = m_pRightTrackModel->Get_BoundingBox()->Get_Center();
        m_vTransformHelper = glm::vec4(m_vRightTrackEmitterNodePosition.x, m_vRightTrackEmitterNodePosition.y + k_TRACK_EMITTER_HEIGHT, m_vRightTrackEmitterNodePosition.z, 1.0f);
        m_mRotationHelper = glm::rotate(glm::mat4(1.0f),   m_vRotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        m_mRotationHelper = glm::rotate(m_mRotationHelper, m_vRotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
        m_mRotationHelper = glm::rotate(m_mRotationHelper, m_vRotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
        m_vTransformHelper = m_mRotationHelper * m_vTransformHelper;
        m_pRightTrackFireEmitter->Set_Position(glm::vec3(_vPosition.x + m_vTransformHelper.x, _vPosition.y + m_vTransformHelper.y, _vPosition.z + m_vTransformHelper.z));
    }
    if(m_pTowerFireEmitter != NULL)
    {
        m_vTowerEmitterNodePosition = m_pBodyModel->Get_BoundingBox()->Get_Center();
        m_vTransformHelper = glm::vec4(m_vTowerEmitterNodePosition.x, m_vTowerEmitterNodePosition.y + k_TOWER_EMITTER_HEIGHT, m_vTowerEmitterNodePosition.z, 1.0f);
        m_mRotationHelper = glm::rotate(glm::mat4(1.0f),   m_vRotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        m_mRotationHelper = glm::rotate(m_mRotationHelper, m_vRotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
        m_mRotationHelper = glm::rotate(m_mRotationHelper, m_vRotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
        m_vTransformHelper = m_mRotationHelper * m_vTransformHelper;
        m_pTowerFireEmitter->Set_Position(glm::vec3(_vPosition.x + m_vTransformHelper.x, _vPosition.y + m_vTransformHelper.y, _vPosition.z + m_vTransformHelper.z));
    }


    
    /*if(m_pFireEmmiter != NULL)
    {
        glm::vec3 vCenter = m_pLeftTrackModel->Get_BoundingBox()->Get_Center();
        glm::vec4 vTransform = glm::vec4(vCenter.x, vCenter.y, vCenter.z, 1.0f);
        glm::mat4x4 mRotation = glm::rotate(glm::mat4(1.0f), m_vRotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
        mRotation = glm::rotate(mRotation, m_vRotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
        mRotation = glm::rotate(mRotation, m_vRotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
        vTransform = mRotation * vTransform;
        m_pFireEmmiter->Set_Position(glm::vec3(_vPosition.x + vTransform.x, _vPosition.y + vTransform.y, _vPosition.z + vTransform.z));
    }*/
        
    m_vPosition = _vPosition;
}

void ICharacterController::Set_Rotation(const glm::vec3 &_vRotation)
{
    if(m_pBodyModel != NULL)
    {
        m_pBodyModel->Set_Rotation(_vRotation);
    }
    if(m_pTowerModel != NULL)
    {
        m_pTowerModel->Set_Rotation(glm::vec3(_vRotation.x, m_fTowerRotationY, _vRotation.z));
    }
    if(m_pLeftTrackModel != NULL)
    {
        m_pLeftTrackModel->Set_Rotation(_vRotation);
    }
    if(m_pRightTrackModel != NULL)
    {
        m_pRightTrackModel->Set_Rotation(_vRotation);
    }
    if(m_pShadowDecal != NULL)
    {
        m_pShadowDecal->Set_Rotation(m_vRotation);
    }
    if(m_pFireCross != NULL)
    {
        m_pFireCross->Set_Rotation(glm::vec3(_vRotation.x, m_fTowerRotationY, _vRotation.z));
    }
    m_vRotation = _vRotation;
}


































