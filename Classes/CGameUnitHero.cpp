//
//  CGameUnitHero.cpp
//  gEngine
//
//  Created by sergey.sergeev on 2/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CGameUnitHero.h"
#include "CSceneMgr.h"

CGameUnitHero::CGameUnitHero(void)
{
    
}

CGameUnitHero::~CGameUnitHero(void)
{
    
}

void CGameUnitHero::Load(void)
{
    m_pModel = (CModel*)CSceneMgr::Instance()->AddCustomModel("footman.gmesh", false, IResource::E_THREAD_BACKGROUND);
    m_pModel->Set_Texture("footman.pvr");
    m_pModel->Set_Scale(CVector3d(0.01f, 0.01f, 0.01f));
    m_pModel->Set_Shader(IResource::E_SHADER_PHONG);
    m_pModel->Create_BoundingBox();
    m_pModel->Create_ColliderBox();
}

void CGameUnitHero::Update(void)
{
    
}