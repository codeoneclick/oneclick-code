//
//  CWorld.cpp
//  gEngine
//
//  Created by sergey.sergeev on 2/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CWorld.h"
#include "CLightPoint.h"

CWorld* CWorld::m_pInstance = NULL;

CWorld::CWorld(void)
{
    m_pBuildingMgr = NULL;
    m_pGameResourceMgr = NULL;
    m_pGameUnitMgr = NULL;

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
    
    m_pGameUnitMgr->Add_Unit(CGameUnitMgr::E_UNIT_TYPE_HERO);
    m_pHero = (CGameUnitHero*)m_pGameUnitMgr->Get_Unit(CGameUnitMgr::E_UNIT_TYPE_HERO);
    
    m_pLight = CSceneMgr::Instance()->Get_Light(ILight::E_LIGHT_MODE_POINT, 0);
    m_pLight->Set_Position(CVector3d(0.0f, 2.0f, 0.0f));
    m_pLight->Set_LightAt(CVector3d(4.0f, 0.0f, 4.0f));
    static_cast<CLightPoint*>(m_pLight)->Set_Visible(true);
    m_pHero->Get_Model()->Set_Light(m_pLight);
    
    m_pCamera = CSceneMgr::Instance()->CreateTargetCamera(45.0f, 0.1f, 1024.0f, m_pHero->Get_Model());
    CSceneMgr::Instance()->Set_Camera(m_pCamera);
    m_pCamera->Set_DistanceToLookAt(4.0f);
    m_pCamera->Set_HeightFromLookAt(4.0f);
    
    m_pLandscape = (CLandscape*)CSceneMgr::Instance()->AddLandscapeModel("landscape.data");
    m_pLandscape->Set_Texture("TileSet.pvr");
    m_pLandscape->Set_Shader(IResource::E_SHADER_PHONG);
    CSceneMgr::Instance()->AddEventListener(m_pLandscape, CEventMgr::E_EVENT_TOUCH);
    m_pLandscape->Set_Position(CVector3d(0.0f, 0.0f, 0.0f));
}

void CWorld::Update(void)
{
    m_pBuildingMgr->Update();
    m_pGameResourceMgr->Update();
    m_pGameUnitMgr->Update();
    
    static float fAngle = 0.0f; fAngle += 0.1f;
    m_pLight->Set_Rotation(CVector3d(0.0f, fAngle, 0.0f));
}
