//
//  IGameUnit.cpp
//  iGaia
//
//  Created by sergey.sergeev on 2/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "ICharacterController.h"
#include "CGameSceneMgr.h"
#include "CSceneMgr.h"
#include "CMathHelper.h"

ICharacterController::ICharacterController(void)
{
    m_eMoveState = E_CHARACTER_CONTROLLER_MOVE_STATE_NONE;
    m_eSteerState = E_CHARACTER_CONTROLLER_STEER_STATE_NONE;
    m_pTarget = NULL;
}

ICharacterController::~ICharacterController(void)
{
    SAFE_DELETE(m_pBody);
    SAFE_DELETE(m_pTower);
    SAFE_DELETE(m_pTrack);
    
    CSceneMgr::Instance()->Get_DecalMgr()->Remove_Decal(m_pShadowDecal);
    CSceneMgr::Instance()->Get_DecalMgr()->Remove_Decal(m_pHealthDecal);

    m_pTarget = NULL;
}

void ICharacterController::Load(void)
{
    m_pShadowDecal = CSceneMgr::Instance()->Get_DecalMgr()->Add_Decal();
    m_pShadowDecal->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_DECAL);
    m_pShadowDecal->Set_Texture("shadow.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);
    
    m_pHealthDecal = CSceneMgr::Instance()->Get_DecalMgr()->Add_Decal();
    m_pHealthDecal->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_DECAL);
    m_pHealthDecal->Set_Texture("ring.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);
    m_pHealthDecal->Set_Color(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
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
    m_vPosition.y = fHeight;
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
    m_vPosition.y = fHeight;
    return true;
}

void ICharacterController::SteerRight(void)
{
    m_vRotation.y -= m_fSteerSpeed;
}

void ICharacterController::SteerLeft(void)
{
    m_vRotation.y += m_fSteerSpeed;
}


void ICharacterController::Set_Position(const glm::vec3 &_vPosition)
{
    if(m_pTrack != NULL)
    {
        m_pTrack->Set_Position(_vPosition);
    }
    
    if(m_pTower != NULL)
    {
        m_pTower->Set_Position(_vPosition);
    }
    
    if(m_pBody != NULL)
    {
        m_pBody->Set_Position(_vPosition);
    }
    
    if(m_pShadowDecal != NULL)
    {
        m_pShadowDecal->Set_Position(glm::vec3(_vPosition.x, 0.0f, _vPosition.z));
    }
    
    if(m_pHealthDecal != NULL)
    {
        m_pHealthDecal->Set_Position(glm::vec3(_vPosition.x, 0.0f, _vPosition.z));
    }
    
    m_vPosition = _vPosition;
}

void ICharacterController::_SmoothRotation(void)
{
    glm::vec3 vCurrentRotation = glm::vec3(0.0f, m_vRotation.y, 0.0f);
    glm::vec2 vRotationOnHeightMap = CMathHelper::Instance()->Get_RotationOnHeightmap(m_vPosition);
    vCurrentRotation.x = -glm::degrees(vRotationOnHeightMap.x);
    vCurrentRotation.z =  glm::degrees(vRotationOnHeightMap.y);
    m_vRotation = glm::mix(m_vRotation, vCurrentRotation, 0.25f);
}

void ICharacterController::Set_Rotation(const glm::vec3 &_vRotation)
{
    if(m_pTrack != NULL)
    {
        m_pTrack->Set_Rotation(_vRotation);
    }
    
    if(m_pTower != NULL)
    {
        m_pTower->Set_Rotation(glm::vec3(_vRotation.x, m_fTowerRotationY, _vRotation.z));
    }
    
    if(m_pBody != NULL)
    {
        m_pBody->Set_Rotation(_vRotation);
    }
    
    if(m_pShadowDecal != NULL)
    {
        m_pShadowDecal->Set_Rotation(m_vRotation);
    }
    
    if(m_pHealthDecal != NULL)
    {
        m_pHealthDecal->Set_Rotation(m_vRotation);
    }

    m_vRotation = _vRotation;
}

void ICharacterController::Shoot(void)
{
    if(m_pTower != NULL)
    {
        glm::vec3 vTowerGunOffset = m_pTower->Get_TowerGunOffset();
        CGameSceneMgr::Instance()->Get_Scene()->Get_GameShooterMgr()->CreateBullet(glm::vec3(m_vPosition.x + sinf(glm::radians(m_fTowerRotationY)) * vTowerGunOffset.x, m_vPosition.y + vTowerGunOffset.y, m_vPosition.z + cosf(glm::radians(m_fTowerRotationY)) * vTowerGunOffset.z), glm::vec3(m_vRotation.x, m_fTowerRotationY, m_vRotation.z));
    }
}

void ICharacterController::Set_Body(ICharacterController::E_CHARACTER_PART_TYPE _eType)
{
    switch (_eType)
    {
        case ICharacterController::E_CHARACTER_PART_TYPE_LIGHT :
        {
            SAFE_DELETE(m_pBody);
            m_pBody = new CTankLightBody();
            m_pBody->Load();
        }
            break;
        case ICharacterController::E_CHARACTER_PART_TYPE_MEDIUM :
        {
            SAFE_DELETE(m_pBody);
            m_pBody = new CTankMediumBody();
            m_pBody->Load();
        }
            break;
        case ICharacterController::E_CHARACTER_PART_TYPE_HEAVY :
        {
            SAFE_DELETE(m_pBody);
            m_pBody = new CTankHeavyBody();
            m_pBody->Load();
        }
            break;
        default:
            break;
    }
}

void ICharacterController::Set_Tower(ICharacterController::E_CHARACTER_PART_TYPE _eType)
{
    switch (_eType)
    {
        case ICharacterController::E_CHARACTER_PART_TYPE_LIGHT :
        {
            SAFE_DELETE(m_pTower);
            m_pTower = new CTankLightTower();
            m_pTower->Load();
        }
            break;
        case ICharacterController::E_CHARACTER_PART_TYPE_MEDIUM :
        {
            SAFE_DELETE(m_pTower);
            m_pTower = new CTankMediumTower();
            m_pTower->Load();
        }
            break;
        case ICharacterController::E_CHARACTER_PART_TYPE_HEAVY :
        {
            SAFE_DELETE(m_pTower);
            m_pTower = new CTankHeavyTower();
            m_pTower->Load();
        }
            break;
        default:
            break;
    }
}

void ICharacterController::Set_Track(ICharacterController::E_CHARACTER_PART_TYPE _eType)
{
    switch (_eType)
    {
        case ICharacterController::E_CHARACTER_PART_TYPE_LIGHT :
        {
            SAFE_DELETE(m_pTrack);
            m_pTrack = new CTankLightTrack();
            m_pTrack->Load();
        }
            break;
        case ICharacterController::E_CHARACTER_PART_TYPE_MEDIUM :
        {
            SAFE_DELETE(m_pTrack);
            m_pTrack = new CTankMediumTrack();
            m_pTrack->Load();
        }
            break;
        case ICharacterController::E_CHARACTER_PART_TYPE_HEAVY :
        {
            SAFE_DELETE(m_pTrack);
            m_pTrack = new CTankHeavyTrack();
            m_pTrack->Load();
        }
            break;
        default:
            break;
    }
}












