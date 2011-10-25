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
    
private:
    
public:
    CTexture();
    ~CTexture();
    char* m_data;
    SDescription m_description;
};

#endif
