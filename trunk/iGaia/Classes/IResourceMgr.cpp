//
//  IResourceMgr.cpp
//  iGaia
//
//  Created by sergey.sergeev on 11/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "IResourceMgr.h"

IResourceMgr::IResourceMgr()
{
    pthread_mutex_init(&m_mutex, NULL);
}

IResourceMgr::~IResourceMgr()
{
    
}


void IResourceMgr::Thread()
{
    pthread_mutex_lock( &m_mutex );
    std::map<std::string, IParser*>::iterator pBTask = m_lTaskPool.begin();
    std::map<std::string, IParser*>::iterator pETask = m_lTaskPool.end();
    while( pBTask != pETask)
    {
        IParser* pParser = pBTask->second;
        if(pParser->Get_Status() == IParser::E_NONE_STATUS)
        {
            pParser->Load(pBTask->first.c_str());
        }
        ++pBTask;
    }
    pthread_mutex_unlock( &m_mutex );
    sleep(1);
}

void IResourceMgr::Update()
{
    std::map<std::string, IParser*>::iterator pBTask = m_lTaskPool.begin();
    std::map<std::string, IParser*>::iterator pETask = m_lTaskPool.end();
    while( pBTask != pETask)
    {
        IParser* pParser = (IParser*)pBTask->second;
        if(pParser->Get_Status() == IParser::E_DONE_STATUS)
        {
            pParser->Commit();
            std::string sRequestName = pBTask->first;
            if(m_lContainer.find(pBTask->first) != m_lContainer.end())
            {
                IResource* pResource = m_lContainer[pBTask->first];
                pResource->Set_Source(pParser->Get_Source());
                m_lTaskPool.erase(pBTask);
                delete pParser;
                return;
            }
        }
        else
        {
            if(pParser->Get_Status() == IParser::E_ERROR_STATUS)
            {
                m_lTaskPool.erase(pBTask);
                delete pParser;
                return;
            }
        }
        ++pBTask;
    }
}

