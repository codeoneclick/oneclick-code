//
//  CPVRLoader.cpp
//  gEngine
//
//  Created by sergey.sergeev on 10/31/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CParser_PVR.h"
#include <fstream>
#include <strstream>
#include "CCommon_IOS.h"

CParser_PVR::CParser_PVR()
{
    m_pSource = NULL;
    m_pData = NULL;
}

CParser_PVR::~CParser_PVR()
{
    if(m_pData != NULL)
    {
        delete m_pData;
        m_pData = NULL;
    }
}

void CParser_PVR::Load(const std::string& _sName)
{
    m_eStatus = E_START_STATUS;
    
    std::string sFileName = Get_ResourceFileName(_sName); 
    std::ifstream pStream;
    pStream.open(sFileName.c_str(), std::ios::binary);
    pStream.seekg( 0, std::ios::end );
    int iLength = pStream.tellg();
    pStream.seekg( 0, std::ios::beg );
    m_pData = new char[iLength];
    pStream.read( m_pData,iLength );
    pStream.close();
    

    m_pDescription = new SDescription();
    m_pHeader = (PVR_Texture_Header*)m_pData;
    
    switch (m_pHeader->dwpfFlags & PVRTEX_PIXELTYPE) 
    {
        case OGL_RGB_565:
            m_pDescription->m_eFormat = TextureFormat565;
            break;
        case OGL_RGBA_5551:
            m_pDescription->m_eFormat = TextureFormat5551;
            break;
        case OGL_RGBA_4444:
            m_pDescription->m_eFormat = TextureFormatRgba;
            m_pDescription->m_uiBPP = 4;
            break;
        case OGL_PVRTC2:    
            m_pDescription->m_eFormat = m_pHeader->dwAlphaBitMask ? TextureFormatPvrtcRgba2 : TextureFormatPvrtcRgb2;
            break;
        case OGL_PVRTC4:
            m_pDescription->m_eFormat = m_pHeader->dwAlphaBitMask ? TextureFormatPvrtcRgba4 : TextureFormatPvrtcRgb4;
            break;
        default:
            std::cout<<"[Texture controller] Unsupported format";
            m_eStatus = E_ERROR_STATUS;
            return;
            break;
    }
    
    m_pDescription->m_vSize.x = m_pHeader->dwWidth;
    m_pDescription->m_vSize.y = m_pHeader->dwHeight;
    m_pDescription->m_uiMIP = m_pHeader->dwMipMapCount ? m_pHeader->dwMipMapCount : 1;
    m_pDescription->m_bCompressed = true;
    
    switch (m_pDescription->m_eFormat) 
    {
        case TextureFormatPvrtcRgba2:
            m_pDescription->m_uiBPP = 2;
            m_pDescription->m_glFormat = GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG;
            break;
        case TextureFormatPvrtcRgb2:
            m_pDescription->m_uiBPP = 2;
            m_pDescription->m_glFormat = GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG;
            break;
        case TextureFormatPvrtcRgba4:
            m_pDescription->m_uiBPP = 4;
            m_pDescription->m_glFormat = GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG;
            break;
        case TextureFormatPvrtcRgb4:
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
            case TextureFormatRgba: 
                m_pDescription->m_glFormat = GL_RGBA;
                m_pDescription->m_glType = GL_UNSIGNED_SHORT_4_4_4_4;
                m_pDescription->m_uiBPP = 16;
                break;
            case TextureFormat565:
                m_pDescription->m_glFormat = GL_RGB;
                m_pDescription->m_glType = GL_UNSIGNED_SHORT_5_6_5;
                m_pDescription->m_uiBPP = 16;
                break;
            case TextureFormat5551:
                m_pDescription->m_glFormat = GL_RGBA;
                m_pDescription->m_glType = GL_UNSIGNED_SHORT_5_5_5_1;
                m_pDescription->m_uiBPP = 16;
                break;
            default:
                break;
        }
    }
    m_eStatus = E_DONE_STATUS;
}

void CParser_PVR::Commit()
{
    int uiWidth  = m_pDescription->m_vSize.x;
    int uiHeight = m_pDescription->m_vSize.y;
    char* pData = m_pData + m_pHeader->dwHeaderSize;
    
    m_pSource = new CTexture::SSource();
    m_pSource->m_iWidth  = m_pDescription->m_vSize.x;
    m_pSource->m_iHeight = m_pDescription->m_vSize.y;
    
    glGenTextures( 1, &m_pSource->m_hTextureHanlde );
    glBindTexture( GL_TEXTURE_2D, m_pSource->m_hTextureHanlde );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    
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


