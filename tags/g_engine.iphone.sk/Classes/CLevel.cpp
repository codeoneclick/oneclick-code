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

CLevel::CLevel(void)
{
    m_pLandscape = NULL;
}

CLevel::~CLevel(void)
{
    
}

void CLevel::Load(void)
{
    m_pLandscape = (CLandscape*)CSceneMgr::Instance()->AddLandscapeModel("landscape.mdl");
    m_pLandscape->Set_Texture("layer_01_diffuse.pvr", 0);
    m_pLandscape->Set_Texture("layer_01_normal.pvr", 1);
    m_pLandscape->Set_Texture("layer_01_bump.pvr", 2);
    m_pLandscape->Set_Shader(IResource::E_SHADER_PARALLAX);
    CSceneMgr::Instance()->AddEventListener(m_pLandscape, CEventMgr::E_EVENT_TOUCH);
    m_pLandscape->Set_Position(CVector3d(0.0f, 0.0f, 0.0f));
    m_pLandscape->Set_DelegateTarget(this);
    m_pLandscape->Add_Delegate(this);
}

void CLevel::OnTouchEvent(IDelegate* _pDelegateOwner)
{
    std::cout<<"[CLevel::OnTouchEvent]";
}

void CLevel::Update(void)
{
    
}