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
    m_pStub = pLoader->Get_Frames();
    pthread_mutex_init(&m_mutex, NULL);
}

CDataController::~CDataController()
{
    
}

CSequence* CDataController::Get_Sequence(std::string _sName, E_LOAD_THREAD _eThread)
{
    CSequence* pSequence = NULL;
    
    if(_eThread == E_THREAD_MAIN)
    {
        if( m_lContainer.find(_sName) != m_lContainer.end())
        {
            pSequence = m_lContainer[_sName];
            pSequence->IncRefCount();
        }
        else
        {
            pSequence = new CSequence();
            pSequence->Set_Frames(m_pStub);
            CFXMLLoader* pLoader = new CFXMLLoader();
            pLoader->Load(_sName.c_str());
            if(pLoader->Get_Status() != CFXMLLoader::E_STATUS_ERROR)
            {
                pSequence->Set_Frames(pLoader->Get_Frames());
            }
            delete pLoader;
        }
    }
    else if(_eThread == E_THREAD_BACKGROUND)
    {
        if( m_lContainer.find(_sName) != m_lContainer.end())
        {
            pSequence = m_lContainer[_sName];
            pSequence->IncRefCount();
        }
        else
        {
            if(m_lTaskPool.find(_sName) == m_lTaskPool.end())
            {
                m_lTaskPool[_sName] = new CFXMLLoader();
            }
            pSequence = new CSequence();
            pSequence->Set_Frames(m_pStub);
            m_lContainer[_sName] = pSequence;
        }
    }
    
    return pSequence;
    
    
    
    /*CSequence* pSequence = NULL;
    if( m_lContainer.find(_sName) != m_lContainer.end())
    {
        pSequence = m_lContainer[_sName];
        pSequence->IncRefCount();
    }
    else
    {
        CFXMLLoader* pLoader = new CFXMLLoader();
        pSequence = pLoader->Load(_sName.c_str());
        m_lContainer[_sName] = pSequence;
        pSequence->IncRefCount();
        pSequence->Set_Done(true);
        delete pLoader;
    }
    return pSequence;*/
}

void CDataController::Unload_Sequence(std::string _sName)
{
    CSequence* pSequence = NULL;
    if( m_lContainer.find(_sName) != m_lContainer.end())
    {
        pSequence = m_lContainer[_sName];
        pSequence->DecRefCount();
        if(pSequence->Get_RefCount() == 0)
        {
            delete pSequence;
            std::map<std::string, CSequence*>::iterator pIterator = m_lContainer.find(_sName);
            m_lContainer.erase(pIterator);
        }
    }
}

void CDataController::Update()
{
    std::map<std::string, CFXMLLoader*>::iterator pBTask = m_lTaskPool.begin();
    std::map<std::string, CFXMLLoader*>::iterator pETask = m_lTaskPool.end();
    while( pBTask != pETask)
    {
        CFXMLLoader* pLoader = pBTask->second;
        if(pLoader->Get_Status() == CFXMLLoader::E_STATUS_DONE)
        {
            std::string sRequestName = pBTask->first;
            if(m_lContainer.find(pBTask->first) != m_lContainer.end())
            {
                CSequence* pSequence = m_lContainer[pBTask->first];
                pSequence->Set_Frames(pLoader->Get_Frames());
                m_lTaskPool.erase(pBTask);
                delete pLoader;
                return;
            }
        }
        else
        {
            if(pLoader->Get_Status() == CFXMLLoader::E_STATUS_ERROR)
            {
                m_lTaskPool.erase(pBTask);
                delete pLoader;
                return;
            }
        }
        ++pBTask;
    }
}

void CDataController::UpdateThread()
{
    pthread_mutex_lock( &m_mutex );
    std::map<std::string, CFXMLLoader*>::iterator pBTask = m_lTaskPool.begin();
    std::map<std::string, CFXMLLoader*>::iterator pETask = m_lTaskPool.end();
    while( pBTask != pETask)
    {
        CFXMLLoader* pLoader = pBTask->second;
        if(pLoader->Get_Status() == CFXMLLoader::E_STATUS_NONE)
        {
            pLoader->Load(pBTask->first.c_str());
        }
        ++pBTask;
    }
    pthread_mutex_unlock( &m_mutex );
    sleep(1);
}











