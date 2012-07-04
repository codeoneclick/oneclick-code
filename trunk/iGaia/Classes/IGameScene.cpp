//
//  IGameScene.cpp
//  iGaia
//
//  Created by sergey sergeev on 7/4/12.
//
//

#include "IGameScene.h"
#include "CMathHelper.h"


IGameScene::IGameScene(void)
{
    m_pCharaterControllerMgr = NULL;
    m_pGameAIMgr = NULL;
    m_pGameShooterMgr = NULL;
}

IGameScene::~IGameScene(void)
{
    
}

void IGameScene::Load(void)
{
    m_pCharaterControllerMgr = new CGameCharaterControllerMgr();
    m_pGameAIMgr = new CGameAIMgr();
    m_pGameShooterMgr = new CGameShooterMgr();
}

void IGameScene::Unload(void)
{
    
}

void IGameScene::Update(void)
{
    m_pCharaterControllerMgr->Update();
    m_pGameShooterMgr->Update();
    m_pGameAIMgr->Update();
    m_pLevel->Update();
}
