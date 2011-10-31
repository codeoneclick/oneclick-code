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

void CTextureController::Get_Texture(std::string _sName, CTexture* _pTexture)
{
    if( m_container.find(_sName) != m_container.end())
    {
        _pTexture->Set_Handle(m_container[_sName].s_handle);
        _pTexture->Set_Width(m_container[_sName].s_uiWidth);
        _pTexture->Set_Height(m_container[_sName].s_uiHeight);
        _pTexture->Set_Done(true);
        return;
    }
    else
    {
        CPVRLoader* pLoader = new CPVRLoader();
        m_container[_sName] = pLoader->Load(_sName.c_str());
        _pTexture->Set_Handle(m_container[_sName].s_handle);
        _pTexture->Set_Width(m_container[_sName].s_uiWidth);
        _pTexture->Set_Height(m_container[_sName].s_uiHeight);       
        _pTexture->Set_Done(true);
        delete pLoader;
        return;
    }
}
