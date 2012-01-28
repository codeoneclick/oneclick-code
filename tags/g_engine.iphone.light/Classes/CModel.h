//
//  CMesh.h
//  gEngine
//
//  Created by sergey.sergeev on 11/17/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CMesh_h
#define gEngine_CMesh_h

#include "CMatrix.h"
#include "CParser_M3.h"
#include "CTexture.h"
#include "CShader.h"
#include "CVertexBuffer.h"


class CModel
{
protected:
    Matrix4x4 m_mScale;
    Matrix4x4 m_mRotation;
    Matrix4x4 m_mTranslation;
    Matrix4x4 m_mWorld;
    Matrix4x4 m_mMVP;
    Matrix4x4 m_mMVP_INV;
    
    Matrix4x4* m_mProjection;
    Matrix4x4* m_mView;
    
    CShader*        m_pShader;
    CTexture**      m_pTextures;
    CVertexBuffer*  m_pVb;
    unsigned short* m_pIb;
    
    CVertexBuffer** m_pCompositeVB;
    unsigned short** m_pCompositeIB;
    unsigned int* m_pCompositeIBCount;
    
    unsigned int m_indexCount;
    
    unsigned int m_iEffectIndex;
    unsigned int m_iModelIndex;
    
    void UpdateEffect();
    void UpdateModel();
public:
    Vector3d     m_vScale;
    Vector3d     m_vPosition;
    Vector3d     m_vRotation;
    
    CModel();
    ~CModel();
    void Load(std::string _sName);
    void Update(float _fTime);
    void Render();
    void Set_Effect(unsigned int _iIndex);
    void Set_Model(unsigned int _iIndex);
};

#endif
