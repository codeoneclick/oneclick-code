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
#include <string.h>

class CVertexBuffer
{
public:

    struct SVertex 
    {
        Vector3d m_vPosition;
        Vector2d m_vTexCoord;
        Vector3d m_vNormal;
        Vector3d m_vTangent;
        Vector4d m_vColor;
    };
    
    static const std::string k_VERTEX_SLOT;
    static const std::string k_TEXCOORD_SLOT;
    static const std::string k_NORMAL_SLOT;
    static const std::string k_TANGENT_SLOT;
    static const std::string k_COLOR_SLOT;
    
private:
    void *m_pData;
    GLuint m_hVBHandle;
    unsigned int m_iNumVertexes;
    unsigned int m_iStride;
    bool m_bVRAM;
public:
    CVertexBuffer(unsigned int _iNumVertexes,unsigned char _iVertexSize);
    ~CVertexBuffer();
    
    inline void *Get_Data() { return m_pData; }
    void Enable(GLuint _hShaderHandle);
    void Disable(GLuint _hShaderHandle);
    void Commit();
};

#endif
