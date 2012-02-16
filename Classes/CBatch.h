//
//  CBatch.h
//  gEngine
//
//  Created by sergey.sergeev on 12/6/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CBatch_h
#define gEngine_CBatch_h

#include "INode.h"

class CBatch
{
public:
    enum E_RENDER_MODE { E_RENDER_MODE_LINES = 0, E_RENDER_MODE_TRIANGLES };
    
    struct SSource
    {
        CMesh* m_pMesh;
        CMatrix4x4 m_mWorld;
        
        SSource();
        SSource(CMesh* _pMesh, CMatrix4x4 _mWorld)
        {
            m_pMesh = _pMesh;
            m_mWorld = _mWorld;
        };
        
    };
protected:
    std::vector<SSource> m_lContainer;
    
    CShader*        m_pShader;
    CTexture**      m_pTextures;
    CMesh*          m_pMesh;
    CMesh::SSource* m_pSource; 
    E_RENDER_MODE m_eRenderMode;
    CVertexBuffer::E_VERTEX_BUFFER_MODE m_eVertexBufferMode;
    void MakeBatch(void);
    void DestroyBatch(void);
public:
    CBatch(CVertexBuffer::E_VERTEX_BUFFER_MODE _eVertexBufferMode);
    ~CBatch();
    void Push(SSource _tSource);
    void Set_Shader(CShader* _pShader);
    void Set_Textures(CTexture** _pTextures) { m_pTextures = _pTextures; }
    void Set_RenderMode(E_RENDER_MODE _eRenderMode) { m_eRenderMode = _eRenderMode; }
    void Render();
};

#endif
