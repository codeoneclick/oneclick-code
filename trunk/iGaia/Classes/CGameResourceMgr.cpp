//
//  CGameResourceMgr.cpp
//  iGaia
//
//  Created by sergey.sergeev on 2/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CGameResourceMgr.h"

CGameResourceMgr::CGameResourceMgr(void)
{
    m_lContainer[E_RESOURCE_TYPE_TREE] = new CResourceTree();
    ((CResourceTree*)m_lContainer[E_RESOURCE_TYPE_TREE])->Load();
    
    m_lContainer[E_RESOURCE_TYPE_ANIMAL] = new CResourceAnimal();
    ((CResourceAnimal*)m_lContainer[E_RESOURCE_TYPE_ANIMAL])->Load();
    
    m_lContainer[E_RESOURCE_TYPE_ORE] = new CResourceOre();
    ((CResourceOre*)m_lContainer[E_RESOURCE_TYPE_ORE])->Load();
    
    m_lContainer[E_RESOURCE_TYPE_WOOD] = new CResourceWood();
    
    m_lContainer[E_RESOURCE_TYPE_FOOD] = new CResourceFood();
    
    m_lContainer[E_RESOURCE_TYPE_LEATHER] = new CResourceLeather();
    
    m_lContainer[E_RESOURCE_TYPE_MANA] = new CResourceMana();
    
    m_lContainer[E_RESOURCE_TYPE_STEEL] = new CResourceSteel();
    
    m_lContainer[E_RESOURCE_TYPE_CLOTH] = new CResourceCloth();
}

CGameResourceMgr::~CGameResourceMgr(void)
{
    
}

int CGameResourceMgr::Get_ResourceCountByType(CGameResourceMgr::E_RESOURCE_TYPE _eType)
{
    IGameResource* pResource = (*m_lContainer.find(_eType)).second;
    return pResource->Get_Count();
}

void CGameResourceMgr::Set_ResourceCountByType(CGameResourceMgr::E_RESOURCE_TYPE _eType, int _iCount)
{
    IGameResource* pResource = (*m_lContainer.find(_eType)).second;
    return pResource->Set_Count(_iCount);
}

void CGameResourceMgr::Inc_ResourceCountByType(CGameResourceMgr::E_RESOURCE_TYPE _eType, int _iIncValue)
{
    IGameResource* pResource = (*m_lContainer.find(_eType)).second;
    int iTempCount = pResource->Get_Count();
    iTempCount += _iIncValue;
    pResource->Set_Count(iTempCount);
}

void CGameResourceMgr::Dec_ResourceCountByType(CGameResourceMgr::E_RESOURCE_TYPE _eType, int _iDecValue)
{
    IGameResource* pResource = (*m_lContainer.find(_eType)).second;
    int iTempCount = pResource->Get_Count();
    iTempCount -= _iDecValue;
    pResource->Set_Count(iTempCount);
}

void CGameResourceMgr::Update(void)
{
    std::map<E_RESOURCE_TYPE, IGameResource*>::iterator pBeginIterator = m_lContainer.begin();
    std::map<E_RESOURCE_TYPE, IGameResource*>::iterator pEndIterator = m_lContainer.end();
    
    while (pBeginIterator != pEndIterator)
    {
        (*pBeginIterator).second->Update();
        ++pBeginIterator;
    }
}






