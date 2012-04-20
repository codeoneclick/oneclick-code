//
//  CLevel.cpp
//  iGaia
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
    m_pGrass = NULL;
}

CLevel::~CLevel(void)
{
    
}

void CLevel::Load(void)
{
    m_pLandscape = (CLandscape*)CSceneMgr::Instance()->AddLandscapeModel("landscape.mdl");
    m_pLandscape->Set_Texture("layer_01_diffuse.pvr", 0, IResource::E_THREAD_BACKGROUND);
    m_pLandscape->Set_Texture("layer_01_normal.pvr",  1, IResource::E_THREAD_BACKGROUND);
    m_pLandscape->Set_Texture("layer_02_diffuse.pvr", 2, IResource::E_THREAD_BACKGROUND);
    m_pLandscape->Set_Texture("layer_02_bump.pvr",    3, IResource::E_THREAD_BACKGROUND);
    m_pLandscape->Set_Texture("layer_01_diffuse.pvr", 4, IResource::E_THREAD_BACKGROUND);
    m_pLandscape->Set_Texture("layer_01_normal.pvr",  5, IResource::E_THREAD_BACKGROUND);
    m_pLandscape->Set_Shader(IResource::E_SHADER_LANDSCAPE);
    CSceneMgr::Instance()->AddEventListener(m_pLandscape, CEventMgr::E_EVENT_TOUCH);
    CSceneMgr::Instance()->Get_PhysicMgr()->Add_CollisionLandscape(m_pLandscape);
    m_pLandscape->Set_Position(glm::vec3(0.0f, 0.0f, 0.0f));
    m_pLandscape->Set_DelegateTarget(this);
    m_pLandscape->Add_Delegate(this);
    m_pLandscape->Set_ForReflection(true);
    m_pLandscape->Set_ForRefraction(true);
    m_pLandscape->Set_EdgeDetect(true);
    m_pLandscape->Set_NormalDepth(true);
    
    m_pWater = (CWater*)CSceneMgr::Instance()->AddWaterModel("water");
    m_pWater->Set_Shader(IResource::E_SHADER_WATER);
    m_pWater->Set_Texture("layer_02_bump.pvr", 0, IResource::E_THREAD_BACKGROUND);
    
    //m_pGrass = (CGrass*)CSceneMgr::Instance()->AddLandscapeGrassModel("grass");
    //m_pGrass->Set_Shader(IResource::E_SHADER_LAMBERT);
    //m_pGrass->Set_Texture("mod_03.pvr", 0, IResource::E_THREAD_BACKGROUND);
}

void CLevel::OnTouchEvent(IDelegate* _pDelegateOwner)
{
    std::cout<<"[CLevel::OnTouchEvent]";
}

void CLevel::OnPhysicEvent(INode* _pNode, glm::vec3 _vPosition, glm::vec3 _vRotation, glm::vec3 _vScale)
{
    
}

void CLevel::Update(void)
{
    static float fValue = 0.0f;
    fValue += 0.1f;
    m_pLandscape->Get_Shader()->SetFloat(fValue, CShader::k_TIMER);
}