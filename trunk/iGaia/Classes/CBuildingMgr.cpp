//
//  CBuildingMgr.cpp
//  iGaia
//
//  Created by sergey.sergeev on 2/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CBuildingMgr.h"

CBuildingMgr::CBuildingMgr(void)
{
    
}

CBuildingMgr::~CBuildingMgr(void)
{
    
}

void CBuildingMgr::Add_Building(CBuildingMgr::E_BUILDING_TYPE _eType)
{
    std::map<E_BUILDING_TYPE, IBuilding*>::iterator pFindIterator = m_lContainer.find(_eType);
    if(pFindIterator != m_lContainer.end())
    {
        // TODO: WARNING
    }
    else
    {
        IBuilding* pBuilding = NULL;
        switch (_eType)
        {
            case E_BUILDING_TYPE_TEMPLE:
                pBuilding = new CBuildingTample();
                pBuilding->Load();
                m_lContainer[_eType] = pBuilding;
                break;
            case E_BUILDING_TYPE_WOODCUTTER:
                pBuilding = new CBuildingWoodCutter();
                pBuilding->Load();
                m_lContainer[_eType] = pBuilding;
                break;
            case E_BUILDING_TYPE_MINER:
                pBuilding = new CBuildingMiner();
                pBuilding->Load();
                m_lContainer[_eType] = pBuilding;
                break;
            case E_BUILDING_TYPE_HUNTER:
                pBuilding = new CBuildingHunter();
                pBuilding->Load();
                m_lContainer[_eType] = pBuilding;
                break;
            case E_BUILDING_TYPE_LETHERWORKER:
                pBuilding = new CBuildingLeatherworker();
                pBuilding->Load();
                m_lContainer[_eType] = pBuilding;
                break;
            case E_BUILDING_TYPE_FARMER:
                pBuilding = new CBuildingFarmer();
                pBuilding->Load();
                m_lContainer[_eType] = pBuilding;
                break;
            case E_BUILDING_TYPE_TAILOR:
                pBuilding = new CBuildingTailor();
                pBuilding->Load();
                m_lContainer[_eType] = pBuilding;
                break;
            case E_BUILDING_TYPE_BLACKSMITH:
                pBuilding = new CBuildingBlacksmith();
                pBuilding->Load();
                m_lContainer[_eType] = pBuilding;
                break;
            default:
                break;
        }
    }
}

void CBuildingMgr::Remove_Building(CBuildingMgr::E_BUILDING_TYPE _eType)
{
    std::map<E_BUILDING_TYPE, IBuilding*>::iterator pFindIterator = m_lContainer.find(_eType);
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

IBuilding* CBuildingMgr::Get_Building(CBuildingMgr::E_BUILDING_TYPE _eType)
{
    std::map<E_BUILDING_TYPE, IBuilding*>::iterator pFindIterator = m_lContainer.find(_eType);
    if(pFindIterator != m_lContainer.end())
    {
        return (*pFindIterator).second;
    }
    else
    {
        return NULL;
    }
}

void CBuildingMgr::Update(void)
{
    std::map<E_BUILDING_TYPE, IBuilding*>::iterator pBeginIterator = m_lContainer.begin();
    std::map<E_BUILDING_TYPE, IBuilding*>::iterator pEndIterator = m_lContainer.end();
    
    while (pBeginIterator != pEndIterator)
    {
        (*pBeginIterator).second->Update();
        ++pBeginIterator;
    }
}






