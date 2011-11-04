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
    pLoader->Commit();
    m_pStub = static_cast<CTexture::SSource*>(pLoader->Get_Source());
}

CTextureController::~CTextureController()
{
    
}

IResource* CTextureController::Load(std::string _sName, IResource::E_LOAD_THREAD _eThread)
{
    CTexture* pTexture = NULL;
    
    if(_eThread == IResource::E_THREAD_MAIN)
    {
        if( m_lContainer.find(_sName) != m_lContainer.end())
        {
            pTexture = static_cast<CTexture*>(m_lContainer[_sName]);
            pTexture->IncRefCount();
        }
        else
        {
            pTexture = new CTexture();
            pTexture->Set_Source(m_pStub);
            CPVRLoader* pLoader = new CPVRLoader();
            pLoader->Load(_sName.c_str());
            if(pLoader->Get_Status() != ILoader::E_STATUS_ERROR)
            {
                pLoader->Commit();
                pTexture->Set_Source(pLoader->Get_Source());
            }
            delete pLoader;
        }
    }
    else if(_eThread == IResource::E_THREAD_BACKGROUND)
    {
        if( m_lContainer.find(_sName) != m_lContainer.end())
        {
            pTexture = static_cast<CTexture*>(m_lContainer[_sName]);
            pTexture->IncRefCount();
        }
        else
        {
            if(m_lTaskPool.find(_sName) == m_lTaskPool.end())
            {
                m_lTaskPool[_sName] = new CPVRLoader();
            }
            pTexture = new CTexture();
            pTexture->Set_Source(m_pStub);
            m_lContainer[_sName] = pTexture;
        }
    }

    return pTexture;
}

void CTextureController::Unload(std::string _sName)
{
    CTexture* pTexture = NULL;
    if( m_lContainer.find(_sName) != m_lContainer.end())
    {
        pTexture = static_cast<CTexture*>(m_lContainer[_sName]);
        pTexture->DecRefCount();
        
        if(pTexture->Get_RefCount() == 0 && pTexture->Get_Handle() != m_pStub->m_uiHanlde)
        {
            delete pTexture;
            std::map<std::string, IResource*>::iterator pIterator = m_lContainer.find(_sName);
            m_lContainer.erase(pIterator);
        }
    }
}



