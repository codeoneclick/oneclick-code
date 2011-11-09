//
//  CMatch3.cpp
//  gEngine
//
//  Created by sergey.sergeev on 11/7/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CMatch3.h"
#include "CShape.h"
#include "CWindow.h"
#include "CMatch3LogicController.h"

CMatch3::CMatch3()
{
    
}

CMatch3::~CMatch3()
{
    
}

void CMatch3::Load()
{
    m_pGameContainer = new CShape();
    INode::SResourceParam param;
    param.m_vColor = Vector4d(1.0f, 1.0f, 1.0f, 1.0f);
    param.m_vSize.x = CWindow::Instance()->Get_Width(); 
    param.m_vSize.y = CWindow::Instance()->Get_Height();
    m_pGameContainer->Load(param);
    
    m_pLevel = new CMatch3Level();
    ((CMatch3Level*)m_pLevel)->Load(8,8);
    Vector3d vLevelPosition = Vector3d(-(7 * 26) / 2, -(7 * 26) / 2, 0.0f);
    m_pLevel->Set_Position(vLevelPosition);
    m_pGameContainer->AddChild(m_pLevel);
}

void CMatch3::Update(float _fTime)
{
    m_pGameContainer->Update(_fTime);
    CMatch3LogicController::Instnace()->Update(_fTime);
}

void CMatch3::Render()
{
    m_pGameContainer->Render();
}

