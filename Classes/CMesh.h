//
//  CMesh.h
//  gEngine
//
//  Created by sergey.sergeev on 11/28/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CMesh_h
#define gEngine_CMesh_h

#include "CVector.h"
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include "IResource.h"
#include "CSkeleton.h"
#include <vector>

#define MAX_BONE_WEIGHTS 8

class CMesh : public IResource
{   
public:
    struct SBoneWeight
    {
        float m_fWeight;
        int   m_iBoneID;
    };

    struct SVertex 
    {
        CVector3d    m_vPosition;
        CVector2d    m_vTexCoord;
        CVector3d    m_vNormal;
        CVector3d    m_vTangent;
        int         m_iNumBones;
        SBoneWeight m_tBoneWeights[MAX_BONE_WEIGHTS];
    };
    
    struct SSource
    {
        SVertex*        m_pData;
        CVertexBuffer*  m_pVB;
        CIndexBuffer*   m_pIB;
        int             m_iNumVertexes;
        int             m_iNumIndexes;
        CVector3d       m_vMaxBound;
        CVector3d       m_vMinBound;
    }; 
protected:
    SSource* m_pSource;
public:
    CMesh();
    ~CMesh();
    CVertexBuffer*  Get_VB(void) { return m_pSource->m_pVB; }
    CIndexBuffer*   Get_IB(void) { return m_pSource->m_pIB; }
    virtual void Set_Source(void* _pSource);
    int Get_NumIndexes() { return m_pSource->m_iNumIndexes; }
    int Get_NumVertexes() { return m_pSource->m_iNumVertexes; }
    CVector3d Get_MaxBound(void) { return m_pSource->m_vMaxBound; }
    CVector3d Get_MinBound(void) { return m_pSource->m_vMinBound; }
};

#endif
