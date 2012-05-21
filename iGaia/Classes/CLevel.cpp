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
    m_pLandscape->Set_Texture("layer_01_diffuse.pvr", 0, CTexture::E_WRAP_MODE_REPEAT, IResource::E_THREAD_BACKGROUND);
    m_pLandscape->Set_Texture("layer_01_normal.pvr",  1, CTexture::E_WRAP_MODE_REPEAT, IResource::E_THREAD_BACKGROUND);
    m_pLandscape->Set_Texture("layer_02_diffuse.pvr", 2, CTexture::E_WRAP_MODE_REPEAT, IResource::E_THREAD_BACKGROUND);
    m_pLandscape->Set_Texture("layer_02_bump.pvr",    3, CTexture::E_WRAP_MODE_REPEAT, IResource::E_THREAD_BACKGROUND);
    m_pLandscape->Set_Texture("layer_03_diffuse.pvr", 4, CTexture::E_WRAP_MODE_REPEAT, IResource::E_THREAD_BACKGROUND);
    m_pLandscape->Set_Texture("layer_01_normal.pvr",  5, CTexture::E_WRAP_MODE_REPEAT, IResource::E_THREAD_BACKGROUND);
    m_pLandscape->Set_Shader(INode::E_RENDER_MODE_SIMPLE,IResource::E_SHADER_LANDSCAPE);
    m_pLandscape->Set_Shader(INode::E_RENDER_MODE_REFLECTION,IResource::E_SHADER_LANDSCAPE);
    m_pLandscape->Set_Shader(INode::E_RENDER_MODE_REFRACTION,IResource::E_SHADER_LANDSCAPE);
    m_pLandscape->Set_Shader(INode::E_RENDER_MODE_SCREEN_NORMAL_MAP,IResource::E_SHADER_NORMAL_DEPTH);
    CSceneMgr::Instance()->AddEventListener(m_pLandscape, CEventMgr::E_EVENT_TOUCH);
    CSceneMgr::Instance()->Get_PhysicMgr()->Add_CollisionLandscape(m_pLandscape);
    m_pLandscape->Set_Position(glm::vec3(0.0f, 0.0f, 0.0f));
    m_pLandscape->Add_DelegateOwner(this);
    m_pLandscape->Set_RenderModeReflectionEnable(true);
    m_pLandscape->Set_RenderModeRefractionEnable(true);
    m_pLandscape->Set_RenderModeScreenNormalEnable(true);
    
    m_pWater = (CWater*)CSceneMgr::Instance()->AddWaterModel("water");
    m_pWater->Set_Shader(INode::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_WATER);
    m_pWater->Set_Texture("layer_02_bump.pvr", 2, CTexture::E_WRAP_MODE_REPEAT, IResource::E_THREAD_BACKGROUND);
    
    m_pGrass = (CGrass*)CSceneMgr::Instance()->AddLandscapeGrassModel("grass");
    m_pGrass->Set_Shader(INode::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_UNIT);
    m_pGrass->Set_Texture("mod_03.pvr", 0, CTexture::E_WRAP_MODE_REPEAT, IResource::E_THREAD_BACKGROUND);
    
    m_pSkyBox = (CSkyBox*)CSceneMgr::Instance()->AddSkyBoxModel("skybox");
    m_pSkyBox->Set_Shader(INode::E_RENDER_MODE_SIMPLE, IResource::E_SHADER_LAMBERT);
    m_pSkyBox->Set_Texture("clouds.pvr", 0, CTexture::E_WRAP_MODE_REPEAT);
}

void CLevel::OnTouchEvent(ITouchDelegate* _pDelegateOwner)
{
    std::cout<<"[CLevel::OnTouchEvent]";
}

void CLevel::Update(void)
{
    //static float fValue = 0.0f;
    //fValue += 0.1f;
    //m_pLandscape->Get_Shader()->SetFloat(fValue, CShader::k_TIMER);
}



