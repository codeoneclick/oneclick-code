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
#include "CResourceMgr.h"
#include "CWorld.h"

CGame* CGame::m_game = NULL;

CGame::CGame()
{
    //CRenderMgr::Instance();
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
    CWorld::Instance()->Load();
}

void CGame::Update()
{
    CWorld::Instance()->Update();
    CResourceMgr::Instance()->Update();
    CSceneMgr::Instance()->Update();
}

void CGame::Render()
{
    CSceneMgr::Instance()->Render();
}










