//
//  CCharacterControllerEnemy.cpp
//  iGaia
//
//  Created by code_oneclick on 4/20/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "CCharacterControllerEnemy.h"
#include "CWorld.h"
#include "CTimer.h"

CCharacterControllerEnemy::CCharacterControllerEnemy(void)
{
    m_pBodyModel = NULL;
    m_pTowerModel = NULL;
    m_pLeftTrackModel = NULL;
    m_pRightTrackModel = NULL;
    
    m_fMaxMoveSpeed = 0.05f;
    m_fMoveAcceleration = 0.01f;
    
    m_fMoveSpeed = 0.1f;
    m_fLeftTrackMoveSpeed = 0.0f;
    m_fRightTrackMoveSpeed = 0.0f;
    m_fSteerSpeed = 1.0f;
    
    m_eState = E_AI_STATE_NONE;
    m_iAIStateDuration = 0;
    
    m_iAIShootTimeStamp = 0;
    
    m_vMoveDirection = glm::vec3(0.0f, 0.0, 0.0f);
}

CCharacterControllerEnemy::~CCharacterControllerEnemy(void)
{
    
}

long CCharacterControllerEnemy::_Get_TimeStamp(void)
{
    return time(NULL);
}

bool CCharacterControllerEnemy::_IsStateTimeElapsed(void)
{
    long iCurrentTimeStamp = _Get_TimeStamp();
    if((iCurrentTimeStamp - m_iAIStateTimeStamp) >= m_iAIStateDuration)
    {
        return true;
    }
    return false;
}

void CCharacterControllerEnemy::Load(void)
{
    glm::vec3 vScale = glm::vec3(1.0f, 1.0f, 1.0f);
    m_pTowerModel = (CModel*)CSceneMgr::Instance()->AddCustomModel("tower_model.mdl", IResource::E_THREAD_BACKGROUND);
    m_pTowerModel->Set_Texture("model_01.pvr", 0, CTexture::E_WRAP_MODE_REPEAT);
    m_pTowerModel->Set_Scale(vScale);
    m_pTowerModel->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_UNIT);
    m_pTowerModel->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_PRE_NORMAL_DEPTH_UNIT);
    m_pTowerModel->Create_BoundingBox();
    m_pTowerModel->Set_RenderModeScreenNormalEnable(true);
    
    m_pLeftTrackModel = (CModel*)CSceneMgr::Instance()->AddCustomModel("left_track_model.mdl", IResource::E_THREAD_BACKGROUND);
    m_pLeftTrackModel->Set_Texture("model_02.pvr", 0, CTexture::E_WRAP_MODE_REPEAT);
    m_pLeftTrackModel->Set_Scale(vScale);
    m_pLeftTrackModel->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_ANIM_TEXCOORD_UNIT);
    m_pLeftTrackModel->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_PRE_NORMAL_DEPTH_UNIT);
    m_pLeftTrackModel->Create_BoundingBox();
    m_pLeftTrackModel->Set_RenderModeScreenNormalEnable(true);
    
    m_pRightTrackModel = (CModel*)CSceneMgr::Instance()->AddCustomModel("right_track_model.mdl", IResource::E_THREAD_BACKGROUND);
    m_pRightTrackModel->Set_Texture("model_02.pvr", 0, CTexture::E_WRAP_MODE_REPEAT);
    m_pRightTrackModel->Set_Scale(vScale);
    m_pRightTrackModel->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_ANIM_TEXCOORD_UNIT);
    m_pRightTrackModel->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_PRE_NORMAL_DEPTH_UNIT);
    m_pRightTrackModel->Create_BoundingBox();
    m_pRightTrackModel->Set_RenderModeScreenNormalEnable(true);
    
    m_pBodyModel = (CModel*)CSceneMgr::Instance()->AddCustomModel("base_model.mdl", IResource::E_THREAD_BACKGROUND);
    m_pBodyModel->Set_Texture("model_01.pvr", 0, CTexture::E_WRAP_MODE_REPEAT);
    m_pBodyModel->Set_Scale(vScale);
    m_pBodyModel->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_UNIT);
    m_pBodyModel->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_PRE_NORMAL_DEPTH_UNIT);
    m_pBodyModel->Create_BoundingBox();
    m_pBodyModel->Set_RenderModeScreenNormalEnable(true);
    
    m_pFireCross = CSceneMgr::Instance()->Get_SpriteMgr()->Add_SpriteCross(4, glm::vec2(256.0f, 256.0f), glm::vec2(512.0f, 512.0f));
    m_pFireCross->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_UNIT);
    m_pFireCross->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_PRE_NORMAL_DEPTH_UNIT);
    m_pFireCross->Set_Texture("model_01.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);
    
    m_pShadowDecal = CSceneMgr::Instance()->Get_DecalMgr()->Add_Decal();
    m_pShadowDecal->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_DECAL);
    m_pShadowDecal->Set_Texture("shadow.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);
    
    m_pLeftExhaustSmokeEmitter = CSceneMgr::Instance()->Get_ParticleMgr()->Add_ParticleEmitterFire(64, glm::vec2(0.033f), glm::vec2(1.25f), 1000, true);
    m_pLeftExhaustSmokeEmitter->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_PARTICLE_EMITTER);
    m_pLeftExhaustSmokeEmitter->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_PRE_NORMAL_DEPTH_PARTICLE_EMITTER);
    m_pLeftExhaustSmokeEmitter->Set_Texture("smoke.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);
    //m_pLeftExhaustSmokeEmitter->Set_Batching(true, "smoke-emitter");
    
    m_pRightExhaustSmokeEmitter = CSceneMgr::Instance()->Get_ParticleMgr()->Add_ParticleEmitterFire(64, glm::vec2(0.033f), glm::vec2(1.25f), 1000, true);
    m_pRightExhaustSmokeEmitter->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_PARTICLE_EMITTER);
    m_pRightExhaustSmokeEmitter->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_PRE_NORMAL_DEPTH_PARTICLE_EMITTER);
    m_pRightExhaustSmokeEmitter->Set_Texture("smoke.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);
    //m_pRightExhaustSmokeEmitter->Set_Batching(true, "smoke-emitter");
    
    m_pLeftTrackSmokeEmitter = CSceneMgr::Instance()->Get_ParticleMgr()->Add_ParticleEmitterFire(64, glm::vec2(0.05f), glm::vec2(2.5f), 1000, true);
    m_pLeftTrackSmokeEmitter->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_PARTICLE_EMITTER);
    m_pLeftTrackSmokeEmitter->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_PRE_NORMAL_DEPTH_PARTICLE_EMITTER);
    m_pLeftTrackSmokeEmitter->Set_Texture("fire.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);
    //m_pLeftTrackSmokeEmitter->Set_Batching(true, "fire-emitter");
    
    m_pRightTrackSmokeEmitter = CSceneMgr::Instance()->Get_ParticleMgr()->Add_ParticleEmitterFire(64, glm::vec2(0.05f), glm::vec2(2.5f), 1000, true);
    m_pRightTrackSmokeEmitter->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_PARTICLE_EMITTER);
    m_pRightTrackSmokeEmitter->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_PRE_NORMAL_DEPTH_PARTICLE_EMITTER);
    m_pRightTrackSmokeEmitter->Set_Texture("fire.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);
    //m_pRightTrackSmokeEmitter->Set_Batching(true, "fire-emitter");
    
    m_pTowerSmokeEmitter = CSceneMgr::Instance()->Get_ParticleMgr()->Add_ParticleEmitterFire(64, glm::vec2(0.05f), glm::vec2(2.5f), 1000, true);
    m_pTowerSmokeEmitter->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_PARTICLE_EMITTER);
    m_pTowerSmokeEmitter->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_PRE_NORMAL_DEPTH_PARTICLE_EMITTER);
    m_pTowerSmokeEmitter->Set_Texture("fire.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);
    //m_pTowerSmokeEmitter->Set_Batching(true, "fire-emitter");
    
    m_pLeftTrackFireEmitter = CSceneMgr::Instance()->Get_ParticleMgr()->Add_ParticleEmitterFire(64, glm::vec2(0.05f), glm::vec2(2.5f), 1000, true);
    m_pLeftTrackFireEmitter->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_PARTICLE_EMITTER);
    m_pLeftTrackFireEmitter->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_PRE_NORMAL_DEPTH_PARTICLE_EMITTER);
    m_pLeftTrackFireEmitter->Set_Texture("fire.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);
    //m_pLeftTrackFireEmitter->Set_Batching(true, "fire-emitter");
    
    m_pRightTrackFireEmitter = CSceneMgr::Instance()->Get_ParticleMgr()->Add_ParticleEmitterFire(64, glm::vec2(0.05f), glm::vec2(2.5f), 1000, true);
    m_pRightTrackFireEmitter->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_PARTICLE_EMITTER);
    m_pRightTrackFireEmitter->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_PRE_NORMAL_DEPTH_PARTICLE_EMITTER);
    m_pRightTrackFireEmitter->Set_Texture("fire.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);
    //m_pRightTrackFireEmitter->Set_Batching(true, "fire-emitter");
    
    m_pTowerFireEmitter = CSceneMgr::Instance()->Get_ParticleMgr()->Add_ParticleEmitterFire(64, glm::vec2(0.05f), glm::vec2(2.5f), 1000, true);
    m_pTowerFireEmitter->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_PARTICLE_EMITTER);
    m_pTowerFireEmitter->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_PRE_NORMAL_DEPTH_PARTICLE_EMITTER);
    m_pTowerFireEmitter->Set_Texture("fire.pvr", 0, CTexture::E_WRAP_MODE_CLAMP);
    //m_pTowerFireEmitter->Set_Batching(true, "fire-emitter");
    
    CSceneMgr::Instance()->AddEventListener(m_pBodyModel, CEventMgr::E_EVENT_TOUCH);
    m_pBodyModel->Add_DelegateOwner(this);
    CWorld::Instance()->Get_Level()->Get_Model()->Add_DelegateOwner(this);
}

void CCharacterControllerEnemy::OnTouchEvent(ITouchDelegate* _pDelegateOwner)
{

}

void CCharacterControllerEnemy::Set_AIState(E_AI_STATE _eState, long _iAIStateDuration)
{
    m_eState = _eState;
    m_iAIStateDuration = _iAIStateDuration;
    m_iAIStateTimeStamp = _Get_TimeStamp();
    if(m_eState == E_AI_STATE_MOVE)
    {
        m_vMoveDirection = glm::normalize(m_vPosition - m_vMovePoint);
    }
}

void CCharacterControllerEnemy::Shoot(void)
{
    if(m_pTarget == NULL)
    {
        return;
    }
    
    glm::vec2 vPoint_01 = glm::vec2(m_vPosition.x, m_vPosition.z);
    glm::vec2 vPoint_02 = glm::vec2(m_pTarget->Get_Position().x, m_pTarget->Get_Position().z);
    
    float fDistanceToTargetPoint = glm::distance(vPoint_01, vPoint_02);
    
    int iAICurrentShootTimeStamp = CTimer::Instance()->Get_TickCount();
    
    if((iAICurrentShootTimeStamp - m_iAIShootTimeStamp > k_AI_SHOOT_INTERVAL) && fDistanceToTargetPoint < k_AI_SHOOT_DISTANCE)
    {
        CWorld::Instance()->Get_GameShooterMgr()->CreateBullet(glm::vec3(m_vPosition.x + sinf(glm::radians(m_fTowerRotationY)) * 1.33f, m_vPosition.y + 1.33f, m_vPosition.z + cosf(glm::radians(m_fTowerRotationY)) * 1.33f), m_pTowerModel->Get_Rotation());
        m_iAIShootTimeStamp = iAICurrentShootTimeStamp;
    }
}

void CCharacterControllerEnemy::Update(void)
{
    glm::vec2 vRightTrackTexCoordOffset = glm::vec2(0.0f, 0.0f);
    glm::vec2 vLeftTrackTexCoordOffset  = glm::vec2(0.0f, 0.0f);
    float fTrackTexCoordOffsetSteerFactor = 0.1f;
      
    switch (m_eState)
    {
        case E_AI_STATE_NONE:
            std::cout<<"[CCharacterControllerEnemy::Update]"<<"state -> AI_STATE_NONE"<<std::endl;
            m_pLeftExhaustSmokeEmitter->Stop();
            m_pRightExhaustSmokeEmitter->Stop();
            break;
        case E_AI_STATE_STAND:
        {
            m_pLeftExhaustSmokeEmitter->Stop();
            m_pRightExhaustSmokeEmitter->Stop();
            std::cout<<"[CCharacterControllerEnemy::Update]"<<"state -> E_AI_STATE_STAND"<<std::endl;
        }
            break;
        case E_AI_STATE_MOVE:
        {
            glm::vec2 vPoint_01 = glm::vec2(m_vPosition.x, m_vPosition.z);
            glm::vec2 vPoint_02 = glm::vec2(m_vMovePoint.x, m_vMovePoint.z);
            
            if(glm::distance(vPoint_01, vPoint_02) < 1.0f)
            {
                m_eState = E_AI_STATE_NONE;
                break;
            }
            
            float fAngleToMovePoint =  glm::degrees(_GetRotationBetweenPointsDot(vPoint_01, vPoint_02));
            if(fabs(fAngleToMovePoint - m_vRotation.y) > 45.0f)
            {
                SteerLeft();
            }
            else
            {
                if(fabs(fAngleToMovePoint - m_vRotation.y) > 5.0f)
                {
                    SteerLeft();
                }
                MoveForward();
            }
            
            vRightTrackTexCoordOffset.x = m_pRightTrackModel->Get_TexCoordOffset().x + fTrackTexCoordOffsetSteerFactor;
            vLeftTrackTexCoordOffset.x = m_pLeftTrackModel->Get_TexCoordOffset().x + fTrackTexCoordOffsetSteerFactor; 
                       
            m_vRotation.y =  glm::degrees(_GetRotationBetweenPoints(m_vMovePoint, m_vPosition) - 1.57f);
            
            m_pLeftExhaustSmokeEmitter->Start();
            m_pRightExhaustSmokeEmitter->Start();
        }
            break;
        default:
            break;
    }
    
    m_pLeftTrackModel->Set_TexCoordOffset(vLeftTrackTexCoordOffset);
    m_pRightTrackModel->Set_TexCoordOffset(vRightTrackTexCoordOffset);
    
    m_fTowerRotationY = m_pTowerModel->Get_Rotation().y;
    Shoot();
    
    Set_Position(m_vPosition);
    _SmoothRotation();
    Set_Rotation(m_vRotation);
    
    glm::vec3 vTargetPoint;
    if(m_pTarget != NULL)
    {
        vTargetPoint = m_pTarget->Get_Position();
    }
    else
    {
        vTargetPoint = m_vMovePoint;
    }
    
    float fAngleToTargetPoint = _GetRotationBetweenPoints(m_vPosition, vTargetPoint);
    m_pTowerModel->Set_Rotation(glm::vec3(m_vRotation.x, glm::degrees(fAngleToTargetPoint + 1.57f), m_vRotation.z));
}




