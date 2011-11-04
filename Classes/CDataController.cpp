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
    CFXMLLoader* pLoader = new CFXMLLoader();
    pLoader->Load("Untitled_default.xml");
    m_pStub = static_cast<CSequence::SSource*>(pLoader->Get_Source());
}

CDataController::~CDataController()
{
    
}

IResource* CDataController::Load(std::string _sName, IResource::E_LOAD_THREAD _eThread)
{
    CSequence* pSequence = NULL;
    
    if(_eThread == IResource::E_THREAD_MAIN)
    {
        if( m_lContainer.find(_sName) != m_lContainer.end())
        {
            pSequence = static_cast<CSequence*>(m_lContainer[_sName]);
            pSequence->IncRefCount();
        }
        else
        {
            pSequence = new CSequence();
            pSequence->Set_Source(m_pStub);
            CFXMLLoader* pLoader = new CFXMLLoader(); 
            pLoader->Load(_sName.c_str());
            if(pLoader->Get_Status() != ILoader::E_STATUS_ERROR)
            {
                pSequence->Set_Source(pLoader->Get_Source());
            }
            delete pLoader;
        }
    }
    else if(_eThread == IResource::E_THREAD_BACKGROUND)
    {
        if( m_lContainer.find(_sName) != m_lContainer.end())
        {
            pSequence = static_cast<CSequence*>(m_lContainer[_sName]);
            pSequence->IncRefCount();
        }
        else
        {
            if(m_lTaskPool.find(_sName) == m_lTaskPool.end())
            {
                m_lTaskPool[_sName] = new CFXMLLoader();
            }
            pSequence = new CSequence();
            pSequence->Set_Source(m_pStub);
            m_lContainer[_sName] = pSequence;
        }
    }
    
    return pSequence;
}

void CDataController::Unload(std::string _sName)
{
    CSequence* pSequence = NULL;
    if( m_lContainer.find(_sName) != m_lContainer.end())
    {
        pSequence = static_cast<CSequence*>(m_lContainer[_sName]);
        pSequence->DecRefCount();
        if(pSequence->Get_RefCount() == 0)
        {
            delete pSequence;
            std::map<std::string, IResource*>::iterator pIterator = m_lContainer.find(_sName);
            m_lContainer.erase(pIterator);
        }
    }
}












