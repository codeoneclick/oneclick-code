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
#include "CTimer.h"

CCharacterControllerPlayer::CCharacterControllerPlayer(void)
{
    m_pBodyModel = NULL;
    m_pTowerModel = NULL;
    //m_pLeftTrackModel = NULL;
    //m_pRightTrackModel = NULL;
    m_pTrack = NULL;
    
    m_fMaxMoveSpeed = 0.2f;
    m_fMoveAcceleration = 0.01f;
    
    m_fMoveSpeed = 0.0f;
    m_fLeftTrackMoveSpeed = 0.0f;
    m_fRightTrackMoveSpeed = 0.0f;
    m_fSteerSpeed = 2.0f;
    m_fTowerSteerSpeed = 4.0f;
    
    m_fTowerRotationY = 0.0f;
    m_iLastCrossFireTime = 0;
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
    m_pTowerModel->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_MODEL);
    m_pTowerModel->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_MODEL_ND);
    m_pTowerModel->Create_BoundingBox();
    m_pTowerModel->Set_RenderMode(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, true);
    
    m_pTrack = new CTankLightTrack();
    m_pTrack->Load();
    
    /*m_pLeftTrackModel = (CModel*)CSceneMgr::Instance()->AddCustomModel("left_track_model.mdl", IResource::E_THREAD_BACKGROUND);
    m_pLeftTrackModel->Set_Texture("model_02.pvr", 0, CTexture::E_WRAP_MODE_REPEAT);
    m_pLeftTrackModel->Set_Scale(vScale);
    m_pLeftTrackModel->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_MODEL);
    m_pLeftTrackModel->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_MODEL_ND);
    m_pLeftTrackModel->Create_BoundingBox();
    m_pLeftTrackModel->Set_RenderMode(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, true);

    m_pRightTrackModel = (CModel*)CSceneMgr::Instance()->AddCustomModel("right_track_model.mdl", IResource::E_THREAD_BACKGROUND);
    m_pRightTrackModel->Set_Texture("model_02.pvr", 0, CTexture::E_WRAP_MODE_REPEAT);
    m_pRightTrackModel->Set_Scale(vScale);
    m_pRightTrackModel->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_MODEL);
    m_pRightTrackModel->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_MODEL_ND);
    m_pRightTrackModel->Create_BoundingBox();
    m_pRightTrackModel->Set_RenderMode(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, true);*/
    
    m_pBodyModel = (CModel*)CSceneMgr::Instance()->AddCustomModel("base_model.mdl", IResource::E_THREAD_BACKGROUND);
    m_pBodyModel->Set_Texture("model_01.pvr", 0, CTexture::E_WRAP_MODE_REPEAT);
    m_pBodyModel->Set_Scale(vScale);
    m_pBodyModel->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_MODEL);
    m_pBodyModel->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_MODEL_ND);
    m_pBodyModel->Create_BoundingBox();
    m_pBodyModel->Set_RenderMode(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, true);
    
    m_pFireCross = CSceneMgr::Instance()->Get_SpriteMgr()->Add_SpriteCross(4, glm::vec2(256.0f, 256.0f), glm::vec2(512.0f, 512.0f));
    m_pFireCross->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_MODEL);
    m_pFireCross->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_MODEL_ND);
    m_pFireCross->Set_Texture("model_01.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);
    
    m_pShadowDecal = CSceneMgr::Instance()->Get_DecalMgr()->Add_Decal();
    m_pShadowDecal->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_DECAL);
    m_pShadowDecal->Set_Texture("shadow.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);
    
    m_pHealthDecal = CSceneMgr::Instance()->Get_DecalMgr()->Add_Decal();
    m_pHealthDecal->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_DECAL);
    m_pHealthDecal->Set_Texture("ring.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);
    m_pHealthDecal->Set_Color(glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
    
    m_pLeftExhaustSmokeEmitter = CSceneMgr::Instance()->Get_ParticleMgr()->Add_ParticleEmitterFire(32, glm::vec2(0.025f), glm::vec2(0.45f), 2000, true);
    m_pLeftExhaustSmokeEmitter->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_PARTICLE);
    m_pLeftExhaustSmokeEmitter->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_PARTICLE_ND);
    m_pLeftExhaustSmokeEmitter->Set_Texture("smoke.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);
    //m_pLeftExhaustSmokeEmitter->Set_Batching(true, "smoke-emitter");
    
    m_pRightExhaustSmokeEmitter = CSceneMgr::Instance()->Get_ParticleMgr()->Add_ParticleEmitterFire(32, glm::vec2(0.025f), glm::vec2(0.45f), 1000, true);
    m_pRightExhaustSmokeEmitter->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_PARTICLE);
    m_pRightExhaustSmokeEmitter->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_PARTICLE_ND);
    m_pRightExhaustSmokeEmitter->Set_Texture("smoke.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);
    //m_pRightExhaustSmokeEmitter->Set_Batching(true, "smoke-emitter");
    
    /*m_pLeftTrackSmokeEmitter = CSceneMgr::Instance()->Get_ParticleMgr()->Add_ParticleEmitterFire(32, glm::vec2(0.05f), glm::vec2(2.5f), 1000, true);
    m_pLeftTrackSmokeEmitter->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_PARTICLE);
    m_pLeftTrackSmokeEmitter->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_PARTICLE_ND);
    m_pLeftTrackSmokeEmitter->Set_Texture("fire.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);
    //m_pLeftTrackSmokeEmitter->Set_Batching(true, "fire-emitter");
    
    m_pRightTrackSmokeEmitter = CSceneMgr::Instance()->Get_ParticleMgr()->Add_ParticleEmitterFire(32, glm::vec2(0.05f), glm::vec2(2.5f), 1000, true);
    m_pRightTrackSmokeEmitter->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_PARTICLE);
    m_pRightTrackSmokeEmitter->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_PARTICLE_ND);
    m_pRightTrackSmokeEmitter->Set_Texture("fire.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);
    //m_pRightTrackSmokeEmitter->Set_Batching(true, "fire-emitter");
    
    m_pTowerSmokeEmitter = CSceneMgr::Instance()->Get_ParticleMgr()->Add_ParticleEmitterFire(32, glm::vec2(0.05f), glm::vec2(2.5f), 1000, true);
    m_pTowerSmokeEmitter->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_PARTICLE);
    m_pTowerSmokeEmitter->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_PARTICLE_ND);
    m_pTowerSmokeEmitter->Set_Texture("fire.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);
    //m_pTowerSmokeEmitter->Set_Batching(true, "fire-emitter");
    
    m_pLeftTrackFireEmitter = CSceneMgr::Instance()->Get_ParticleMgr()->Add_ParticleEmitterFire(32, glm::vec2(0.05f), glm::vec2(2.5f), 1000, true);
    m_pLeftTrackFireEmitter->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_PARTICLE);
    m_pLeftTrackFireEmitter->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_PARTICLE_ND);
    m_pLeftTrackFireEmitter->Set_Texture("fire.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);
    //m_pLeftTrackFireEmitter->Set_Batching(true, "fire-emitter");
    
    m_pRightTrackFireEmitter = CSceneMgr::Instance()->Get_ParticleMgr()->Add_ParticleEmitterFire(32, glm::vec2(0.05f), glm::vec2(2.5f), 1000, true);
    m_pRightTrackFireEmitter->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_PARTICLE);
    m_pRightTrackFireEmitter->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_PARTICLE_ND);
    m_pRightTrackFireEmitter->Set_Texture("fire.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);
    //m_pRightTrackFireEmitter->Set_Batching(true, "fire-emitter");*/
    
    m_pTowerFireEmitter = CSceneMgr::Instance()->Get_ParticleMgr()->Add_ParticleEmitterFire(32, glm::vec2(0.05f), glm::vec2(2.5f), 1000, true);
    m_pTowerFireEmitter->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_PARTICLE);
    m_pTowerFireEmitter->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_PARTICLE_ND);
    m_pTowerFireEmitter->Set_Texture("fire.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);
    //m_pTowerFireEmitter->Set_Batching(true, "fire-emitter");

    CSceneMgr::Instance()->AddEventListener(m_pBodyModel, CEventMgr::E_EVENT_TOUCH);
    m_pBodyModel->Add_DelegateOwner(this);
    CWorld::Instance()->Get_Level()->Get_Model()->Add_DelegateOwner(this);
    
    //m_pLeftTrackFireEmitter->Start();
    //m_pRightTrackFireEmitter->Start();
    //m_pTowerFireEmitter->Start();
}

void CCharacterControllerPlayer::OnTouchEvent(ITouchDelegate* _pDelegateOwner)
{
    //CSceneMgr::Instance()->Get_CollisionMgr()->Get_Touch3DPoint();
}

void CCharacterControllerPlayer::Update(void)
{   
    m_fMoveSpeed = m_fMaxMoveSpeed;
    
    //glm::vec2 vRightTrackTexCoordOffset = glm::vec2(0.0f, 0.0f);
    //glm::vec2 vLeftTrackTexCoordOffset  = glm::vec2(0.0f, 0.0f);
    float fTrackTexCoordOffsetMoveFactor  = 0.2f;
    float fTrackTexCoordOffsetSteerFactor = 0.1f;
    
    ICamera* pCamera = CSceneMgr::Instance()->Get_Camera();
    switch (m_eMoveState)
    {
        case ICharacterController::E_CHARACTER_CONTROLLER_MOVE_STATE_NONE:
            if(pCamera->Get_FovY() > k_CAMERA_FOV_Y_STATE_NONE)
            {
                pCamera->Set_FovY(pCamera->Get_FovY() - k_CAMERA_FOV_Y_DELTA_STATE_NONE);
            }
            m_pLeftExhaustSmokeEmitter->Stop();
            m_pRightExhaustSmokeEmitter->Stop();
            break;
        case ICharacterController::E_CHARACTER_CONTROLLER_MOVE_STATE_FORWARD:
            
            MoveForward();
           
            m_pTrack->Move_LeftTrack(-fTrackTexCoordOffsetMoveFactor);
            m_pTrack->Move_RightTrack(-fTrackTexCoordOffsetMoveFactor);
            //vRightTrackTexCoordOffset.x = m_pRightTrackModel->Get_TexCoordOffset().x - fTrackTexCoordOffsetMoveFactor;
            //vLeftTrackTexCoordOffset.x = m_pLeftTrackModel->Get_TexCoordOffset().x - fTrackTexCoordOffsetMoveFactor;
            
            if(pCamera->Get_FovY() < k_CAMERA_FOV_Y_STATE_FORWARD)
            {
                pCamera->Set_FovY(pCamera->Get_FovY() + k_CAMERA_FOV_Y_DELTA_STATE_FORWARD);
            }
            m_pLeftExhaustSmokeEmitter->Start();
            m_pRightExhaustSmokeEmitter->Start();
            break;
        case ICharacterController::E_CHARACTER_CONTROLLER_MOVE_STATE_BACKWARD:
            
            MoveBackward();
            
            m_pTrack->Move_LeftTrack(fTrackTexCoordOffsetMoveFactor);
            m_pTrack->Move_RightTrack(fTrackTexCoordOffsetMoveFactor);
            //vRightTrackTexCoordOffset.x = m_pRightTrackModel->Get_TexCoordOffset().x + fTrackTexCoordOffsetMoveFactor;
            //vLeftTrackTexCoordOffset.x = m_pLeftTrackModel->Get_TexCoordOffset().x + fTrackTexCoordOffsetMoveFactor;
            
            if(pCamera->Get_FovY() > k_CAMERA_FOV_Y_STATE_BACKWARD)
            {
                pCamera->Set_FovY(pCamera->Get_FovY() - k_CAMERA_FOV_Y_DELTA_STATE_BACKWARD);
            }
            m_pLeftExhaustSmokeEmitter->Start();
            m_pRightExhaustSmokeEmitter->Start();
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
            
            m_pTrack->Move_LeftTrack(-fTrackTexCoordOffsetMoveFactor);
            m_pTrack->Move_RightTrack(fTrackTexCoordOffsetMoveFactor);
            //vRightTrackTexCoordOffset.x = m_pRightTrackModel->Get_TexCoordOffset().x + fTrackTexCoordOffsetSteerFactor;
            //vLeftTrackTexCoordOffset.x = m_pLeftTrackModel->Get_TexCoordOffset().x - fTrackTexCoordOffsetSteerFactor;
            
            m_pLeftExhaustSmokeEmitter->Start();
            m_pRightExhaustSmokeEmitter->Start();
            
            break;
        case ICharacterController::E_CHARACTER_CONTROLLER_STEER_STATE_RIGHT:
            
            SteerRight();
            
            m_pTrack->Move_LeftTrack(fTrackTexCoordOffsetMoveFactor);
            m_pTrack->Move_RightTrack(-fTrackTexCoordOffsetMoveFactor);
            //vRightTrackTexCoordOffset.x = m_pRightTrackModel->Get_TexCoordOffset().x - fTrackTexCoordOffsetSteerFactor;
            //vLeftTrackTexCoordOffset.x = m_pLeftTrackModel->Get_TexCoordOffset().x + fTrackTexCoordOffsetSteerFactor;
            
            m_pLeftExhaustSmokeEmitter->Start();
            m_pRightExhaustSmokeEmitter->Start();
            
            break;
        default:
            break;
    }
    
    switch (m_eSteerTowerState)
    {
        case ICharacterController::E_CHARACTER_CONTROLLER_STEER_STATE_TOWER_NONE:
            
            break;
        case ICharacterController::E_CHARACTER_CONTROLLER_STEER_STATE_TOWER_RIGHT:
        {
            m_fTowerRotationY += m_fTowerSteerSpeed;
        }
            break;
        case ICharacterController::E_CHARACTER_CONTROLLER_STEER_STATE_TOWER_LEFT:
        {
            m_fTowerRotationY -= m_fTowerSteerSpeed;
        }
            break;
            
        default:
            break;
    }
    
    m_pTrack->Update();
    
    //m_pLeftTrackModel->Set_TexCoordOffset(vLeftTrackTexCoordOffset);
    //m_pRightTrackModel->Set_TexCoordOffset(vRightTrackTexCoordOffset);

    Set_Position(m_vPosition);
    _SmoothRotation();
    Set_Rotation(m_vRotation);
    
    int iCurrentCrossFireTime = CTimer::Instance()->Get_TickCount();
    if(iCurrentCrossFireTime - m_iLastCrossFireTime > k_CROSS_FIRE_TIME_MAX)
    {
        m_pFireCross->Disable();
    }
}










