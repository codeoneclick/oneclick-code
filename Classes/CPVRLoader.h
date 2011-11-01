//
//  CPVRLoader.h
//  gEngine
//
//  Created by sergey.sergeev on 10/31/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CPVRLoader_h
#define gEngine_CPVRLoader_h

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include "PVRTTexture.h"
#include "CVector.h"
#include "CTexture.h"

class CPVRLoader
{
protected:
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
    
    struct SPVRData
    {
        char* s_data;
        SDescription s_description;
        GLuint s_hanlde;
        PVR_Texture_Header* s_header;
    };
private:
    void Commit(SPVRData* _data);
public:
    CPVRLoader();
    ~CPVRLoader();
    CTexture* Load(const char* _sName);
};

#endif
