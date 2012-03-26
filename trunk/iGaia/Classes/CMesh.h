//
//  CMesh.h
//  iGaia
//
//  Created by sergey.sergeev on 11/28/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CMesh_h
#define iGaia_CMesh_h

#include "CVertexBuffer.h"
#include "CIndexBuffer.h"
#include "IResource.h"
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
        glm::vec3    m_vPosition;
        glm::vec2    m_vTexCoord;
        glm::vec3    m_vNormal;
        glm::vec3    m_vTangent;
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
        glm::vec3       m_vMaxBound;
        glm::vec3       m_vMinBound;
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
    glm::vec3 Get_MaxBound(void) { return m_pSource->m_vMaxBound; }
    glm::vec3 Get_MinBound(void) { return m_pSource->m_vMinBound; }
};

#endif
