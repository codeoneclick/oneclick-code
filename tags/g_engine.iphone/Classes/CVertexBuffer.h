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
    enum VB_DECLARATION { VBD_V2FC4F = 0, VBD_V2T2, VBD_V2FT2FC4F };
    
    struct SVertexVC
    {
        Vector3d s_position;
        Vector4d s_color;
    };
    
    struct SVertexVT
    {
        Vector3d s_position;
        Vector2d s_texcoord;
    };
    
    struct SVertexVTC
    {
        Vector3d s_position;
        Vector2d s_texcoord;
        Vector4d s_color;
    };
    
    static const std::string k_VERTEX_SLOT;
    static const std::string k_TEXCOORD_SLOT;
    static const std::string k_COLOR_SLOT;
private:
    void *m_pData;
    VB_DECLARATION m_declaration;
    GLuint m_handle;
    unsigned int m_count;
    unsigned int m_stride;
    bool m_vram;
public:
    CVertexBuffer(unsigned int _vertexCount,unsigned char _elementSize, VB_DECLARATION _declaration);
    ~CVertexBuffer();
    
    inline VB_DECLARATION Declaration() { return m_declaration; }
    inline void *Data() { return m_pData; }
    void Enable(GLuint _handle);
    void Disable(GLuint _handle);
    void Commit();
    inline bool Vram() { return m_vram; }
};

#endif
