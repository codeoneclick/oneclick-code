//
//  CTexture.h
//  gEngine
//
//  Created by Snow Leopard User on 25/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CTexture_h
#define gEngine_CTexture_h

#include "CVector.h"
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include "PVRTTexture.h"

class CTexture
{
public:
    enum TextureFormat 
    {
        TextureFormatGray,
        TextureFormatGrayAlpha,
        TextureFormatRgb,
        TextureFormatRgba,
        TextureFormatPvrtcRgb2,
        TextureFormatPvrtcRgba2,
        TextureFormatPvrtcRgb4,
        TextureFormatPvrtcRgba4,
        TextureFormat565,
        TextureFormat5551,
    };
    
    struct SDescription
    {
        TextureFormat s_format;
        int s_bpp;
        Vector2d s_size;
        int s_mip;
    };
    
protected:
    char* m_data;
    SDescription m_description;
    GLuint m_id;
    PVR_Texture_Header* m_header;
public:
    CTexture();
    ~CTexture();
    inline char* Get_Data() { return m_data; }
    inline void  Set_Data(char* _data) { m_data = _data; }
    inline SDescription Get_Description() { return m_description; }
    inline void  Set_Description(SDescription _description) { m_description = _description; }
    inline PVR_Texture_Header* Get_Header() { return m_header; }
    inline void  Set_Header(PVR_Texture_Header* _header) { m_header = _header; }
    inline GLuint Get_Handle() { return m_id; }
    inline void   Set_Handle(GLuint _handle) { m_id = _handle; }
};

#endif
