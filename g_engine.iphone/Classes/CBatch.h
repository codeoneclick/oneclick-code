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
protected:
    std::vector<INode*> m_lContainer;
    
    Matrix4x4   m_mWorld;
    CShader*    m_pShader;
    CTexture**  m_pTextures;
    CMesh*      m_pMesh;
    CMesh::SSource* m_pSource; 
    Vector4d    m_vColor;
    int         m_iNumVertexes;
    int         m_iNumIndexes;
    
    void Create();
public:
    CBatch();
    ~CBatch();
    void Clear();
    void Push(INode* _pNode);
    void Render();
};

#endif
