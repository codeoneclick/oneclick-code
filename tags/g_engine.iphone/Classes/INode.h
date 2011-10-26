//
//  INode.h
//  gEngine
//
//  Created by sergey.sergeev on 10/21/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_INode_h
#define gEngine_INode_h

#include "CMatrix.h"
#include "CShader.h"
#include "CVertexBuffer.h"
#include "CCamera.h"
#include "CResourceController.h"

class INode
{
protected:
    Matrix4x4 m_mScale;
    Matrix4x4 m_mRotation;
    Matrix4x4 m_mTranslation;
    Matrix4x4 m_mWorld;
    
    Matrix4x4 *m_mProjection;
    Matrix4x4 *m_mView;
    
    CShader       *m_shader;
    CTexture      *m_texture;
    CVertexBuffer *m_vb;
    GLubyte       *m_ib;
public:
    INode();
    ~INode();
    virtual void Update(float _fTime);
    virtual void Render() = 0;
    inline CVertexBuffer* Get_VB() { return m_vb; }
    inline GLubyte* Get_IB() { return m_ib; }
public:
    Vector2d     m_vScale;
    Vector3d     m_vPosition;
    float        m_fRotation;
};


#endif
