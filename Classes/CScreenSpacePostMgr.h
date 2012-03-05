//
//  CScreenSpacePostMgr.h
//  gEngine
//
//  Created by sergey.sergeev on 12/1/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CScreenSpacePostMgr_h
#define gEngine_CScreenSpacePostMgr_h

#include "CShader.h"
class CMesh;

class CScreenSpacePostMgr
{
public:
    enum E_POST_TEXTURE { E_POST_TEXTURE_SIMPLE = 0, E_POST_TEXTURE_BLOOM_EXTRACT, E_POST_TEXTURE_BLOOM_COMBINE, E_POST_TEXTURE_BLUR };
protected:
    GLuint m_hTexturePostSimple;
    GLuint m_hTexturePostBloomExtract;
    GLuint m_hTexturePostBloomCombine;
    GLuint m_hTexturePostBlur;
    
    GLuint m_hOffScreenFrameBuffer;
    GLuint m_hScreenFrameBuffer;
    GLuint m_hDepthBuffer;
    GLuint m_hRenderBuffer;
    
    CShader* m_pShaderPostSimple;
    CShader* m_pShaderPostBloomExtract;
    CShader* m_pShaderPostBloomCombine;
    CShader* m_pShaderPostBlur;
    
    CMesh* m_pMesh;
public:
    CScreenSpacePostMgr();
    ~CScreenSpacePostMgr();
    
    void BindRenderBufferAsBuffer(void);
    void BindRenderBufferAsTexture(CScreenSpacePostMgr::E_POST_TEXTURE _ePostTexture);
    void Render_PostSimple(void);
    void Render_PostBloomExtract(void);
    void Render_PostBloomCombine(void);
    void Render_PostBlur(void);
};

#endif