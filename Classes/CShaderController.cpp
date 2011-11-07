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
#include "../Shaders/ShaderTexture.vert"
#include "../Shaders/ShaderTexture.frag"

#include "../Shaders/ShaderColor.vert"
#include "../Shaders/ShaderColor.frag"

CShaderController::CShaderController()
{
    CGLSLLoader *pLoader = new CGLSLLoader(); 
    CGLSLLoader::SGLSLData pData = pLoader->Load(ShaderTextureV, ShaderTextureF);
    m_container[E_TEXTURE] = pData;

    pData = pLoader->Load(ShaderColorV, ShaderColorF);
    m_container[E_COLOR] = pData;
}

CShaderController::~CShaderController()
{
    
}

CShader* CShaderController::Get_Shader(E_SHADER _eShader)
{
    CShader* pShader = NULL;
    if( m_container.find(_eShader) != m_container.end())
    {
        pShader = new CShader();
        pShader->Set_pHandle(m_container[_eShader].s_pHandle);
        pShader->Set_vHandle(m_container[_eShader].s_vHandle);
        pShader->Set_fHandle(m_container[_eShader].s_fHandle);
        return pShader;
    }
    else
    {
        return NULL;
    }
}