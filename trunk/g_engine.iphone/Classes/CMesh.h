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
        Vector3d    m_vPosition;
        Vector2d    m_vTexCoord;
        Vector3d    m_vNormal;
        Vector3d    m_vTangent;
        int         m_iNumBones;
        SBoneWeight m_tBoneWeights[MAX_BONE_WEIGHTS];
    };
    
    struct SSource
    {
        SVertex*        m_pData;
        CVertexBuffer*  m_pVB;
        unsigned short* m_pIB;
        CSkeleton*      m_pSkeleton;
        int             m_iNumVertexes;
        int             m_iNumIndexes;
        std::vector<SVertex*> m_pSequence;
    }; 
protected:
    SSource* m_pSource;
public:
    CMesh();
    ~CMesh();
    inline CVertexBuffer*  Get_VB() { return m_pSource->m_pVB; }
    inline unsigned short* Get_IB() { return m_pSource->m_pIB; }
    virtual void Set_Source(void* _pSource);
    inline int Get_NumIndexes() { return m_pSource->m_iNumIndexes; }
    inline int Get_NumVertexes() { return m_pSource->m_iNumVertexes; }
    inline unsigned int   Get_FramesCount() { return m_pSource->m_pSequence.size(); }
    inline std::vector<SVertex*> Get_Sequence() { return m_pSource->m_pSequence; }
};

#endif
