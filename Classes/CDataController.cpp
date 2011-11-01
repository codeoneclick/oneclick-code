//
//  CDataController.cpp
//  gEngine
//
//  Created by sergey.sergeev on 10/28/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CDataController.h"

CDataController::CDataController()
{
    
}

CDataController::~CDataController()
{
    
}

CSequence* CDataController::Get_Sequence(std::string _sName)
{
    CSequence* pSequence = NULL;
    if( m_container.find(_sName) != m_container.end())
    {
        pSequence = m_container[_sName];
        pSequence->IncRefCount();
    }
    else
    {
        CFXMLLoader* pLoader = new CFXMLLoader();
        pSequence = pLoader->Load(_sName.c_str());
        m_container[_sName] = pSequence;
        pSequence->IncRefCount();
        pSequence->Set_Done(true);
        delete pLoader;
    }
    return pSequence;
}

void CDataController::Unload_Sequence(std::string _sName)
{
    CSequence* pSequence = NULL;
    if( m_container.find(_sName) != m_container.end())
    {
        pSequence = m_container[_sName];
        pSequence->DecRefCount();
        if(pSequence->Get_RefCount() == 0)
        {
            delete pSequence;
            std::map<std::string, CSequence*>::iterator pIterator = m_container.find(_sName);
            m_container.erase(pIterator);
        }
    }
}










