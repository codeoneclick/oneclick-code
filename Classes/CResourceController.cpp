//
//  CResourceController.cpp
//  gEngine
//
//  Created by Snow Leopard User on 24/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CResourceController.h"

void* UpdateThread(void *_pParam)
{
    CResourceController* pController = (CResourceController*)_pParam;
    while (true)
    {
        pController->TextureController()->UpdateThread();
    }
}

CResourceController* CResourceController::m_pInstance = NULL;

CResourceController* CResourceController::Instance()
{
    if(m_pInstance == NULL)
    {
        m_pInstance = new CResourceController();
    }
    return m_pInstance;
}

CResourceController::CResourceController()
{
    m_pTextureController = new CTextureController();
    m_pShaderController = new CShaderController();
    m_pDataController = new CDataController();
    pthread_create(&m_thread, NULL, UpdateThread, (void*)this);
}

CResourceController::~CResourceController()
{
    
}


void CResourceController::Update()
{
    m_pTextureController->Update();
}


