//
//  CShaderComposite.cpp
//  iGaia
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

#include "../Shaders/ShaderPostEdgeDetect.vert"
#include "../Shaders/ShaderPostEdgeDetect.frag"

#include "../Shaders/ShaderPostNormalDepth.vert"
#include "../Shaders/ShaderPostNormalDepth.frag"

#include "../Shaders/ShaderProjectTexture.vert"
#include "../Shaders/ShaderProjectTexture.frag"

#include "../Shaders/ShaderWater.vert"
#include "../Shaders/ShaderWater.frag"

#include "../Shaders/ShaderPreNormalDepthUnit.vert"
#include "../Shaders/ShaderPreNormalDepthUnit.frag"

#include "../Shaders/ShaderAnimTexCoordUnit.vert"
#include "../Shaders/ShaderAnimTexCoordUnit.frag"

#include "../Shaders/ShaderPreShadowMap.vert"
#include "../Shaders/ShaderPreShadowMap.frag"

#include "../Shaders/ShaderTextureCube.vert"
#include "../Shaders/ShaderTextureCube.frag"

#include "../Shaders/ShaderShadowPlane.vert"
#include "../Shaders/ShaderShadowPlane.frag"

#include "../Shaders/ShaderDecal.vert"
#include "../Shaders/ShaderDecal.frag"

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
    
    pData = pParser->Load(ShaderPostEdgeDetectV, ShaderPostEdgeDetectF);
    pShader = new CShader(pData.s_pHandle);
    m_lContainer[IResource::E_SHADER_EDGE_DETECT] = pShader;
    
    pData = pParser->Load(ShaderPostNormalDepthV, ShaderPostNormalDepthF);
    pShader = new CShader(pData.s_pHandle);
    m_lContainer[IResource::E_SHADER_NORMAL_DEPTH] = pShader;
    
    pData = pParser->Load(ShaderProjectTextureV, ShaderProjectTextureF);
    pShader = new CShader(pData.s_pHandle);
    m_lContainer[IResource::E_SHADER_PROJECT_TEXTURE] = pShader;
    
    pData = pParser->Load(ShaderWaterV, ShaderWaterF);
    pShader = new CShader(pData.s_pHandle);
    m_lContainer[IResource::E_SHADER_WATER] = pShader;
    
    pData = pParser->Load(ShaderPreNormalDepthUnitV, ShaderPreNormalDepthUnitF);
    pShader = new CShader(pData.s_pHandle);
    m_lContainer[IResource::E_SHADER_PRE_NORMAL_DEPTH_UNIT] = pShader;

    pData = pParser->Load(ShaderAnimTexCoordUnitV, ShaderAnimTexCoordUnitF);
    pShader = new CShader(pData.s_pHandle);
    m_lContainer[IResource::E_SHADER_ANIM_TEXCOORD_UNIT] = pShader;
    
    pData = pParser->Load(ShaderPreShadowMapV, ShaderPreShadowMapF);
    pShader = new CShader(pData.s_pHandle);
    m_lContainer[IResource::E_SHADER_SHADOW_MAP] = pShader;
    
    pData = pParser->Load(ShaderTextureCubeV, ShaderTextureCubeF);
    pShader = new CShader(pData.s_pHandle);
    m_lContainer[IResource::E_SHADER_TEXTURE_CUBE] = pShader;
    
    pData = pParser->Load(ShaderShadowPlaneV, ShaderShadowPlaneF);
    pShader = new CShader(pData.s_pHandle);
    m_lContainer[IResource::E_SHADER_SHADOW_PLANE] = pShader;
    
    pData = pParser->Load(ShaderDecalV, ShaderDecalF);
    pShader = new CShader(pData.s_pHandle);
    m_lContainer[IResource::E_SHADER_DECAL] = pShader;
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