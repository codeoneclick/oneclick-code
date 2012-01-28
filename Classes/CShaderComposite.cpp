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

#include "../Shaders/ShaderColorVertexDiffuse.vert"
#include "../Shaders/ShaderColorVertexDiffuse.frag"

#include "../Shaders/ShaderTextureVertexDiffuse.vert"
#include "../Shaders/ShaderTextureVertexDiffuse.frag"

#include "../Shaders/ShaderTexturePixelDiffuse.vert"
#include "../Shaders/ShaderTexturePixelDiffuse.frag"

#include "../Shaders/ShaderTexturePixelDiffuseSpecularColor.vert"
#include "../Shaders/ShaderTexturePixelDiffuseSpecularColor.frag"

#include "../Shaders/ShaderTexturePixelDiffuseSpecularTexture.vert"
#include "../Shaders/ShaderTexturePixelDiffuseSpecularTexture.frag"


CShaderComposite* CShaderComposite::m_pInstance = NULL;

CShaderComposite::CShaderComposite()
{
    CParser_GLSL *pParser = new CParser_GLSL(); 
    CParser_GLSL::SGLSLData pData;
    
    pData = pParser->Load(ShaderColorV, ShaderColorF);
    CShader* pShader = new CShader();
    pShader->Set_pHandle(pData.s_pHandle);
    pShader->Commit();
    m_lContainer[E_COLOR] = pShader;
    
    pData = pParser->Load(ShaderTextureV, ShaderTextureF);
    pShader = new CShader();
    pShader->Set_pHandle(pData.s_pHandle);
    pShader->Commit();
    m_lContainer[E_TEXTURE] = pShader;
    
    pData = pParser->Load(ShaderColorVertexDiffuseV, ShaderColorVertexDiffuseF);
    pShader = new CShader();
    pShader->Set_pHandle(pData.s_pHandle);
    pShader->Commit();
    m_lContainer[E_COLOR_VERTEX_DIFFUSE] = pShader;
    
    pData = pParser->Load(ShaderTextureVertexDiffuseV, ShaderTextureVertexDiffuseF);
    pShader = new CShader();
    pShader->Set_pHandle(pData.s_pHandle);
    pShader->Commit();
    m_lContainer[E_TEXTURE_VERTEX_DIFFUSE] = pShader;
    
    pData = pParser->Load(ShaderTexturePixelDiffuseV, ShaderTexturePixelDiffuseF);
    pShader = new CShader();
    pShader->Set_pHandle(pData.s_pHandle);
    pShader->Commit();
    m_lContainer[E_TEXTURE_PIXEL_DIFFUSE] = pShader;
    
    pData = pParser->Load(ShaderTexturePixelDiffuseSpecularColorV, ShaderTexturePixelDiffuseSpecularColorF);
    pShader = new CShader();
    pShader->Set_pHandle(pData.s_pHandle);
    pShader->Commit();
    m_lContainer[E_TEXTURE_PIXEL_DIFFUSE_SPECULAR_COLOR] = pShader;
    
    pData = pParser->Load(ShaderTexturePixelDiffuseSpecularTextureV, ShaderTexturePixelDiffuseSpecularTextureF);
    pShader = new CShader();
    pShader->Set_pHandle(pData.s_pHandle);
    pShader->Commit();
    m_lContainer[E_TEXTURE_PIXEL_DIFFUSE_SPECULAR_TEXTURE] = pShader;
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
    if( m_lContainer.find(_eShader) != m_lContainer.end())
    {
        return m_lContainer[_eShader];
    }
    else
    {
        return NULL;
    }
}