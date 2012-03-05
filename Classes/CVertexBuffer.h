//
//  CVertexBuffer.h
//  gEngine
//
//  Created by sergey.sergeev on 10/19/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CVertexBuffer_h
#define gEngine_CVertexBuffer_h

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include "CVector.h"
#include <stdlib.h>

class CVertexBuffer
{
public:
    enum E_VERTEX_BUFFER_MODE { E_VERTEX_BUFFER_MODE_VTN = 0, E_VERTEX_BUFFER_MODE_VC, E_VERTEX_BUFFER_MODE_VNC };
        
    struct SVertexVTN
    {
        CVector3d m_vPosition; 
        CVector2d m_vTexCoord; 
        CVector3d m_vNormal;   
    };
    
    struct SVertexVNC
    {
        CVector3d m_vPosition;
        CVector3d m_vNormal;
        CColor4 m_cColor;
        char padding[4];
    };
    
    struct SVertexVC
    {
        CVector3d m_vPosition; 
        CColor4 m_cColor;
        char padding[16];
    };
    
    static const std::string k_SLOT_POSITION;
    static const std::string k_SLOT_TEXCOORD;
    static const std::string k_SLOT_NORMAL;
    static const std::string k_SLOT_COLOR;
    
private:
    void *m_pData;
    GLuint m_iHandle;
    GLuint m_iShaderHandle;
    unsigned int m_iNumVertexes;
    unsigned int m_iSize;
    bool m_bIsInVRAM;
    E_VERTEX_BUFFER_MODE m_eMode;
    
    GLint m_iPositionSlot;
    GLint m_iTexcoordSlot;
    GLint m_iNormalSlot;
    GLint m_iColorSlot;

public:
    CVertexBuffer(unsigned int _iNumVertexes,unsigned char _iVertexSize, E_VERTEX_BUFFER_MODE _eMode);
    ~CVertexBuffer();
    
    unsigned int Get_NumVertexes(void) { return  m_iNumVertexes; }
    void *Get_Data() { return m_pData; }
    void Set_ShaderRef(GLuint _iShaderHandler);
    GLuint Get_ShaderRef(void) { return m_iShaderHandle; }
    void Enable();
    void Disable();
    void Commit();
};

#endif
