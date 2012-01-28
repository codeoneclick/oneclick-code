//
//  CTexture.cpp
//  gEngine
//
//  Created by Snow Leopard User on 25/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CTexture.h"

CTexture::CTexture()
{
    m_eParser = IResource::E_PVR_PARSER;
}

CTexture::~CTexture()
{
    glDeleteTextures(1, &m_uiHandle);
}

void CTexture::Set_Source(void *_pSource)
{
    SSource* pSource = static_cast<SSource*>(_pSource);
    m_uiHandle = pSource->m_uiHanlde;
    m_uiWidth  = pSource->m_uiWidth;
    m_uiHeight = pSource->m_uiHeight;
}
