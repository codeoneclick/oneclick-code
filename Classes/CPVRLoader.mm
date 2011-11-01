//
//  CPVRLoader.cpp
//  gEngine
//
//  Created by sergey.sergeev on 10/31/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CPVRLoader.h"

CPVRLoader::CPVRLoader()
{
    
}

CPVRLoader::~CPVRLoader()
{
    
}

CTexture* CPVRLoader::Load(const char* _sName)
{
    NSString* sName = [NSString stringWithUTF8String:_sName];
    NSString* sPath = [[NSBundle mainBundle] resourcePath];
    sPath = [sPath stringByAppendingPathComponent:sName];
    NSLog(@"[Texture controller] Texture load :%@",sPath);
    
    CPVRLoader::SPVRData* pvrData = new CPVRLoader::SPVRData();
    
    NSData* source = [NSData dataWithContentsOfFile:sPath];
    pvrData->s_header = (PVR_Texture_Header*) [source bytes];
    bool alpha = pvrData->s_header->dwAlphaBitMask ? true : false;
    
    switch (pvrData->s_header->dwpfFlags & PVRTEX_PIXELTYPE) 
    {
        case OGL_RGB_565:
            pvrData->s_description.s_format = CPVRLoader::TextureFormat565;
            break;
        case OGL_RGBA_5551:
            pvrData->s_description.s_format = CPVRLoader::TextureFormat5551;
            break;
        case OGL_RGBA_4444:
            pvrData->s_description.s_format = CPVRLoader::TextureFormatRgba;
            pvrData->s_description.s_bpp = 4;
            break;
        case OGL_PVRTC2:    
            pvrData->s_description.s_format = alpha ? CPVRLoader::TextureFormatPvrtcRgba2 : CPVRLoader::TextureFormatPvrtcRgb2;
            break;
        case OGL_PVRTC4:
            pvrData->s_description.s_format = alpha ? CPVRLoader::TextureFormatPvrtcRgba4 : CPVRLoader::TextureFormatPvrtcRgb4;
            break;
        default:
            NSLog(@"[Texture controller] Unsupported format :%@",sPath);
            break;
    }
    pvrData->s_description.s_size.x = pvrData->s_header->dwWidth;
    pvrData->s_description.s_size.y = pvrData->s_header->dwHeight;
    pvrData->s_description.s_mip = pvrData->s_header->dwMipMapCount ? pvrData->s_header->dwMipMapCount : 1;
    
    pvrData->s_data = (char*) [source bytes];
    unsigned int offset = pvrData->s_header->dwHeaderSize;
    pvrData->s_data += offset;
    
    Commit(pvrData);
    
    delete (char*)[source bytes];
    pvrData->s_data = NULL;

    CTexture* pTexture = new CTexture();
    pTexture->Set_Handle(pvrData->s_hanlde);
    pTexture->Set_Width(pvrData->s_description.s_size.x);
    pTexture->Set_Height(pvrData->s_description.s_size.y);
    
    return pTexture;
}

void CPVRLoader::Commit(CPVRLoader::SPVRData *_data)
{
    int glWidth = _data->s_description.s_size.x;
    int glHeight = _data->s_description.s_size.y;
    GLenum glFormat;
    bool compressed = true;
    
    GLuint handle = -1;
    glGenTextures( 1, &handle );
    glBindTexture( GL_TEXTURE_2D, handle );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    
    switch (_data->s_description.s_format) 
    {
        case CPVRLoader::TextureFormatPvrtcRgba2:
        {
            _data->s_description.s_bpp = 2;
            glFormat = GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG;
        }
            break;
        case CPVRLoader::TextureFormatPvrtcRgb2:
        {
            _data->s_description.s_bpp = 2;
            glFormat = GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG;
        }
            break;
        case CPVRLoader::TextureFormatPvrtcRgba4:
        {
            _data->s_description.s_bpp = 4;
            glFormat = GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG;
        }
            break;
        case CPVRLoader::TextureFormatPvrtcRgb4:
        {
            _data->s_description.s_bpp = 4;
            glFormat = GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG;
        }
            break;
        default:
        {
            compressed = false;
        }
            break;
    }
    
    if (compressed) 
    {
        for (unsigned int level = 0; level < _data->s_description.s_mip; ++level) 
        {
            GLsizei size = std::max(32, glWidth * glHeight * _data->s_description.s_bpp / 8);
            glCompressedTexImage2D(GL_TEXTURE_2D, level, glFormat, glWidth, glHeight, 0, size, _data->s_data);
            _data->s_data += size;
            glWidth >>= 1; glHeight >>= 1;
        }
    } 
    else
    {
        GLenum glType;
        switch (_data->s_description.s_format) 
        {
            case CPVRLoader::TextureFormatRgba: 
            {
                glFormat = GL_RGBA;
                glType = GL_UNSIGNED_SHORT_4_4_4_4;
                _data->s_description.s_bpp = 16;
            }
                break;
            case CPVRLoader::TextureFormat565:
            {
                glFormat = GL_RGB;
                glType = GL_UNSIGNED_SHORT_5_6_5;
                _data->s_description.s_bpp = 16;
            }
                break;
            case CPVRLoader::TextureFormat5551:
            {
                glFormat = GL_RGBA;
                glType = GL_UNSIGNED_SHORT_5_5_5_1;
                _data->s_description.s_bpp = 16;
            }
                break;
            default:
            {
            }
                break;
        }
        
        for (int level = 0; level < _data->s_description.s_mip; ++level)
        {
            GLsizei size = glWidth * glHeight * _data->s_description.s_bpp / 8;
            glTexImage2D(GL_TEXTURE_2D, level, glFormat, glWidth, glHeight, 0, glFormat, glType, _data->s_data);
            _data->s_data += size;
            glWidth >>= 1; glHeight >>= 1;
        }
    }
    _data->s_hanlde = handle;
}











