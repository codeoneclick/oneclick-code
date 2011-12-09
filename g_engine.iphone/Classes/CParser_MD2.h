//
//  CParser_MD2.h
//  gEngine
//
//  Created by sergey.sergeev on 11/29/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CParser_MD2_h
#define gEngine_CParser_MD2_h

#include "stdlib.h"
#include <string>
#include "CVector.h"
#include "CMesh.h"
#include "IParser.h"
#include <algorithm>

class CParser_MD2 : public IParser
{
private:
    struct SMD2_Header
	{
        int ident;
        int version;
        int skinwidth;			
        int skinheight;	
        int framesize;
        int num_skins;			
        int num_xyz;			
        int num_st;
        int num_tris;	
        int num_glcmds;
        int num_frames;			
        int ofs_skins;
        int ofs_st;
        int ofs_tris;
        int ofs_frames;
        int ofs_glcmds; 
        int ofs_end;
	};
    
    struct SMD2_VT
    {
        short x;
        short y;
    };
    
    struct SMD2_VertexRef_01
    {
        short pPositionRef[3];
        short pTexcoordRef[3];
    };
    
    struct SMD2_VertexRef_02
	{
		unsigned char pV[3];
		unsigned char pI;
	};
    
    struct SMD2_Frame
	{
		Vector3d vScale;
		Vector3d vPosition;
		char sName[16];
		SMD2_VertexRef_02 pVertexRef[1];
	};
    
    struct SMD2_VertexList
    {
        float x,y,z;  
    };
    
    struct SMD2_IndexList
    {
        int a, b, c;
        float a_s, a_t,b_s, b_t,c_s, c_t;
    };
    
    struct SMD2_FrameList
    {
        SMD2_VertexList *pV;  
    };
    
private:
    CMesh::SSource* m_pSource;
    char*           m_pData;
public:
    CParser_MD2();
    ~CParser_MD2();
    
    virtual void  Load(const std::string& _sName);
    virtual void* Get_Source() { return m_pSource; }
    virtual void  Commit();
};

#endif
