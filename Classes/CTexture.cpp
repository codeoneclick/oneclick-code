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
    m_bDone = false;
    m_uiRefCount = 0;
}

CTexture::~CTexture()
{
    glDeleteTextures(1, &m_handle);
}