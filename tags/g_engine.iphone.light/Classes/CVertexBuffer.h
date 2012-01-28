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
    };
    
    static const std::string k_VERTEX_SLOT;
    static const std::string k_TEXCOORD_SLOT;
    static const std::string k_NORMAL_SLOT;
    unsigned int m_iCount;
private:
    void *m_pData;
    GLuint m_handle;
    unsigned int m_count;
    unsigned int m_stride;
    bool m_vram;
public:
    CVertexBuffer(unsigned int _vertexCount,unsigned char _elementSize);
    ~CVertexBuffer();
    
    inline void *Get_Data() { return m_pData; }
    void Enable(GLuint _handle);
    void Disable(GLuint _handle);
    void Commit();
    unsigned int Get_Count() { return m_iCount; }
};

#endif
