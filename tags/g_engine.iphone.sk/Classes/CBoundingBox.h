//
//  CBoundingBox.h
//  gEngine
//
//  Created by sergey.sergeev on 1/4/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CBoundingBox_h
#define gEngine_CBoundingBox_h
#include "CVector.h"
#include "CMatrix.h"
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include "CMesh.h"
#include "CShader.h"

class CBoundingBox
{
protected:
    CVector3d m_vMax;
    CVector3d m_vMin;
    CMatrix4x4 m_mWorld;
    CShader* m_pShader;
    CMesh* m_pMesh;
    bool m_bIsBatching;
public:
    static const float k_MAX_VALUE;
    static const float k_MIN_VALUE;
    
    CBoundingBox(const CVector3d &_vMax, const CVector3d &_vMin);
    ~CBoundingBox();
    
    void Set_WorldMatrix(const CMatrix4x4 &_mWorld) { m_mWorld = _mWorld; }
    CMatrix4x4 Get_WorldMatrix(void) { return m_mWorld; }
    CMesh* Get_Mesh(void) { return m_pMesh; }
    void Set_MaxMinPoints(const CVector3d &_vMax, const CVector3d &_vMin) { m_vMax = _vMax; m_vMin = _vMin; }
    void Set_Batching(bool _bValue) { m_bIsBatching = _bValue; }
    
    void Render(void);
};

#endif
