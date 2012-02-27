//
//  CLevel.cpp
//  gEngine
//
//  Created by sergey.sergeev on 2/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CLevel.h"
#include "CSceneMgr.h"
#include "CNavigationMeshWrapper.h"

CLevel::CLevel(void)
{
    m_pLandscape = NULL;
}

CLevel::~CLevel(void)
{
    
}

void CLevel::Load(void)
{
    m_pLandscape = (CLandscape*)CSceneMgr::Instance()->AddLandscapeModel("landscape.data");
    m_pLandscape->Set_Texture("TileSet.pvr");
    m_pLandscape->Set_Shader(IResource::E_SHADER_LAMBERT);
    CSceneMgr::Instance()->AddEventListener(m_pLandscape, CEventMgr::E_EVENT_TOUCH);
    m_pLandscape->Set_Position(CVector3d(0.0f, 0.0f, 0.0f));
    m_pLandscape->Set_SelfDelegate(this);
    m_pLandscape->Add_DelegateOwner(this);
    CNavigationMeshWrapper::Instance()->SetupNavigationMesh(m_pLandscape);
    CMesh* pMesh = CNavigationMeshWrapper::Instance()->CreateRenderNavMesh();
    m_pLandscape->Set_NavMesh(pMesh);
}

void CLevel::OnTouchEvent(IDelegate* _pDelegateOwner)
{
    std::cout<<"[CLevel::OnTouchEvent]";
}

void CLevel::Update(void)
{
    
}