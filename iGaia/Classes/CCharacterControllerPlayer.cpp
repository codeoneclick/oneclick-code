//
//  CCharacterControllerPlayer.cpp
//  iGaia
//
//  Created by sergey.sergeev on 2/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CCharacterControllerPlayer.h"
#include "CGameSceneMgr.h"
#include "CSceneMgr.h"
#include "CTimer.h"

CCharacterControllerPlayer::CCharacterControllerPlayer(void)
{
    m_pBody = NULL;
    m_pTrack = NULL;
    m_pTower = NULL;
    
    m_fMaxMoveSpeed = 0.2f;
    m_fMoveAcceleration = 0.01f;
    
    m_fMoveSpeed = 0.0f;
    m_fLeftTrackMoveSpeed = 0.0f;
    m_fRightTrackMoveSpeed = 0.0f;
    m_fSteerSpeed = 2.0f;
    m_fTowerSteerSpeed = 4.0f;
    m_fTowerRotationY = 0.0f;
}

CCharacterControllerPlayer::~CCharacterControllerPlayer(void)
{
    CSceneMgr::Instance()->RemoveEventListener(m_pBody->Get_BasisNode(), CEventMgr::E_EVENT_TOUCH);
}

void CCharacterControllerPlayer::Load(void)
{
    ICharacterController::Load();
    
    m_pTrack = new CTankLightTrack();
    m_pTrack->Load();
    
    m_pTower = new CTankLightTower();
    m_pTower->Load();
    
    m_pBody = new CTankLightBody();
    m_pBody->Load();
    
    m_vMaxBound = m_pBody->Get_BodyMaxBound();
    m_vMinBound = m_pBody->Get_BodyMinBound();
    
    m_vTowerCenterBound = m_pTower->Get_TowerCenterBound();
    m_vRightTrackCenterBound = m_pTrack->Get_RightTrackTowerCenterBound();
    m_vLeftTrackCenterBound = m_pTrack->Get_LeftTrackTowerCenterBound();
    
    /*CSceneMgr::Instance()->AddEventListener(m_pBody->Get_BasisNode(), CEventMgr::E_EVENT_TOUCH);
    m_pBody->Get_BasisNode()->Add_DelegateOwner(this);
    CGameSceneMgr::Instance()->Get_Scene()->Get_Level()->Get_Landscape()->Add_DelegateOwner(this);*/
}

void CCharacterControllerPlayer::OnTouchEvent(ITouchDelegate* _pDelegateOwner)
{
    //CSceneMgr::Instance()->Get_CollisionMgr()->Get_Touch3DPoint();
}

void CCharacterControllerPlayer::Update(void)
{   
    m_fMoveSpeed = m_fMaxMoveSpeed;
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
            m_pBody->StartExhaust(false);
            break;
        case ICharacterController::E_CHARACTER_CONTROLLER_MOVE_STATE_FORWARD:
            
            MoveForward();
           
            m_pTrack->Move_LeftTrack(-fTrackTexCoordOffsetMoveFactor);
            m_pTrack->Move_RightTrack(-fTrackTexCoordOffsetMoveFactor);
            
            if(pCamera->Get_FovY() < k_CAMERA_FOV_Y_STATE_FORWARD)
            {
                pCamera->Set_FovY(pCamera->Get_FovY() + k_CAMERA_FOV_Y_DELTA_STATE_FORWARD);
            }
            m_pBody->StartExhaust(true);
            break;
        case ICharacterController::E_CHARACTER_CONTROLLER_MOVE_STATE_BACKWARD:
            
            MoveBackward();
            
            m_pTrack->Move_LeftTrack(fTrackTexCoordOffsetMoveFactor);
            m_pTrack->Move_RightTrack(fTrackTexCoordOffsetMoveFactor);
            
            if(pCamera->Get_FovY() > k_CAMERA_FOV_Y_STATE_BACKWARD)
            {
                pCamera->Set_FovY(pCamera->Get_FovY() - k_CAMERA_FOV_Y_DELTA_STATE_BACKWARD);
            }
            m_pBody->StartExhaust(true);
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
            m_pBody->StartExhaust(true);
            
            break;
        case ICharacterController::E_CHARACTER_CONTROLLER_STEER_STATE_RIGHT:
            
            SteerRight();
            
            m_pTrack->Move_LeftTrack(fTrackTexCoordOffsetMoveFactor);
            m_pTrack->Move_RightTrack(-fTrackTexCoordOffsetMoveFactor);
            m_pBody->StartExhaust(true);
            
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
    m_pTower->Update();
    m_pBody->Update();

    Set_Position(m_vPosition);
    _SmoothRotation();
    Set_Rotation(m_vRotation);
}










