//
//  CScreenSpacePostMgr.h
//  iGaia
//
//  Created by sergey.sergeev on 12/1/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CScreenSpacePostMgr_h
#define iGaia_CScreenSpacePostMgr_h

#include "CShader.h"
class CMesh;

#define k_OFFSCREEN_FBO_COUNT 5

class CScreenSpacePostMgr
{
public:
    enum E_OFFSCREEN_MODE { E_OFFSCREEN_MODE_SIMPLE = 0, E_OFFSCREEN_MODE_REFLECTION, E_OFFSCREEN_MODE_BLOOM_EXTRACT, E_OFFSCREEN_MODE_BLOOM_COMBINE, E_OFFSCREEN_MODE_BLUR };
protected:
    static int k_REFLECTION_TEXTURE_SIZE;
    static int k_REFRACTION_TEXTURE_SIZE;
    
    GLuint m_hOffScreenFBOs[k_OFFSCREEN_FBO_COUNT];
    GLuint m_hOffScreenTextures[k_OFFSCREEN_FBO_COUNT];
    GLuint m_hOffScreenDepthBuffers[k_OFFSCREEN_FBO_COUNT];
    glm::vec2 m_pOffScreenSize[k_OFFSCREEN_FBO_COUNT];
    GLuint m_hScreenFBO;
    GLuint m_hScreenRenderBuffer;
    
    /*GLuint m_hTexturePostSimple;
    GLuint m_hTexturePostBloomExtract;
    GLuint m_hTexturePostBloomCombine;
    GLuint m_hTexturePostBlur;
    
    GLuint m_hOffScreenFrameBuffer;
    GLuint m_hScreenFrameBuffer;
    GLuint m_hDepthBuffer;
    GLuint m_hRenderBuffer;
    GLuint m_hReflectionFrameBuffer;*/
    
    CShader* m_pShaderPostSimple;
    CShader* m_pShaderPostBloomExtract;
    CShader* m_pShaderPostBloomCombine;
    CShader* m_pShaderPostBlur;
    
    //GLuint m_hTextureReflection;
    //GLuint m_hTextureRefraction;
    
    CShader* m_pShaderReflection;
    
    CMesh* m_pMesh;
public:
    CScreenSpacePostMgr(void);
    ~CScreenSpacePostMgr(void);
    
    void EnableOffScreenMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE _eMode);
    void DisableOffScreenMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE _eMode);
    void EnableScreenMode(void);
    void DisableScreenMode(void);
    
    void Render_PostSimple(void);
    void Render_PostBloomExtract(void);
    void Render_PostBloomCombine(void);
    void Render_PostBlur(void);
    
    GLuint Get_OffScreenTexture(CScreenSpacePostMgr::E_OFFSCREEN_MODE _eMode) { return m_hOffScreenTextures[_eMode]; }
};

#endif