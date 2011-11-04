//
//  CResourceController.cpp
//  gEngine
//
//  Created by Snow Leopard User on 24/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CResource.h"

void* UpdateThread(void *_pParam)
{
    CResource* pController = (CResource*)_pParam;
    while (true)
    {
        pController->m_pTextureController->Thread();
        pController->m_pDataController->Thread();
    }
}

CResource* CResource::m_pInstance = NULL;

CResource* CResource::Instance()
{
    if(m_pInstance == NULL)
    {
        m_pInstance = new CResource();
    }
    return m_pInstance;
}

CResource::CResource()
{
    m_pTextureController = new CTextureController();
    m_pShaderController = new CShaderController();
    m_pDataController = new CDataController();
    pthread_create(&m_thread, NULL, UpdateThread, (void*)this);
}

CResource::~CResource()
{
    
}

void CResource::Update()
{
    m_pTextureController->Update();
    m_pDataController->Update();
}

IResource* CResource::Load(std::string _sName, IResource::E_PARSER _eParser, IResource::E_LOAD_THREAD _eThread)
{
    switch (_eParser)
    {
        case IResource::E_PVR :
            return m_pTextureController->Load(_sName, _eThread);
            break;
        case IResource::E_FXML:
            return m_pDataController->Load(_sName, _eThread);
            break;
        default:
            return NULL;
            break;
    }
}

void CResource::Unload(IResource *_pResource)
{
    switch (_pResource->Get_Parser())
    {
        case IResource::E_PVR :
            m_pTextureController->Unload(_pResource->Get_Name());
            break;
        case IResource::E_FXML:
            m_pDataController->Unload(_pResource->Get_Name());
            break;
        default:
            break;
    }
}

/*
CTexture* CResource::Get_Texture(std::string _sName, CTextureController::E_LOAD_THREAD _eThread)
{
    return m_pTextureController->Get_Texture(_sName, _eThread);
}

void CResource::Unload_Texture(std::string _sName)
{
    m_pTextureController->Unload_Texture(_sName);
}

CSequence* CResource::Get_Sequence(std::string _sName, CDataController::E_LOAD_THREAD _eThread)
{
    return m_pDataController->Get_Sequence(_sName, _eThread);
}

void CResource::Unload_Sequence(std::string _sName)
{
    m_pDataController->Unload_Sequence(_sName);
}*/

void CResource::Get_Shader(std::string _sName, CShader *_pShader)
{
    m_pShaderController->Get_Shader( _sName, _pShader);
}


