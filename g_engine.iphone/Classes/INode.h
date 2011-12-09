//
//  INode.h
//  gEngine
//
//  Created by sergey.sergeev on 11/28/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_INode_h
#define gEngine_INode_h

#include "CVector.h"
#include "CMatrix.h"
#include "CQuaternion.h"
#include "CTexture.h"
#include "CShader.h"
#include "CVertexBuffer.h"
#include "CMesh.h"

#include "CShaderComposite.h"
#include "CCamera.h"
#include "CResourceMgr.h"
#include "CMeshComposite.h"

class INode
{
public:
    struct SIntersectorID
    {
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    };
protected:
    Matrix4x4   m_mScale;
    Matrix4x4   m_mRotation;
    Matrix4x4   m_mTranslation;
    Matrix4x4   m_mWorld;
    
    CShader*    m_pShader;
    CTexture**  m_pTextures;
    CMesh*      m_pMesh;
    Vector4d    m_vColor;
    
    Vector3d    m_vScale;
    Vector3d    m_vPosition;
    Vector3d    m_vRotation;
    
    SIntersectorID   m_tIntersectorID;
    CShader*         m_pIntersectorShader;
    bool             m_bIntersected;
    IResource::E_INTERSECTOR m_eIntersector;
    
    bool m_bBatch;
public:
    INode();
    virtual ~INode();
    virtual void Load(IResource::SResource _pReosurce) = 0;
    virtual void Intersect(bool _bItersected) = 0;
    virtual void Update(float _fTime);
    virtual void Render() = 0;
    
    CShader* Get_Shader() const;
    inline CTexture** Get_Textures() const { return m_pTextures; }
    inline CMesh* Get_Mesh() const { return m_pMesh; }
    
    inline void Set_Position(Vector3d _vPosition) { m_vPosition = _vPosition; }
    Vector3d Get_Position();
    inline void Set_Rotation(Vector3d _vRotation) { m_vRotation = _vRotation; }
    Vector3d Get_Rotation();
    inline void Set_Scale(Vector3d _vScale) { m_vScale = _vScale; }
    Vector3d Get_Scale();
    void Set_IntersectorID(SIntersectorID _tIntersectorID);
    inline SIntersectorID Get_IntersectorID() { return m_tIntersectorID; }
    inline bool Get_Itersected() { return m_bIntersected; }
    inline Matrix4x4 Get_WorldMatrix() { return m_mWorld; }
};

#endif










