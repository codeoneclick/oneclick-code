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
#include <Box2D/Box2D.h>

class INode
{
protected:
    Matrix4x4 m_mScale;
    Matrix4x4 m_mRotation;
    Matrix4x4 m_mTranslation;
    Matrix4x4 m_mWorld;
    
    Matrix4x4* m_mProjection;
    Matrix4x4* m_mView;
    
    CShader*       m_pShader;
    CTexture*      m_pTexture;
    CVertexBuffer* m_pVb;
    GLubyte*       m_pIb;
    
    b2BodyDef      m_pBodyDef;
    b2Body*        m_pBody;
    
    Vector2d     m_vScale;
    Vector3d     m_vPosition;
    float        m_fRotation;
    
    std::string  m_strResTexture;
    std::string  m_strResShader;
public:
    INode();
    virtual ~INode();
    virtual void Update(float _fTime);
    virtual void Render() = 0;
    inline CVertexBuffer* Get_VB() { return m_pVb; }
    inline GLubyte* Get_IB() { return m_pIb; }
    Vector3d Get_Position() { return m_vPosition; }
    virtual void Set_Position(Vector3d &_vPosition) { m_vPosition = _vPosition; }
    float Get_Rotation() { return m_fRotation; }
    virtual void Set_Rotation(float _fRotation) { m_fRotation = _fRotation; }
    Vector2d Get_Scale() { return m_vScale; }
    virtual void Set_Scale(Vector2d &_vScale) { m_vScale = _vScale; }
};


#endif
