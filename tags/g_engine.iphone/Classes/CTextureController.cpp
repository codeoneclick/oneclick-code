//
//  CTextureController.cpp
//  gEngine
//
//  Created by Snow Leopard User on 24/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CTextureController.h"
#include <cmath>
#include "stdlib.h"
#include <algorithm>

CTextureController::CTextureController()
{
    CPVRLoader* pLoader = new CPVRLoader();
    pLoader->Load("Untitled_default.pvr");
    pLoader->CommitVRAM();
    m_pStub = pLoader->Get_Source();
    pthread_mutex_init(&m_mutex, NULL);
}

CTextureController::~CTextureController()
{
    
}

CTexture* CTextureController::Get_Texture(std::string _sName, E_LOAD_THREAD _eThread)
{
    CTexture* pTexture = NULL;
    
    if(_eThread == E_THREAD_MAIN)
    {
        if( m_lContainer.find(_sName) != m_lContainer.end())
        {
            pTexture = m_lContainer[_sName];
            pTexture->IncRefCount();
        }
        else
        {
            pTexture = new CTexture();
            pTexture->Set_Handle(m_pStub->m_uiHanlde);
            pTexture->Set_Width(m_pStub->m_pDescription->m_vSize.x);
            pTexture->Set_Height(m_pStub->m_pDescription->m_vSize.y);
            CPVRLoader* pLoader = new CPVRLoader();
            pLoader->Load(_sName.c_str());
            if(pLoader->Get_Status() != CPVRLoader::E_STATUS_ERROR)
            {
                pLoader->CommitVRAM();
                CPVRLoader::SPVRSource* pSource = pLoader->Get_Source();
                pTexture->Set_Handle(pSource->m_uiHanlde);
                pTexture->Set_Width(pSource->m_pDescription->m_vSize.x);
                pTexture->Set_Height(pSource->m_pDescription->m_vSize.y);
            }
            delete pLoader;
        }
    }
    else if(_eThread == E_THREAD_BACKGROUND)
    {
        if( m_lContainer.find(_sName) != m_lContainer.end())
        {
            pTexture = m_lContainer[_sName];
            pTexture->IncRefCount();
        }
        else
        {
            if(m_lTaskPool.find(_sName) == m_lTaskPool.end())
            {
                m_lTaskPool[_sName] = new CPVRLoader();
            }
            pTexture = new CTexture();
            pTexture->Set_Handle(m_pStub->m_uiHanlde);
            pTexture->Set_Width(m_pStub->m_pDescription->m_vSize.x);
            pTexture->Set_Height(m_pStub->m_pDescription->m_vSize.y);
            m_lContainer[_sName] = pTexture;
        }
    }

    return pTexture;
}

void CTextureController::Unload_Texture(std::string _sName)
{
    CTexture* pTexture = NULL;
    if( m_lContainer.find(_sName) != m_lContainer.end())
    {
        pTexture = m_lContainer[_sName];
        pTexture->DecRefCount();
        
        if(pTexture->Get_RefCount() == 0 && pTexture->Get_Handle() != m_pStub->m_uiHanlde)
        {
            delete pTexture;
            std::map<std::string, CTexture*>::iterator pIterator = m_lContainer.find(_sName);
            m_lContainer.erase(pIterator);
        }
    }
}

void CTextureController::Update()
{
    std::map<std::string, CPVRLoader*>::iterator pBTask = m_lTaskPool.begin();
    std::map<std::string, CPVRLoader*>::iterator pETask = m_lTaskPool.end();
    while( pBTask != pETask)
    {
        CPVRLoader* pLoader = pBTask->second;
        if(pLoader->Get_Status() == CPVRLoader::E_STATUS_DONE)
        {
            pLoader->CommitVRAM();
            CPVRLoader::SPVRSource* pSource = pLoader->Get_Source();
            std::string sRequestName = pBTask->first;
            if(m_lContainer.find(pBTask->first) != m_lContainer.end())
            {
                CTexture* pTexture = m_lContainer[pBTask->first];
                pTexture->Set_Handle(pSource->m_uiHanlde);
                pTexture->Set_Width(pSource->m_pDescription->m_vSize.x);
                pTexture->Set_Height(pSource->m_pDescription->m_vSize.y);
                m_lTaskPool.erase(pBTask);
                delete pLoader;
                return;
            }
        }
        else
        {
            if(pLoader->Get_Status() == CPVRLoader::E_STATUS_ERROR)
            {
                m_lTaskPool.erase(pBTask);
                delete pLoader;
                return;
            }
        }
        ++pBTask;
    }
}

void CTextureController::UpdateThread()
{
    pthread_mutex_lock( &m_mutex );
    std::map<std::string, CPVRLoader*>::iterator pBTask = m_lTaskPool.begin();
    std::map<std::string, CPVRLoader*>::iterator pETask = m_lTaskPool.end();
    while( pBTask != pETask)
    {
        CPVRLoader* pLoader = pBTask->second;
        if(pLoader->Get_Status() == CPVRLoader::E_STATUS_NONE)
        {
            pLoader->Load(pBTask->first.c_str());
        }
        ++pBTask;
    }
    pthread_mutex_unlock( &m_mutex );
    sleep(1);
}



