//
//  CGameUnitMgr.cpp
//  iGaia
//
//  Created by sergey.sergeev on 2/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CGameUnitMgr.h"

CGameUnitMgr::CGameUnitMgr(void)
{
    
}

CGameUnitMgr::~CGameUnitMgr(void)
{
    
}

void CGameUnitMgr::Add_Unit(CGameUnitMgr::E_UNIT_TYPE _eType)
{
    std::map<E_UNIT_TYPE, IGameUnit*>::iterator pFindIterator = m_lContainer.find(_eType);
    if(pFindIterator != m_lContainer.end())
    {
        // TODO: WARNING
    }
    else
    {
        IGameUnit* pGameUnit = NULL;
        switch (_eType) 
        {
            case E_UNIT_TYPE_HERO:
                pGameUnit = new CGameUnitHero();
                pGameUnit->Load();
                m_lContainer[_eType] = pGameUnit;
                break;
            case E_UNIT_TYPE_WORKER:
                
                break;
            default:
                break;
        }         
    }
}
void CGameUnitMgr::Remove_Unit(CGameUnitMgr::E_UNIT_TYPE _eType)
{
    std::map<E_UNIT_TYPE, IGameUnit*>::iterator pFindIterator = m_lContainer.find(_eType);
    if(pFindIterator != m_lContainer.end())
    {
        m_lContainer.erase(pFindIterator);
        delete (*pFindIterator).second;
    }
    else
    {
        // TODO: WARNING
    }
}

IGameUnit* CGameUnitMgr::Get_Unit(CGameUnitMgr::E_UNIT_TYPE _eType)
{
    std::map<E_UNIT_TYPE, IGameUnit*>::iterator pFindIterator = m_lContainer.find(_eType);
    if(pFindIterator != m_lContainer.end())
    {
        return (*pFindIterator).second;
    }
    else
    {
        return NULL;
    }
}

void CGameUnitMgr::Update(void)
{
    std::map<E_UNIT_TYPE, IGameUnit*>::iterator pBeginIterator = m_lContainer.begin();
    std::map<E_UNIT_TYPE, IGameUnit*>::iterator pEndIterator = m_lContainer.end();
    
    while (pBeginIterator != pEndIterator)
    {
        (*pBeginIterator).second->Update();
        ++pBeginIterator;
    }
}









