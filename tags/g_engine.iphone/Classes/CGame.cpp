//
//  CGame.cpp
//  gEngine
//
//  Created by Snow Leopard User on 26/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CGame.h"
#include "CSceneEngine.h"
#include "CCamera.h"

CGame* CGame::m_game = NULL;

CGame::CGame()
{
    
}

CGame::~CGame()
{
    
}

CGame* CGame::Instance()
{
    if(m_game == NULL)
    {
        m_game = new CGame();
    }
    return m_game;
}

void CGame::Load(float _fWidth, float _fHeight)
{
    m_pRenderController = new CRenderEngine(_fWidth, _fHeight);
    CCamera::Instance()->Init(_fWidth, _fHeight);
    CResourceController::SResource resource;
    resource.s_sName = "node_01";
    resource.s_vSize = Vector2d(64.0f, 64.0f);
    resource.s_vColor = Vector4d(1.0f,0.0f,0.0f,1.0f);
    resource.s_tNode = CResourceController::SResource::SPRITE;
    resource.s_vPosition = Vector3d(0.0f,0.0f,0.0f);
    INode* node_01 = CSceneEngine::Instance()->AddNode(resource);
    
    resource.s_sName = "node_02";
    resource.s_vColor = Vector4d(0.0f,1.0f,0.0f,1.0f);
    resource.s_tNode = CResourceController::SResource::DSPRITE;
    INode* node_02 = CSceneEngine::Instance()->AddNode(resource);
    
    resource.s_sName = "node_03";
    resource.s_vColor = Vector4d(0.0f,0.0f,1.0f,1.0f);
    resource.s_tNode = CResourceController::SResource::DSPRITE;
    resource.s_vPosition = Vector3d(-32.0f,128.0f,0.0f);
    INode* node_03 = CSceneEngine::Instance()->AddNode(resource);
    
    //CSceneEngine::Instance()->RemoveNode(node_03);
}

void CGame::Update(float _fTime)
{
    m_pRenderController->Update(_fTime);
}

void CGame::Render()
{
    m_pRenderController->Render();
}

