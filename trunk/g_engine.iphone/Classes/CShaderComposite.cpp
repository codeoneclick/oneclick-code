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
    m_lContainer[IResource::E_COLOR] = pData;
    
    pData = pParser->Load(ShaderTextureV, ShaderTextureF);
    m_lContainer[IResource::E_TEXTURE] = pData;
    
    pData = pParser->Load(ShaderColorVertexDiffuseV, ShaderColorVertexDiffuseF);
    m_lContainer[IResource::E_COLOR_VERTEX_DIFFUSE] = pData;
    
    pData = pParser->Load(ShaderTextureVertexDiffuseV, ShaderTextureVertexDiffuseF);
    m_lContainer[IResource::E_TEXTURE_VERTEX_DIFFUSE] = pData;
    
    pData = pParser->Load(ShaderTexturePixelDiffuseV, ShaderTexturePixelDiffuseF);
    m_lContainer[IResource::E_TEXTURE_PIXEL_DIFFUSE] = pData;
    
    pData = pParser->Load(ShaderTexturePixelDiffuseSpecularColorV, ShaderTexturePixelDiffuseSpecularColorF);
    m_lContainer[IResource::E_TEXTURE_PIXEL_DIFFUSE_SPECULAR_COLOR] = pData;
    
    pData = pParser->Load(ShaderTexturePixelDiffuseSpecularTextureV, ShaderTexturePixelDiffuseSpecularTextureF);
    m_lContainer[IResource::E_TEXTURE_PIXEL_DIFFUSE_SPECULAR_TEXTURE] = pData;
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

CShader* CShaderComposite::Get_Shader(IResource::E_SHADER _eShader)
{
    CShader* pShader = NULL;
    if( m_lContainer.find(_eShader) != m_lContainer.end())
    {
        pShader = new CShader();
        pShader->Set_ProgramHandle(m_lContainer[_eShader].s_pHandle);
        pShader->Commit();
        return pShader;
    }
    else
    {
        return NULL;
    }
}