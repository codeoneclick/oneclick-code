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
    m_pGameUnitMgr = NULL;
    m_bIsHeroUnderControl = true;
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
    m_pGameUnitMgr = new CGameUnitMgr();
    
    m_pLevel = new CLevel();
    m_pLevel->Load();
    
    m_pGameUnitMgr->Add_Unit(CGameUnitMgr::E_UNIT_TYPE_HERO);
    m_pHero = (CGameUnitHero*)m_pGameUnitMgr->Get_Unit(CGameUnitMgr::E_UNIT_TYPE_HERO);
    m_pHero->Get_Model()->Set_Position(glm::vec3(0.0f, 0.0f, 0.0f));
    
    m_pLight = CSceneMgr::Instance()->Get_Light(ILight::E_LIGHT_MODE_POINT, 0);
    m_pLight->Set_Position(glm::vec3(0.0f, 4.0f, 0.0f));
    m_pLight->Set_LightAt(glm::vec3(16.0f, 0.0f, 16.0f));
    static_cast<CLightPoint*>(m_pLight)->Set_Visible(true);
    
    m_pHero->Get_Model()->Set_Light(m_pLight);
    m_pLevel->Get_Model()->Set_Light(m_pLight);
    
    m_pCamera = CSceneMgr::Instance()->CreateFreeCamera(45.0f, 0.1f, 1024.0f);
    CSceneMgr::Instance()->Set_Camera(m_pCamera);
    m_pCamera->Set_DistanceToLookAt(8.0f);
    m_pCamera->Set_HeightFromLookAt(8.0f);
    glm::vec3 vCameraRotation = glm::vec3(0.0f, -MATH_PI / 4.0f, 0.0f);
    m_pCamera->Set_Rotation(vCameraRotation);
}

void CWorld::Update(void)
{
    m_pBuildingMgr->Update();
    m_pGameResourceMgr->Update();
    m_pGameUnitMgr->Update();
    
    m_pLevel->Update();
    
    static float fAngle = 0.0f; fAngle += 0.1f;
    m_pLight->Set_Rotation(glm::vec3(0.0f, fAngle, 0.0f));
    
    glm::vec3 vCameraPosition = m_pCamera->Get_Position();
    float fCameraHeight = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_HeightValueAtPoint(vCameraPosition.x, vCameraPosition.z);
    m_pCamera->Set_HeightFromLookAt(8.0f + fCameraHeight);
    
    //CVector3d vLightPosition = CVector3d(m_pHero->Get_Model()->Get_Position().x, 8.0f, m_pHero->Get_Model()->Get_Position().z);
    //m_pLight->Set_Position(vLightPosition);
}







