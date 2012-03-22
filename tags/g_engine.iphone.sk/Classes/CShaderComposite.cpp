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

#include "../Shaders/ShaderPhong.vert"
#include "../Shaders/ShaderPhong.frag"

#include "../Shaders/ShaderLambert.vert"
#include "../Shaders/ShaderLambert.frag"

#include "../Shaders/ShaderCellShading.vert"
#include "../Shaders/ShaderCellShading.frag"

#include "../Shaders/ShaderGooch.vert"
#include "../Shaders/ShaderGooch.frag"

#include "../Shaders/ShaderRimLight.vert"
#include "../Shaders/ShaderRimLight.frag"

#include "../Shaders/ShaderPostBloomCombine.vert"
#include "../Shaders/ShaderPostBloomCombine.frag"

#include "../Shaders/ShaderPostBloomExtract.vert"
#include "../Shaders/ShaderPostBloomExtract.frag"

#include "../Shaders/ShaderPostBlur.vert"
#include "../Shaders/ShaderPostBlur.frag"

#include "../Shaders/ShaderParallax.vert"
#include "../Shaders/ShaderParallax.frag"

#include "../Shaders/ShaderLandscape.vert"
#include "../Shaders/ShaderLandscape.frag"

#include "../Shaders/ShaderUnit.vert"
#include "../Shaders/ShaderUnit.frag"

CShaderComposite* CShaderComposite::m_pInstance = NULL;

CShaderComposite::CShaderComposite()
{
    CParser_GLSL *pParser = new CParser_GLSL(); 
    CParser_GLSL::SGLSLData pData;
    
    pData = pParser->Load(ShaderColorV, ShaderColorF);
    CShader* pShader = new CShader(pData.s_pHandle);
    m_lContainer[IResource::E_SHADER_COLOR] = pShader;
    
    pData = pParser->Load(ShaderTextureV, ShaderTextureF);
    pShader = new CShader(pData.s_pHandle);
    m_lContainer[IResource::E_SHADER_TEXTURE] = pShader;
    
    pData = pParser->Load(ShaderLambertV, ShaderLambertF);
    pShader = new CShader(pData.s_pHandle);
    m_lContainer[IResource::E_SHADER_LAMBERT] = pShader;
    
    pData = pParser->Load(ShaderPhongV, ShaderPhongF);
    pShader = new CShader(pData.s_pHandle);
    m_lContainer[IResource::E_SHADER_PHONG] = pShader;
    
    pData = pParser->Load(ShaderCellShadingV, ShaderCellShadingF);
    pShader = new CShader(pData.s_pHandle);
    m_lContainer[IResource::E_SHADER_CELL_SHADING] = pShader;
    
    pData = pParser->Load(ShaderGoochV, ShaderGoochF);
    pShader = new CShader(pData.s_pHandle);
    m_lContainer[IResource::E_SHADER_GOOCH] = pShader;
    
    pData = pParser->Load(ShaderRimLightV, ShaderRimLightF);
    pShader = new CShader(pData.s_pHandle);
    m_lContainer[IResource::E_SHADER_RIM_LIGHT] = pShader;
    
    pData = pParser->Load(ShaderPostBloomExtractV, ShaderPostBloomExtractF);
    pShader = new CShader(pData.s_pHandle);
    m_lContainer[IResource::E_SHADER_BLOOM_EXTRACT] = pShader;
    
    pData = pParser->Load(ShaderPostBloomCombineV, ShaderPostBloomCombineF);
    pShader = new CShader(pData.s_pHandle);
    m_lContainer[IResource::E_SHADER_BLOOM_COMBINE] = pShader;
    
    pData = pParser->Load(ShaderPostBlurV, ShaderPostBlurF);
    pShader = new CShader(pData.s_pHandle);
    m_lContainer[IResource::E_SHADER_BLUR] = pShader;
    
    pData = pParser->Load(ShaderParallaxV, ShaderParallaxF);
    pShader = new CShader(pData.s_pHandle);
    m_lContainer[IResource::E_SHADER_PARALLAX] = pShader;
    
    pData = pParser->Load(ShaderLandscapeV, ShaderLandscapeF);
    pShader = new CShader(pData.s_pHandle);
    m_lContainer[IResource::E_SHADER_LANDSCAPE] = pShader;
    
    pData = pParser->Load(ShaderUnitV, ShaderUnitF);
    pShader = new CShader(pData.s_pHandle);
    m_lContainer[IResource::E_SHADER_UNIT] = pShader;

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
    if( m_lContainer.find(_eShader) != m_lContainer.end())
    {
        return m_lContainer[_eShader];
    }
    else
    {
        return NULL;
    }
}