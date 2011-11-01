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
    
}

CTextureController::~CTextureController()
{
    
}

CTexture* CTextureController::Get_Texture(std::string _sName)
{
    CTexture* pTexture = NULL;
    if( m_container.find(_sName) != m_container.end())
    {
        pTexture = m_container[_sName];
        pTexture->IncRefCount();
    }
    else
    {
        CPVRLoader* pLoader = new CPVRLoader();
        pTexture = pLoader->Load(_sName.c_str());
        m_container[_sName] = pTexture;
        pTexture->IncRefCount();
        pTexture->Set_Done(true);
        delete pLoader;
    }
    return pTexture;
}

void CTextureController::Unload_Texture(std::string _sName)
{
    CTexture* pTexture = NULL;
    if( m_container.find(_sName) != m_container.end())
    {
        pTexture = m_container[_sName];
        pTexture->DecRefCount();
        
        if(pTexture->Get_RefCount() == 0)
        {
            delete pTexture;
            std::map<std::string, CTexture*>::iterator pIterator = m_container.find(_sName);
            m_container.erase(pIterator);
        }
    }
}
