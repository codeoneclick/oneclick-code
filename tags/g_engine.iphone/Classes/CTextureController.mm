//
//  CTextureController.cpp
//  gEngine
//
//  Created by Snow Leopard User on 24/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CTextureController.h"
#include <cmath>
#include "stdlib.h"
#include <algorithm>

CTextureController::CTextureController()
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

CTextureController::~CTextureController()
{
    
}

CTexture* CTextureController::Texture(std::string _sName)
{
    CTexture* pTexture = new CTexture();
    Load(_sName, pTexture);
    Commit(pTexture);
    m_container[_sName] = pTexture;
    return pTexture;
}

void CTextureController::Load(std::string _sName, CTexture* pTexture)
{
    NSString* sName = [NSString stringWithUTF8String:_sName.c_str()];
    NSString* sPath = [[NSBundle mainBundle] resourcePath];
    sPath = [sPath stringByAppendingPathComponent:sName];
    NSLog(@"[Texture controller] Texture load :%@",sPath);
    
    NSData* source = [NSData dataWithContentsOfFile:sPath];
    PVR_Texture_Header* header = (PVR_Texture_Header*) [source bytes];
    bool alpha = header->dwAlphaBitMask ? true : false;
    
    CTexture::SDescription description;
    switch (header->dwpfFlags & PVRTEX_PIXELTYPE) 
    {
        case OGL_RGB_565:
            description.s_format = CTexture::TextureFormat565;
            break;
        case OGL_RGBA_5551:
            description.s_format = CTexture::TextureFormat5551;
            break;
        case OGL_RGBA_4444:
            description.s_format = CTexture::TextureFormatRgba;
            description.s_bpp = 4;
            break;
        case OGL_PVRTC2:    
            description.s_format = alpha ? CTexture::TextureFormatPvrtcRgba2 : CTexture::TextureFormatPvrtcRgb2;
            break;
        case OGL_PVRTC4:
            description.s_format = alpha ? CTexture::TextureFormatPvrtcRgba4 : CTexture::TextureFormatPvrtcRgb4;
            break;
        default:
            NSLog(@"[Texture controller] Unsupported format :%@",sPath);
            break;
    }
    description.s_size.x = header->dwWidth;
    description.s_size.y = header->dwHeight;
    description.s_mip = header->dwMipMapCount;
    
    char* data = (char*) [source bytes];
    unsigned int offset = header->dwHeaderSize;
    data += offset;
    
    pTexture->Set_Description(description);
    pTexture->Set_Data(data);
}

void CTextureController::Commit(CTexture *pTexture)
{
    CTexture::SDescription description = pTexture->Get_Description();
    int glWidth = description.s_size.x;
    int glHeight = description.s_size.y;
    GLenum glFormat;
    bool compressed = true;
    
    GLuint textureId = -1;
    glGenTextures( 1, &textureId );
    glBindTexture( GL_TEXTURE_2D, textureId );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    
    switch (description.s_format) 
    {
        case CTexture::TextureFormatPvrtcRgba2:
        {
            description.s_bpp = 2;
            glFormat = GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG;
        }
            break;
        case CTexture::TextureFormatPvrtcRgb2:
        {
            description.s_bpp = 2;
            glFormat = GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG;
        }
            break;
        case CTexture::TextureFormatPvrtcRgba4:
        {
            description.s_bpp = 4;
            glFormat = GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG;
        }
            break;
        case CTexture::TextureFormatPvrtcRgb4:
        {
            description.s_bpp = 4;
            glFormat = GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG;
        }
            break;
        default:
        {
            compressed = false;
        }
            break;
    }
    
    char* data = pTexture->Get_Data();
    
    if (compressed) 
    {
        for (unsigned int level = 0; level < description.s_mip; ++level) 
        {
            GLsizei size = std::max(32, glWidth * glHeight * description.s_bpp / 8);
            glCompressedTexImage2D(GL_TEXTURE_2D, level, glFormat, glWidth, glHeight, 0, size, data);
            data += size;
            glWidth >>= 1; glHeight >>= 1;
        }
    } 
    else 
    {
        GLenum glType;
        switch (description.s_format) 
        {
            case CTexture::TextureFormatRgba: 
            {
                glFormat = GL_RGBA;
                glType = GL_UNSIGNED_SHORT_4_4_4_4;
                description.s_bpp = 16;
            }
                break;
            case CTexture::TextureFormat565:
            {
                glFormat = GL_RGB;
                glType = GL_UNSIGNED_SHORT_5_6_5;
                description.s_bpp = 16;
            }
                break;
            case CTexture::TextureFormat5551:
            {
                glFormat = GL_RGBA;
                glType = GL_UNSIGNED_SHORT_5_5_5_1;
                description.s_bpp = 16;
            }
                break;
            default:
            {
            }
                break;
        }
        for (int level = 0; level < description.s_mip; ++level)
        {
            GLsizei size = glWidth * glHeight * description.s_bpp / 8;
            glTexImage2D(GL_TEXTURE_2D, level, glFormat, glWidth, glHeight, 0, glFormat, glType, data);
            data += size;
            glWidth >>= 1; glHeight >>= 1;
        }
    }
    
    pTexture->Set_Handle(textureId);
}



