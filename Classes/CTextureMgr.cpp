//
//  CTextureController.cpp
//  gEngine
//
//  Created by Snow Leopard User on 24/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CTextureMgr.h"
#include <cmath>
#include "stdlib.h"
#include <algorithm>

CTextureMgr::CTextureMgr()
{
    CParser_PVR* pParser = new CParser_PVR();
    pParser->Load("Untitled_default.pvr");
    pParser->Commit();
    m_pStub = static_cast<CTexture::SSource*>(pParser->Get_Source());
}

CTextureMgr::~CTextureMgr()
{
    
}

IResource* CTextureMgr::Load(std::string _sName, IResourceMgr::E_THREAD _eThread)
{
    CTexture* pTexture = NULL;
    
    if(_eThread == IResourceMgr::E_MAIN_THREAD)
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
            CParser_PVR* pParser = new CParser_PVR();
            pParser->Load(_sName.c_str());
            if(pParser->Get_Status() != IParser::E_ERROR_STATUS)
            {
                pParser->Commit();
                pTexture->Set_Source(pParser->Get_Source());
            }
            delete pParser;
        }
    }
    else if(_eThread == IResourceMgr::E_BACKGROUND_THREAD)
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
                m_lTaskPool[_sName] = new CParser_PVR();
            }
            pTexture = new CTexture();
            pTexture->Set_Source(m_pStub);
            m_lContainer[_sName] = pTexture;
        }
    }

    return pTexture;
}

void CTextureMgr::Unload(std::string _sName)
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



