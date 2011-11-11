//
//  CShaderComposite.cpp
//  gEngine
//
//  Created by Snow Leopard User on 24/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CShaderComposite.h"

#define STRINGIFY(A)  #A
#include "../Shaders/ShaderTexture.vert"
#include "../Shaders/ShaderTexture.frag"

#include "../Shaders/ShaderColor.vert"
#include "../Shaders/ShaderColor.frag"

CShaderComposite* CShaderComposite::m_pInstance = NULL;

CShaderComposite::CShaderComposite()
{
    CParser_GLSL *pParser = new CParser_GLSL(); 
    CParser_GLSL::SGLSLData pData = pParser->Load(ShaderTextureV, ShaderTextureF);
    m_container[E_TEXTURE] = pData;

    pData = pParser->Load(ShaderColorV, ShaderColorF);
    m_container[E_COLOR] = pData;
}

CShaderComposite::~CShaderComposite()
{
    
}

CShaderComposite* CShaderComposite::Instance()
{
    if(m_pInstance == NULL)
    {
        m_pInstance = new CShaderComposite();
    }
    return m_pInstance;
}

CShader* CShaderComposite::Get_Shader(E_SHADER _eShader)
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