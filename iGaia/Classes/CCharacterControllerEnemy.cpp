//
//  CCharacterControllerEnemy.cpp
//  iGaia
//
//  Created by code_oneclick on 4/20/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "CCharacterControllerEnemy.h"
#include "CGameSceneMgr.h"
#include "CTimer.h"
#include "CTankLightTrack.h"
#include "CTankLightTower.h"
#include "CTankLightBody.h"

CCharacterControllerEnemy::CCharacterControllerEnemy(void)
{
    m_pTrack = NULL;
    m_pTower = NULL;
    m_pBody  = NULL;
    
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
    CSceneMgr::Instance()->RemoveEventListener(m_pBody->Get_BasisNode(), CEventMgr::E_EVENT_TOUCH);
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
    ICharacterController::Load();
    
    m_pTrack = new CTankLightTrack();
    m_pTrack->Load();
    
    m_pTower = new CTankLightTower();
    m_pTower->Load();
    
    m_pBody = new CTankLightBody();
    m_pBody->Load();
    
    /*CSceneMgr::Instance()->AddEventListener(m_pBody->Get_BasisNode(), CEventMgr::E_EVENT_TOUCH);
    m_pBody->Get_BasisNode()->Add_DelegateOwner(this);
    CGameSceneMgr::Instance()->Get_Scene()->Get_Level()->Get_Landscape()->Add_DelegateOwner(this);*/
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
    
    if((iAICurrentShootTimeStamp - m_iAIShootTimeStamp > k_AI_SHOOT_INTERVAL) && fDistanceToTargetPoint < k_AI_SHOOT_DISTANCE && m_pTower != NULL)
    {
        glm::vec3 vTowerGunOffset = m_pTower->Get_TowerGunOffset();
        CGameSceneMgr::Instance()->Get_Scene()->Get_GameShooterMgr()->CreateBullet(glm::vec3(m_vPosition.x + sinf(glm::radians(m_fTowerRotationY)) * vTowerGunOffset.x, m_vPosition.y + vTowerGunOffset.y, m_vPosition.z + cosf(glm::radians(m_fTowerRotationY)) * vTowerGunOffset.z), glm::vec3(m_vRotation.x, m_fTowerRotationY, m_vRotation.z));
        m_iAIShootTimeStamp = iAICurrentShootTimeStamp;
    }
}

void CCharacterControllerEnemy::Update(void)
{
    float fTrackTexCoordOffsetMoveFactor  = 0.2f;
    float fTrackTexCoordOffsetSteerFactor = 0.1f;
    switch (m_eState)
    {
        case E_AI_STATE_NONE:
            std::cout<<"[CCharacterControllerEnemy::Update]"<<"state -> AI_STATE_NONE"<<std::endl;
            m_pBody->StartExhaust(false);
            break;
        case E_AI_STATE_STAND:
        {
            m_pBody->StartExhaust(false);
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
            
            float fAngleToMovePoint =  glm::degrees(CMathHelper::Instance()->Get_RotationBetweenPointsDot(vPoint_01, vPoint_02));
            if(fabs(fAngleToMovePoint - m_vRotation.y) > 45.0f)
            {
                SteerLeft();
                m_pTrack->Move_LeftTrack(-fTrackTexCoordOffsetMoveFactor);
                m_pTrack->Move_RightTrack(fTrackTexCoordOffsetMoveFactor);
            }
            else
            {
                if(fabs(fAngleToMovePoint - m_vRotation.y) > 5.0f)
                {
                    SteerLeft();
                }
                MoveForward();
                m_pTrack->Move_LeftTrack(-fTrackTexCoordOffsetMoveFactor);
                m_pTrack->Move_RightTrack(-fTrackTexCoordOffsetMoveFactor);
            }
             
            m_vRotation.y =  glm::degrees(CMathHelper::Instance()->Get_RotationBetweenPoints(m_vMovePoint, m_vPosition) - CMathHelper::k_HALF_PI);
            m_pBody->StartExhaust(true);
        }
            break;
        default:
            break;
    }
    
    m_pTrack->Update();
    m_pTower->Update();
    m_pBody->Update();
    
    Shoot();
    
    glm::vec3 vTargetPoint;
    if(m_pTarget != NULL)
    {
        vTargetPoint = m_pTarget->Get_Position();
    }
    else
    {
        vTargetPoint = m_vMovePoint;
    }
    
    m_fTowerRotationY = glm::degrees(CMathHelper::Instance()->Get_RotationBetweenPoints(m_vPosition, vTargetPoint) + CMathHelper::k_HALF_PI);
    
    Set_Position(m_vPosition);
    _SmoothRotation();
    Set_Rotation(m_vRotation);
}




