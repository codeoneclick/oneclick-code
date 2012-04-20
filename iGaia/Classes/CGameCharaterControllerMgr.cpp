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

CGameCharaterControllerMgr::CGameCharaterControllerMgr(void)
{
    m_pCharacterControllerPlayer = NULL;
}

CGameCharaterControllerMgr::~CGameCharaterControllerMgr(void)
{
    
}

void CGameCharaterControllerMgr::Add_MainCharacterController(void)
{
    m_pCharacterControllerPlayer = new CCharacterControllerPlayer();
    m_pCharacterControllerPlayer->Load();
    m_lContainer.push_back(m_pCharacterControllerPlayer);
}

void CGameCharaterControllerMgr::Add_EnemyCharacterController(void)
{
    
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










