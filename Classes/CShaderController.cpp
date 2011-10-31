//
//  CShaderController.cpp
//  gEngine
//
//  Created by Snow Leopard User on 24/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CShaderController.h"

#define STRINGIFY(A)  #A
#include "../Shaders/Basic.vert"
#include "../Shaders/Basic.frag"

CShaderController::CShaderController()
{
    
}

CShaderController::~CShaderController()
{
    
}

void CShaderController::Get_Shader(std::string _sName, CShader* _pShader)
{
    if( m_container.find(_sName) != m_container.end())
    {
        _pShader->Set_pHandle(m_container[_sName].s_pHandle);
        _pShader->Set_vHandle(m_container[_sName].s_vHandle);
        _pShader->Set_fHandle(m_container[_sName].s_fHandle);
        _pShader->Set_Done(true);
        return;
    }
    else
    {
        CGLSLLoader *pLoader = new CGLSLLoader(); 
        CGLSLLoader::SGLSLData data = pLoader->Load(BasicVertexShader,BasicFragmentShader);
        _pShader->Set_pHandle(data.s_pHandle);
        _pShader->Set_vHandle(data.s_vHandle);
        _pShader->Set_fHandle(data.s_fHandle);
        _pShader->Set_Done(true);
        m_container[_sName] = data;
        delete pLoader;
        return;
    }
}