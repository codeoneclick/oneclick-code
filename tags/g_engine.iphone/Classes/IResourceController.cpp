//
//  IResourceController.cpp
//  gEngine
//
//  Created by sergey.sergeev on 11/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "IResourceController.h"

IResourceController::IResourceController()
{
    pthread_mutex_init(&m_mutex, NULL);
}

IResourceController::~IResourceController()
{
    
}


void IResourceController::Thread()
{
    pthread_mutex_lock( &m_mutex );
    std::map<std::string, ILoader*>::iterator pBTask = m_lTaskPool.begin();
    std::map<std::string, ILoader*>::iterator pETask = m_lTaskPool.end();
    while( pBTask != pETask)
    {
        ILoader* pLoader = pBTask->second;
        if(pLoader->Get_Status() == ILoader::E_STATUS_NONE)
        {
            pLoader->Load(pBTask->first.c_str());
        }
        ++pBTask;
    }
    pthread_mutex_unlock( &m_mutex );
    sleep(1);
}

void IResourceController::Update()
{
    std::map<std::string, ILoader*>::iterator pBTask = m_lTaskPool.begin();
    std::map<std::string, ILoader*>::iterator pETask = m_lTaskPool.end();
    while( pBTask != pETask)
    {
        ILoader* pLoader = (ILoader*)pBTask->second;
        if(pLoader->Get_Status() == ILoader::E_STATUS_DONE)
        {
            pLoader->Commit();
            std::string sRequestName = pBTask->first;
            if(m_lContainer.find(pBTask->first) != m_lContainer.end())
            {
                IResource* pResource = m_lContainer[pBTask->first];
                pResource->Set_Source(pLoader->Get_Source());
                m_lTaskPool.erase(pBTask);
                delete pLoader;
                return;
            }
        }
        else
        {
            if(pLoader->Get_Status() == ILoader::E_STATUS_ERROR)
            {
                m_lTaskPool.erase(pBTask);
                delete pLoader;
                return;
            }
        }
        ++pBTask;
    }
}

