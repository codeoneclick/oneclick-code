//
//  CResourceMgr.cpp
//  gEngine
//
//  Created by Snow Leopard User on 24/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CResourceMgr.h"

void* Thread(void *_pParam)
{
    CResourceMgr* pInstance = (CResourceMgr*)_pParam;
    while (true)
    {
        std::map<IResourceMgr::E_MGR,IResourceMgr*>::iterator pBMgr = pInstance->m_lMgr.begin();
        std::map<IResourceMgr::E_MGR,IResourceMgr*>::iterator pEMgr = pInstance->m_lMgr.end();
        while( pBMgr != pEMgr)
        {
            pBMgr->second->Thread();
            ++pBMgr;
        }
    }
}

CResourceMgr* CResourceMgr::m_pInstance = NULL;

CResourceMgr* CResourceMgr::Instance()
{
    if(m_pInstance == NULL)
    {
        m_pInstance = new CResourceMgr();
    }
    return m_pInstance;
}

CResourceMgr::CResourceMgr()
{
    m_lMgr[IResourceMgr::E_TEXTURE_MGR] = new CTextureMgr();
    m_lMgr[IResourceMgr::E_SEQUENCE_MGR] = new CSequenceMgr();
    pthread_create(&m_thread, NULL, Thread, (void*)this);
}

CResourceMgr::~CResourceMgr()
{
    
}

void CResourceMgr::Update()
{
    std::map<IResourceMgr::E_MGR,IResourceMgr*>::iterator pBMgr = m_lMgr.begin();
    std::map<IResourceMgr::E_MGR,IResourceMgr*>::iterator pEMgr = m_lMgr.end();
    while( pBMgr != pEMgr)
    {
        pBMgr->second->Update();
        ++pBMgr;
    }
}

IResource* CResourceMgr::Load(const std::string& _sName,IResourceMgr::E_MGR _eMgr, IResourceMgr::E_PARSER _eParser, IResourceMgr::E_THREAD _eThread)
{
    switch (_eParser)
    {
        case IResourceMgr::E_PVR_PARSER :
            return m_lMgr[IResourceMgr::E_TEXTURE_MGR]->Load(_sName, _eThread);
            break;
        case IResourceMgr::E_SEQ_PARSER :
            return m_lMgr[IResourceMgr::E_SEQUENCE_MGR]->Load(_sName, _eThread);
            break;
        default:
            return NULL;
            break;
    }
}

void CResourceMgr::Unload(IResource *_pResource)
{
    switch (_pResource->Get_Parser())
    {
        case IResourceMgr::E_PVR_PARSER :
            m_lMgr[IResourceMgr::E_TEXTURE_MGR]->Unload(_pResource->Get_Name());
            break;
        case IResourceMgr::E_SEQ_PARSER :
            m_lMgr[IResourceMgr::E_SEQUENCE_MGR]->Unload(_pResource->Get_Name());
            break;
        default:
            break;
    }
}

