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
    m_pSource = NULL;
    m_pData = NULL;
}

CPVRLoader::~CPVRLoader()
{
    if(m_pData != NULL)
    {
        delete m_pData;
        m_pData = NULL;
    }
}

void CPVRLoader::Load(const char *_sName)
{
    m_eStatus = E_STATUS_START;
    NSString* sName = [NSString stringWithUTF8String:_sName];
    NSString* sPath = [[NSBundle mainBundle] resourcePath];
    sPath = [sPath stringByAppendingPathComponent:sName];
    NSData* pData = [NSData dataWithContentsOfFile:sPath];
    
    if(pData == nil)
    {
        NSLog(@"[Texture controller] Texture does not load :%@",sPath);
        m_eStatus = E_STATUS_ERROR;
        return;
    }
    
    NSLog(@"[Texture controller] Texture load :%@",sPath);
    

    m_pDescription = new SDescription();
    m_pHeader = (PVR_Texture_Header*) [pData bytes];
    m_pData = (char*)[pData bytes];
    
    switch (m_pHeader->dwpfFlags & PVRTEX_PIXELTYPE) 
    {
        case OGL_RGB_565:
            m_pDescription->m_eFormat = CPVRLoader::TextureFormat565;
            break;
        case OGL_RGBA_5551:
            m_pDescription->m_eFormat = CPVRLoader::TextureFormat5551;
            break;
        case OGL_RGBA_4444:
            m_pDescription->m_eFormat = CPVRLoader::TextureFormatRgba;
            m_pDescription->m_uiBPP = 4;
            break;
        case OGL_PVRTC2:    
            m_pDescription->m_eFormat = m_pHeader->dwAlphaBitMask ? CPVRLoader::TextureFormatPvrtcRgba2 : CPVRLoader::TextureFormatPvrtcRgb2;
            break;
        case OGL_PVRTC4:
            m_pDescription->m_eFormat = m_pHeader->dwAlphaBitMask ? CPVRLoader::TextureFormatPvrtcRgba4 : CPVRLoader::TextureFormatPvrtcRgb4;
            break;
        default:
            NSLog(@"[Texture controller] Unsupported format :%@",sPath);
            m_eStatus = E_STATUS_ERROR;
            return;
            break;
    }
    
    m_pDescription->m_vSize.x = m_pHeader->dwWidth;
    m_pDescription->m_vSize.y = m_pHeader->dwHeight;
    m_pDescription->m_uiMIP = m_pHeader->dwMipMapCount ? m_pHeader->dwMipMapCount : 1;
    m_pDescription->m_bCompressed = true;
    
    switch (m_pDescription->m_eFormat) 
    {
        case CPVRLoader::TextureFormatPvrtcRgba2:
            m_pDescription->m_uiBPP = 2;
            m_pDescription->m_glFormat = GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG;
            break;
        case CPVRLoader::TextureFormatPvrtcRgb2:
            m_pDescription->m_uiBPP = 2;
            m_pDescription->m_glFormat = GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG;
            break;
        case CPVRLoader::TextureFormatPvrtcRgba4:
            m_pDescription->m_uiBPP = 4;
            m_pDescription->m_glFormat = GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG;
            break;
        case CPVRLoader::TextureFormatPvrtcRgb4:
            m_pDescription->m_uiBPP = 4;
            m_pDescription->m_glFormat = GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG;
            break;
        default:
            m_pDescription->m_bCompressed = false;
            break;
    }
    
    if(!m_pDescription->m_bCompressed)
    {
        switch (m_pDescription->m_eFormat) 
        {
            case CPVRLoader::TextureFormatRgba: 
                m_pDescription->m_glFormat = GL_RGBA;
                m_pDescription->m_glType = GL_UNSIGNED_SHORT_4_4_4_4;
                m_pDescription->m_uiBPP = 16;
                break;
            case CPVRLoader::TextureFormat565:
                m_pDescription->m_glFormat = GL_RGB;
                m_pDescription->m_glType = GL_UNSIGNED_SHORT_5_6_5;
                m_pDescription->m_uiBPP = 16;
                break;
            case CPVRLoader::TextureFormat5551:
                m_pDescription->m_glFormat = GL_RGBA;
                m_pDescription->m_glType = GL_UNSIGNED_SHORT_5_5_5_1;
                m_pDescription->m_uiBPP = 16;
                break;
            default:
                break;
        }
    }
    m_eStatus = E_STATUS_DONE;
}

void CPVRLoader::Commit()
{
    int uiWidth  = m_pDescription->m_vSize.x;
    int uiHeight = m_pDescription->m_vSize.y;
    char* pData = m_pData + m_pHeader->dwHeaderSize;
    
    m_pSource = new CTexture::SSource();
    m_pSource->m_uiWidth  = m_pDescription->m_vSize.x;
    m_pSource->m_uiHeight = m_pDescription->m_vSize.y;
    
    glGenTextures( 1, &m_pSource->m_uiHanlde );
    glBindTexture( GL_TEXTURE_2D, m_pSource->m_uiHanlde );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    
    if (m_pDescription->m_bCompressed) 
    {
        for (unsigned int level = 0; level < m_pDescription->m_uiMIP; ++level) 
        {
            GLsizei size = std::max(32, uiWidth * uiHeight * m_pDescription->m_uiBPP / 8);
            glCompressedTexImage2D(GL_TEXTURE_2D, level, m_pDescription->m_glFormat, uiWidth, uiHeight, 0, size, pData);
            pData += size;
            uiWidth >>= 1; uiHeight >>= 1;
        }
    } 
    else
    {       
        for (int level = 0; level < m_pDescription->m_uiMIP; ++level)
        {
            GLsizei size = uiWidth * uiHeight * m_pDescription->m_uiBPP / 8;
            glTexImage2D(GL_TEXTURE_2D, level, m_pDescription->m_glFormat, uiWidth, uiHeight, 0, m_pDescription->m_glFormat, m_pDescription->m_glType, pData);
            pData += size;
            uiWidth >>= 1; uiHeight >>= 1;
        }
    }
}


