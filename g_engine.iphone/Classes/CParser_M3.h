//
//  CParser_M3.h
//  gEngine
//
//  Created by sergey.sergeev on 11/17/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CParser_M3_h
#define gEngine_CParser_M3_h

#include "stdlib.h"
#include <string>
#include "CVector.h"
#include "CMesh.h"
#include "IParser.h"

class CParser_M3 : public IParser
{
private:
    CMesh::SSource* m_pSource;
    char*           m_pData;
protected:
    
    enum E_M3_VERSION { E_M3_01 = 0, E_M3_02, E_M3_03, E_M3_UNKNOWN };
    
    struct SM3_Header
    {
        char m_pId[4];
        unsigned int m_iTagsOffset;
        unsigned int m_iTagsCount;
        unsigned int unknown_01;
        unsigned int unknown_02;
    };
    
    struct SM3_Tag 
    {
        char m_pName[4];
        unsigned int m_iBlockOffset;
        unsigned int m_iBlockSize;
        unsigned int n_iVersion;
    };
    
    struct SM3_TagReference
    {
        unsigned int m_iEntries;
        unsigned int m_iReference;
    };
    
    struct SM3_Region 
    {
        unsigned short m_iVertexOffset;
        unsigned short m_iVertexCount;
        unsigned int   m_iIndexOffset;
        unsigned int   m_iIndexCount; 
    };
    
    struct SM3_IndexBlock
    {
        SM3_TagReference m_pFaces; 
        SM3_TagReference m_Regions; 
        SM3_TagReference unknown_01;
        SM3_TagReference unknown_02;
    };
        
    struct SM3I_VertexBlock
    {
        Vector3d m_vPosition;
        unsigned char  m_iBoneWeight[4];
        unsigned char  m_iBoneIndex[4];
        unsigned char  m_iNormal[4];
        unsigned short m_iTexCoord[2];
    };
    
    struct SM3_VertexBlock_01 : public SM3I_VertexBlock
    {
        unsigned int   unknown_01;
        unsigned char  m_iTangent[4];
    };
    
    struct SM3_VertexBlock_02 : public SM3I_VertexBlock
    {
        unsigned char  m_iTangent[4];
    };
    
    struct SM3_VertexBlock_03 : public SM3I_VertexBlock
    {
        unsigned char  unknown_01[10];
    };
    
public:
    CParser_M3();
    ~CParser_M3();
    virtual void  Load(const std::string& _sName);
    virtual void* Get_Source() { return m_pSource; }
    virtual void  Commit();
};


#endif
