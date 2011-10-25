//
//  CResourceController.cpp
//  gEngine
//
//  Created by Snow Leopard User on 24/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CResourceController.h"

CResourceController* CResourceController::m_resourceController = NULL;

CResourceController* CResourceController::Instance()
{
    if(m_resourceController == NULL)
    {
        m_resourceController = new CResourceController();
    }
    return m_resourceController;
}

CResourceController::CResourceController()
{
    m_textureController = new CTextureController();
    m_shaderController = new CShaderController();
}

CResourceController::~CResourceController()
{
    
}