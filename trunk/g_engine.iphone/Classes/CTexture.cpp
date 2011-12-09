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
    glDeleteTextures(1, &m_pSource->m_hTextureHanlde);
    delete m_pSource;
}

void CTexture::Set_Source(void *_pSource)
{
    m_pSource = static_cast<SSource*>(_pSource);
}
