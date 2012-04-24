//
//  CGameCharaterControllerMgr.cpp
//  iGaia
//
//  Created by sergey.sergeev on 2/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CGameCharaterControllerMgr.h"
#include "CCharacterControllerPlayer.h"
#include "CCharacterControllerEnemy.h"

CGameCharaterControllerMgr::CGameCharaterControllerMgr(void)
{
    m_pCharacterControllerPlayer = NULL;
}

CGameCharaterControllerMgr::~CGameCharaterControllerMgr(void)
{
    
}

ICharacterController* CGameCharaterControllerMgr::Add_MainCharacterController(void)
{
    m_pCharacterControllerPlayer = new CCharacterControllerPlayer();
    m_pCharacterControllerPlayer->Load();
    m_lContainer.push_back(m_pCharacterControllerPlayer);
    return m_pCharacterControllerPlayer;
}

ICharacterController* CGameCharaterControllerMgr::Add_EnemyCharacterController(void)
{
    CCharacterControllerEnemy* pCharacterController = new CCharacterControllerEnemy();
    pCharacterController->Load();
    m_lContainer.push_back(pCharacterController);
    return pCharacterController;
}

void CGameCharaterControllerMgr::Remove_MainCharacterController(void)
{
    
}

void CGameCharaterControllerMgr::Remove_EnemyCharacterController(ICharacterController* _pCharacterController)
{
    
}

void CGameCharaterControllerMgr::Reset_MainCharacterController(void)
{
    
}

void CGameCharaterControllerMgr::Update(void)
{
    std::vector<ICharacterController*>::iterator pBeginIterator = m_lContainer.begin();
    std::vector<ICharacterController*>::iterator pEndIterator = m_lContainer.end();
    
    while (pBeginIterator != pEndIterator)
    {
        (*pBeginIterator)->Update();
        ++pBeginIterator;
    }
}










