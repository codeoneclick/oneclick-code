//
//  CCharacterControllerEnemy.cpp
//  iGaia
//
//  Created by code_oneclick on 4/20/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "CCharacterControllerEnemy.h"
#include "CWorld.h"

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
    //m_pTowerModel->Create_BoundingBox();
    m_pTowerModel->Set_RenderModeScreenNormalEnable(true);
    
    m_pLeftTrackModel = (CModel*)CSceneMgr::Instance()->AddCustomModel("left_track_model.mdl", IResource::E_THREAD_BACKGROUND);
    m_pLeftTrackModel->Set_Texture("model_02.pvr", 0, CTexture::E_WRAP_MODE_REPEAT);
    m_pLeftTrackModel->Set_Scale(vScale);
    m_pLeftTrackModel->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_ANIM_TEXCOORD_UNIT);
    m_pLeftTrackModel->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_PRE_NORMAL_DEPTH_UNIT);
    //m_pLeftTrackModel->Create_BoundingBox();
    m_pLeftTrackModel->Set_RenderModeScreenNormalEnable(true);
    
    m_pRightTrackModel = (CModel*)CSceneMgr::Instance()->AddCustomModel("right_track_model.mdl", IResource::E_THREAD_BACKGROUND);
    m_pRightTrackModel->Set_Texture("model_02.pvr", 0, CTexture::E_WRAP_MODE_REPEAT);
    m_pRightTrackModel->Set_Scale(vScale);
    m_pRightTrackModel->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_ANIM_TEXCOORD_UNIT);
    m_pRightTrackModel->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_PRE_NORMAL_DEPTH_UNIT);
    //m_pRightTrackModel->Create_BoundingBox();
    m_pRightTrackModel->Set_RenderModeScreenNormalEnable(true);
    
    m_pBodyModel = (CModel*)CSceneMgr::Instance()->AddCustomModel("base_model.mdl", IResource::E_THREAD_BACKGROUND);
    m_pBodyModel->Set_Texture("model_01.pvr", 0, CTexture::E_WRAP_MODE_REPEAT);
    m_pBodyModel->Set_Scale(vScale);
    m_pBodyModel->Set_Shader(CShader::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_UNIT);
    m_pBodyModel->Set_Shader(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP, IResource::E_SHADER_PRE_NORMAL_DEPTH_UNIT);
    //m_pBodyModel->Create_BoundingBox();
    m_pBodyModel->Set_RenderModeScreenNormalEnable(true);
    
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
        m_vMoveDirection = glm::normalize(m_vPosition - m_vTargetPoint);
    }
}

bool CCharacterControllerEnemy::_MoveForwardAI(void)
{
    glm::vec2 vPoint_01 = glm::vec2(m_vPosition.x, m_vPosition.z);
    glm::vec2 vPoint_02 = glm::vec2(m_vTargetPoint.x, m_vTargetPoint.z);
    glm::vec2 vPoint_03 = glm::mix(vPoint_01, vPoint_02, m_fMoveSpeed);
    glm::vec3 vPosition = glm::vec3(vPoint_03.x, 0.0f, vPoint_03.y);
    vPosition.y = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_HeightValue(vPoint_03.x, vPoint_03.y);
    Set_Position(vPosition);

    std::cout<<"[CCharacterControllerEnemy::_MoveForwardAI] Current Position : "<<m_vPosition.x<<","<<m_vPosition.z<<std::endl;
    std::cout<<"[CCharacterControllerEnemy::_MoveForwardAI] Target Position : "<<m_vTargetPoint.x<<","<<m_vTargetPoint.z<<std::endl;
    return true;
}

bool CCharacterControllerEnemy::_MoveBackwardAI(void)
{
    return true;
}

bool CCharacterControllerEnemy::_SteerLeftAI(void)
{
    return true;
}

bool CCharacterControllerEnemy::_SteerRightAI(void)
{
    return true;
}

void CCharacterControllerEnemy::Update(void)
{
    switch (m_eState)
    {
        case E_AI_STATE_NONE:
            std::cout<<"[CCharacterControllerEnemy::Update]"<<"state -> AI_STATE_NONE"<<std::endl;
            break;
        case E_AI_STATE_STAND:
        {
            
        }
            break;
        case E_AI_STATE_MOVE:
        {
            /*float fAngleToTarget =  glm::degrees(_GetRotationBetweenPoints(m_vTargetPoint, m_vPosition) - 1.57f);
            std::cout<<"[CCharacterControllerEnemy::Update] Angle :"<<fAngleToTarget - m_vRotation.y<<std::endl;
            if(fabs(fAngleToTarget - m_vRotation.y) > 45.0f)
            {
                SteerLeft();
            }
            else
            {
                if(fabs(fAngleToTarget - m_vRotation.y) > 5.0f)
                {
                    SteerLeft();
                }
                MoveForward();
            }
            
            if(glm::distance(m_vTargetPoint, m_vPosition) < 1.5f)
            {
                m_eState = E_AI_STATE_NONE;
            }
            
            m_vPosition.y = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_HeightValue(m_vPosition.x, m_vPosition.z);
            Set_Position(m_vPosition);
            */
            
            _MoveForwardAI();
            glm::vec2 vPoint_01 = glm::vec2(m_vPosition.x, m_vPosition.z);
            glm::vec2 vPoint_02 = glm::vec2(m_vTargetPoint.x, m_vTargetPoint.z);
            if(glm::distance(vPoint_01, vPoint_02) < 1.0f)
            {
                m_eState = E_AI_STATE_NONE;
            }
            
            glm::vec2 vRotationOnHeightMap = _Get_RotationOnHeightmap(m_vPosition);
            m_vRotation.x = -glm::degrees(vRotationOnHeightMap.x);
            m_vRotation.z =  glm::degrees(vRotationOnHeightMap.y);
            Set_Rotation(m_vRotation);
            
            float fTowerTargetAngle = _GetRotationBetweenPoints(m_vPosition, m_vTargetPoint);
            m_pTowerModel->Set_Rotation(glm::vec3(m_vRotation.x, glm::degrees(fTowerTargetAngle - 1.57f), m_vRotation.z));
            //std::cout<<"[CCharacterControllerEnemy::Update]"<<"state -> AI_STATE_MOVE"<<" To Point : "<<m_vTargetPoint.x<<" , "<<m_vTargetPoint.z<<std::endl;
            //std::cout<<"[CCharacterControllerEnemy::Update]"<<"state -> AI_STATE_MOVE"<<" From Point : "<<m_vPosition.x<<" , "<<m_vPosition.z<<std::endl;
        }
            break;
        default:
            break;
    }
}




