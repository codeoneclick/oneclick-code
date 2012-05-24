//
//  CCharacterControllerPlayer.cpp
//  iGaia
//
//  Created by sergey.sergeev on 2/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CCharacterControllerPlayer.h"
#include "CSceneMgr.h"
#include "CWorld.h"
#include "CLandscape.h"

CCharacterControllerPlayer::CCharacterControllerPlayer(void)
{
    m_pBodyModel = NULL;
    m_pTowerModel = NULL;
    m_pLeftTrackModel = NULL;
    m_pRightTrackModel = NULL;
    //m_pShadow = NULL;
    
    m_fMaxMoveSpeed = 0.2f;
    m_fMoveAcceleration = 0.01f;
    
    m_fMoveSpeed = 0.0f;
    m_fLeftTrackMoveSpeed = 0.0f;
    m_fRightTrackMoveSpeed = 0.0f;
    m_fSteerSpeed = 2.0f;
    
    m_vTowerModelTarget = glm::vec3(0.0f, 0.0f, 0.0f);
}

CCharacterControllerPlayer::~CCharacterControllerPlayer(void)
{
    
}

void CCharacterControllerPlayer::Load(void)
{
    
    glm::vec3 vScale = glm::vec3(1.0f, 1.0f, 1.0f);
    m_pTowerModel = (CModel*)CSceneMgr::Instance()->AddCustomModel("tower_model.mdl", IResource::E_THREAD_BACKGROUND);
    m_pTowerModel->Set_Texture("model_01.pvr", 0, CTexture::E_WRAP_MODE_REPEAT);
    m_pTowerModel->Set_Scale(vScale);
    m_pTowerModel->Set_Shader(INode::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_UNIT);
    m_pTowerModel->Set_Shader(INode::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_PRE_NORMAL_DEPTH_UNIT);
    m_pTowerModel->Create_BoundingBox();
    m_pTowerModel->Set_RenderModeScreenNormalEnable(true);
    //m_pTowerModel->Set_RenderModeShadowMapEnable(true);
    
    m_pLeftTrackModel = (CModel*)CSceneMgr::Instance()->AddCustomModel("left_track_model.mdl", IResource::E_THREAD_BACKGROUND);
    m_pLeftTrackModel->Set_Texture("model_02.pvr", 0, CTexture::E_WRAP_MODE_REPEAT);
    m_pLeftTrackModel->Set_Scale(vScale);
    m_pLeftTrackModel->Set_Shader(INode::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_ANIM_TEXCOORD_UNIT);
    m_pLeftTrackModel->Set_Shader(INode::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_PRE_NORMAL_DEPTH_UNIT);
    m_pLeftTrackModel->Create_BoundingBox();
    m_pLeftTrackModel->Set_RenderModeScreenNormalEnable(true);
    //m_pLeftTrackModel->Set_RenderModeShadowMapEnable(true);

    m_pRightTrackModel = (CModel*)CSceneMgr::Instance()->AddCustomModel("right_track_model.mdl", IResource::E_THREAD_BACKGROUND);
    m_pRightTrackModel->Set_Texture("model_02.pvr", 0, CTexture::E_WRAP_MODE_REPEAT);
    m_pRightTrackModel->Set_Scale(vScale);
    m_pRightTrackModel->Set_Shader(INode::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_ANIM_TEXCOORD_UNIT);
    m_pRightTrackModel->Set_Shader(INode::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_PRE_NORMAL_DEPTH_UNIT);
    m_pRightTrackModel->Create_BoundingBox();
    m_pRightTrackModel->Set_RenderModeScreenNormalEnable(true);
    //m_pRightTrackModel->Set_RenderModeShadowMapEnable(true);
    
    m_pBodyModel = (CModel*)CSceneMgr::Instance()->AddCustomModel("base_model.mdl", IResource::E_THREAD_BACKGROUND);
    m_pBodyModel->Set_Texture("model_01.pvr", 0, CTexture::E_WRAP_MODE_REPEAT);
    m_pBodyModel->Set_Scale(vScale);
    m_pBodyModel->Set_Shader(INode::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_UNIT);
    m_pBodyModel->Set_Shader(INode::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_PRE_NORMAL_DEPTH_UNIT);
    m_pBodyModel->Create_BoundingBox();
    m_pBodyModel->Set_RenderModeScreenNormalEnable(true);
    //m_pBodyModel->Set_RenderModeShadowMapEnable(true);
    
    m_pExplosionEmitter = CSceneMgr::Instance()->Get_ParticleMgr()->Add_ParticleEmitter();
    m_pExplosionEmitter->Set_Shader(INode::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_UNIT);
    m_pExplosionEmitter->Set_Texture("fire.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);
    m_pExplosionEmitter->Set_Position(glm::vec3(0.0f, 0.33f, 0.0f));
    
    m_pShadowDecal = CSceneMgr::Instance()->Get_DecalMgr()->Add_Decal();
    m_pShadowDecal->Set_Shader(INode::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_DECAL);
    m_pShadowDecal->Set_Texture("shadow.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);

    CSceneMgr::Instance()->AddEventListener(m_pBodyModel, CEventMgr::E_EVENT_TOUCH);
    CSceneMgr::Instance()->Get_PhysicMgr()->Add_CollisionModelAsVehicle(m_pBodyModel, 2000, glm::vec3(2.0f, 2.0f, 2.0f));
    CSceneMgr::Instance()->Get_PhysicMgr()->Add_WheelToVehicleModel(m_pBodyModel, glm::vec3(-1.0f, 1.0f,  1.0f));
    CSceneMgr::Instance()->Get_PhysicMgr()->Add_WheelToVehicleModel(m_pBodyModel, glm::vec3(-1.0f, 1.0f, -1.0f));
    CSceneMgr::Instance()->Get_PhysicMgr()->Add_WheelToVehicleModel(m_pBodyModel, glm::vec3( 1.0f, 1.0f, -1.0f));
    CSceneMgr::Instance()->Get_PhysicMgr()->Add_WheelToVehicleModel(m_pBodyModel, glm::vec3( 1.0f, 1.0f,  1.0f));
    m_pBodyModel->Add_DelegateOwner(this);
    CWorld::Instance()->Get_Level()->Get_Model()->Add_DelegateOwner(this);
}

void CCharacterControllerPlayer::Set_Position(const glm::vec3 &_vPosition)
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
    m_vPosition = _vPosition;
}

void CCharacterControllerPlayer::Set_Rotation(const glm::vec3 &_vRotation)
{
    if(m_pBodyModel != NULL)
    {
        m_pBodyModel->Set_Rotation(_vRotation);
    }
    if(m_pTowerModel != NULL)
    {
        m_pTowerModel->Set_Rotation(_vRotation);
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
    m_vRotation = _vRotation;
}

void CCharacterControllerPlayer::OnTouchEvent(ITouchDelegate* _pDelegateOwner)
{
    m_vTowerModelTarget = CSceneMgr::Instance()->Get_CollisionMgr()->Get_Touch3DPoint();
}

void CCharacterControllerPlayer::Update(void)
{
    switch (m_eLeftTrackState)
    {
        case E_CHARACTER_CONTROLLER_STATE_NONE:
        {
            if(m_fLeftTrackMoveSpeed > 0.0f)
            {
                m_fLeftTrackMoveSpeed -= m_fMoveAcceleration;
            }
            else if(m_fLeftTrackMoveSpeed < 0.0f)
            {
                m_fLeftTrackMoveSpeed += m_fMoveAcceleration;
            }
        }
            break;
        case E_CHARACTER_CONTROLLER_STATE_INC_MOVE:
            if(m_fLeftTrackMoveSpeed < m_fMaxMoveSpeed)
            {
                m_fLeftTrackMoveSpeed += m_fMoveAcceleration;
            }
            break;
        case E_CHARACTER_CONTROLLER_STATE_DEC_MOVE:
            if(m_fLeftTrackMoveSpeed > -m_fMaxMoveSpeed)
            {
                m_fLeftTrackMoveSpeed -= m_fMoveAcceleration;
            }
            break;
        default:
            break;
    }
    
    switch (m_eRightTrackState)
    {
        case E_CHARACTER_CONTROLLER_STATE_NONE:
        {
            if(m_fRightTrackMoveSpeed > 0.0f)
            {
                m_fRightTrackMoveSpeed -= m_fMoveAcceleration;
            }
            else if(m_fRightTrackMoveSpeed < 0.0f)
            {
                m_fRightTrackMoveSpeed += m_fMoveAcceleration;
            }
        }
            break;
        case E_CHARACTER_CONTROLLER_STATE_INC_MOVE:
            if(m_fRightTrackMoveSpeed < m_fMaxMoveSpeed)
            {
                m_fRightTrackMoveSpeed += m_fMoveAcceleration;
            }
            break;
        case E_CHARACTER_CONTROLLER_STATE_DEC_MOVE:
            if(m_fRightTrackMoveSpeed > -m_fMaxMoveSpeed)
            {
                m_fRightTrackMoveSpeed -= m_fMoveAcceleration;
            }
            break;
        default:
            break;
    }
    
    m_fMoveSpeed = fabs(m_fLeftTrackMoveSpeed + m_fRightTrackMoveSpeed);
    
    if((m_fLeftTrackMoveSpeed + m_fRightTrackMoveSpeed) > 0.0f)
    {
        MoveForward();
    }
    else if ((m_fLeftTrackMoveSpeed + m_fRightTrackMoveSpeed) < 0.0f)
    {
        MoveBackward();
    }
    
    if(m_fLeftTrackMoveSpeed > m_fRightTrackMoveSpeed)
    {
        SteerLeft();
    }
    else if(m_fRightTrackMoveSpeed > m_fLeftTrackMoveSpeed)
    {
        SteerRight();
    }
    
    m_fMoveSpeed = m_fMaxMoveSpeed;
    
    glm::vec2 vRightTrackTexCoordOffset = glm::vec2(0.0f, 0.0f);
    glm::vec2 vLeftTrackTexCoordOffset  = glm::vec2(0.0f, 0.0f);
    float fTrackTexCoordOffsetMoveFactor  = 0.2f;
    float fTrackTexCoordOffsetSteerFactor = 0.1f;
    
    ICamera* pCamera = CSceneMgr::Instance()->Get_Camera();
    switch (m_eMoveState)
    {
        case ICharacterController::E_CHARACTER_CONTROLLER_MOVE_STATE_NONE:
            if(pCamera->Get_FovY() > 45.0f)
            {
                //pCamera->Set_FovY(pCamera->Get_FovY() - 0.66f);
            }
            break;
        case ICharacterController::E_CHARACTER_CONTROLLER_MOVE_STATE_FORWARD:
            
            MoveForward();
           
            vRightTrackTexCoordOffset.x = m_pRightTrackModel->Get_TexCoordOffset().x - fTrackTexCoordOffsetMoveFactor;
            vLeftTrackTexCoordOffset.x = m_pLeftTrackModel->Get_TexCoordOffset().x - fTrackTexCoordOffsetMoveFactor;
            
            if(pCamera->Get_FovY() < 55.0f)
            {
                //pCamera->Set_FovY(pCamera->Get_FovY() + 0.33f);
            }
            
            break;
        case ICharacterController::E_CHARACTER_CONTROLLER_MOVE_STATE_BACKWARD:
            
            MoveBackward();
            
            vRightTrackTexCoordOffset.x = m_pRightTrackModel->Get_TexCoordOffset().x + fTrackTexCoordOffsetMoveFactor;
            vLeftTrackTexCoordOffset.x = m_pLeftTrackModel->Get_TexCoordOffset().x + fTrackTexCoordOffsetMoveFactor;
            
            if(pCamera->Get_FovY() > 45.0f)
            {
                //pCamera->Set_FovY(pCamera->Get_FovY() - 0.99f);
            }
            
            break;
        default:
            break;
    }
    
    switch (m_eSteerState)
    {
        case ICharacterController::E_CHARACTER_CONTROLLER_STEER_STATE_NONE:
            
            break;
        case ICharacterController::E_CHARACTER_CONTROLLER_STEER_STATE_LEFT:
            
            SteerLeft();
            
            vRightTrackTexCoordOffset.x = m_pRightTrackModel->Get_TexCoordOffset().x + fTrackTexCoordOffsetSteerFactor;
            vLeftTrackTexCoordOffset.x = m_pLeftTrackModel->Get_TexCoordOffset().x - fTrackTexCoordOffsetSteerFactor;
            
            break;
        case ICharacterController::E_CHARACTER_CONTROLLER_STEER_STATE_RIGHT:
            
            SteerRight();
            
            vRightTrackTexCoordOffset.x = m_pRightTrackModel->Get_TexCoordOffset().x - fTrackTexCoordOffsetSteerFactor;
            vLeftTrackTexCoordOffset.x = m_pLeftTrackModel->Get_TexCoordOffset().x + fTrackTexCoordOffsetSteerFactor;
            
            break;
        default:
            break;
    }
    
    m_pLeftTrackModel->Set_TexCoordOffset(vLeftTrackTexCoordOffset);
    m_pRightTrackModel->Set_TexCoordOffset(vRightTrackTexCoordOffset);

    m_vPosition.y = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_HeightValue(m_vPosition.x, m_vPosition.z);
    Set_Position(m_vPosition);
    glm::vec3 vCurrentRotation = glm::vec3(0.0f, m_vRotation.y, 0.0f);
    glm::vec2 vRotationOnHeightMap = _Get_RotationOnHeightmap(m_vPosition);
    vCurrentRotation.x = -glm::degrees(vRotationOnHeightMap.x);
    vCurrentRotation.z =  glm::degrees(vRotationOnHeightMap.y);
    m_vRotation = glm::mix(m_vRotation, vCurrentRotation, 0.25f);
    Set_Rotation(m_vRotation);
    
    //m_pExplosionEmitter->Set_Position(m_vPosition);
    
    float fTowerTargetAngle = _GetRotationBetweenPoints(m_vPosition, m_vTowerModelTarget);
    m_pTowerModel->Set_Rotation(glm::vec3(m_vRotation.x, glm::degrees(fTowerTargetAngle + 1.57f), m_vRotation.z));
}










