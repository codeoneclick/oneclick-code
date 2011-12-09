//
//  CGame.cpp
//  gEngine
//
//  Created by Snow Leopard User on 26/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CGame.h"
#include "CInput.h"
#include "CCamera.h"
#include "CResourceMgr.h"
#include "CParser_MD2.h"

CGame* CGame::m_game = NULL;

CGame::CGame()
{
    CCamera::Instance();
    CRenderMgr::Instance();
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

void CGame::Load()
{   
    
    m_pLevel = new CLevel();
    m_pLevel->Load("none");
}

void CGame::Update(CSceneMgr::E_RENDER_STATE _eState, float _fTime)
{
    m_pLevel->Update(_fTime);
    CCamera::Instance()->Update(_fTime);
    CResourceMgr::Instance()->Update();
    CSceneMgr::Instance()->Update(_eState,_fTime);
}

void CGame::Render(CSceneMgr::E_RENDER_STATE _eState)
{
    CRenderMgr::Instance()->Begin(_eState);
    CSceneMgr::Instance()->Render();
    CRenderMgr::Instance()->End(_eState);
}










