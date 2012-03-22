//
//  ICollider.h
//  gEngine
//
//  Created by sergey.sergeev on 1/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_ICollider_h
#define gEngine_ICollider_h

#include "CVector.h"
#include "CMatrix.h"
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include "CMesh.h"
#include "CShader.h"

class ICollider
{
/*public:
    struct SColliderID
    {
        unsigned int m_iHex;
        union 
        {
            struct 
            {
                unsigned char r;
                unsigned char g;
                unsigned char b;
            };
            unsigned char v[3];
        };
    };
protected:
    CVector3d m_vMax;
    CVector3d m_vMin;
    CMatrix4x4 m_mWorld;
    CShader* m_pShader;
    CMesh* m_pMesh;
    SColliderID m_tColliderID;
    bool m_bIsBatching;
    bool m_bIsTouchCollided;
public:
    ICollider();
    virtual ~ICollider();
    
    void Set_WorldMatrix(const CMatrix4x4 &_mWorld) { m_mWorld = _mWorld; }
    CMatrix4x4 Get_WorldMatrix(void) { return m_mWorld; }
    void Set_MaxMinPoints(const CVector3d &_vMax, const CVector3d &_vMin) { m_vMax = _vMax; m_vMin = _vMin; }
    void Set_ColliredID(SColliderID _tColliderID);
    SColliderID Get_ColliderID(void) { return m_tColliderID; }
    CMesh* Get_Mesh(void) { return m_pMesh; }
    void Set_Batching(bool _bValue) { m_bIsBatching = _bValue; }
    
    void Set_TouchCollided(bool _bIsTouchCollided) { m_bIsTouchCollided = _bIsTouchCollided; }
    bool Get_TouchCollided(void) { return m_bIsTouchCollided; }
    
    virtual void Render(void) = 0;*/
};


#endif
