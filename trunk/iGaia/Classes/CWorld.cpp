//
//  CWorld.cpp
//  iGaia
//
//  Created by sergey.sergeev on 2/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CWorld.h"
#include "CLightPoint.h"

#define MATH_PI 3.14f

CWorld* CWorld::m_pInstance = NULL;

CWorld::CWorld(void)
{
    m_pBuildingMgr = NULL;
    m_pGameResourceMgr = NULL;
    m_pCharaterControllerMgr = NULL;
    m_pGameAIMgr = NULL;
    m_bIsHeroUnderControl = true;
    m_eCameraMode = E_CAMERA_MODE_1;
    m_pGameShooterMgr = NULL;
}

CWorld::~CWorld(void)
{
    
}

CWorld* CWorld::Instance(void)
{
    if(m_pInstance == NULL)
    {
        m_pInstance = new CWorld();
    }
    return m_pInstance;
}

void CWorld::Load(void)
{
    m_pBuildingMgr = new CBuildingMgr();
    m_pGameResourceMgr = new CGameResourceMgr();
    m_pCharaterControllerMgr = new CGameCharaterControllerMgr();
    m_pGameAIMgr = new CGameAIMgr();
    m_pGameShooterMgr = new CGameShooterMgr();
    
    m_pLevel = new CLevel();
    m_pLevel->Load();
    
    m_pCharaterControllerMgr->Add_MainCharacterController();
    m_pCharacterControllerPlayer = static_cast<CCharacterControllerPlayer*>(m_pCharaterControllerMgr->Get_MainCharacterController());
    m_pCharacterControllerPlayer->Set_Position(glm::vec3(2.0f, 0.0f, 2.0f));
    
    CCharacterControllerEnemy* pCharacterControllerEnemy = static_cast<CCharacterControllerEnemy*>(m_pCharaterControllerMgr->Add_EnemyCharacterController());
    m_pGameAIMgr->Add_AICharacterController(pCharacterControllerEnemy);
    pCharacterControllerEnemy->Set_Position(glm::vec3(3.0f, 0.0f, 3.0f));
    
    m_pLight = CSceneMgr::Instance()->Get_Light(ILight::E_LIGHT_MODE_POINT, 0);
    m_pLight->Set_Position(glm::vec3(0.0f, 4.0f, 0.0f));
    m_pLight->Set_LightAt(glm::vec3(16.0f, 0.0f, 16.0f));
    static_cast<CLightPoint*>(m_pLight)->Set_Visible(true);
    CSceneMgr::Instance()->Set_GlobalLight(m_pLight);
    
    m_pCamera = CSceneMgr::Instance()->CreateTargetCamera(45.0f, 0.1f, 1024.0f, m_pCharacterControllerPlayer->Get_TargetForCamera());
    CSceneMgr::Instance()->Set_Camera(m_pCamera);
    m_pCamera->Set_DistanceToLookAt(k_CAMERA_DISTANCE_MODE_1);
    m_pCamera->Set_HeightFromLookAt(k_CAMERA_HEIGHT_MODE_1);
    m_iCurrentCameraHeight = k_CAMERA_HEIGHT_MODE_1;
}

void CWorld::SwitchCameraMode(CWorld::E_CAMERA_MODE _eCameraMode)
{
    m_eCameraMode = _eCameraMode;
}

void CWorld::SwitchCameraModeToNext(void)
{
    if(m_eCameraMode == E_CAMERA_MODE_1)
    {
        m_eCameraMode = E_CAMERA_MODE_2;
    }
    else
    {
        m_eCameraMode = E_CAMERA_MODE_1;
    }
}

void CWorld::Update(void)
{
    m_pBuildingMgr->Update();
    m_pGameResourceMgr->Update();
    m_pCharaterControllerMgr->Update();
    m_pGameShooterMgr->Update();
    m_pGameAIMgr->Update();
    
    m_pLevel->Update();
    
    static float fAngle = 0.0f; fAngle += 0.1f;
    m_pLight->Set_Rotation(glm::vec3(0.0f, fAngle, 0.0f));
    
    glm::vec3 vCameraPosition = m_pCamera->Get_Position();
    float fCameraHeight = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_HeightValue(vCameraPosition.x, vCameraPosition.z);
    
    if(m_eCameraMode == E_CAMERA_MODE_1 && m_iCurrentCameraHeight > k_CAMERA_HEIGHT_MODE_1)
    {
        m_iCurrentCameraHeight -= k_CAMERA_DISPLACE_INC;
    }
    else if(m_eCameraMode == E_CAMERA_MODE_2 && m_iCurrentCameraHeight < k_CAMERA_HEIGHT_MODE_2)
    {
        m_iCurrentCameraHeight += k_CAMERA_DISPLACE_INC;
    }
    m_pCamera->Set_HeightFromLookAt(m_iCurrentCameraHeight + fCameraHeight);
    
    glm::vec3 vCurrentCameraRotation = m_pCamera->Get_Rotation();
    vCurrentCameraRotation.y = glm::radians(m_pCharacterControllerPlayer->Get_Rotation().y) - 1.57f;
    glm::vec3 vOldCameraRotation = m_pCamera->Get_Rotation();
    glm::vec3 vCameraRotation = glm::mix(vOldCameraRotation, vCurrentCameraRotation, 0.25f);
    m_pCamera->Set_Rotation(vCameraRotation);
    
       
    //CVector3d vLightPosition = CVector3d(m_pHero->Get_Model()->Get_Position().x, 8.0f, m_pHero->Get_Model()->Get_Position().z);
    //m_pLight->Set_Position(vLightPosition);
}







