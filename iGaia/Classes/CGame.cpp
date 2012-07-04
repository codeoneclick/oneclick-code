//
//  CGame.cpp
//  iGaia
//
//  Created by Snow Leopard User on 26/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CGame.h"
#include "CInput.h"
#include "CResourceMgr.h"
#include "CGameSceneMgr.h"
#include "CGameInGameScene.h"

CGame* CGame::m_game = NULL;

CGame::CGame(void)
{

}

CGame::~CGame(void)
{
    
}

CGame* CGame::Instance(void)
{
    if(m_game == NULL)
    {
        m_game = new CGame();
    }
    return m_game;
}

void CGame::Load(void)
{
    CGameInGameScene* pScene = new CGameInGameScene();
    CGameSceneMgr::Instance()->Set_Scene(pScene);
    pScene->Load();
}

void CGame::Update(void)
{
    CGameSceneMgr::Instance()->Update();
    CResourceMgr::Instance()->Update();
    CSceneMgr::Instance()->Update();
}

void CGame::Render(void)
{
    CSceneMgr::Instance()->Render();
}










