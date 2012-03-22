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
        case OGL_PVRTC2:    
            m_pDescription->m_eFormat = m_pHeader->dwAlphaBitMask ? TextureFormatPvrtcRgba2 : TextureFormatPvrtcRgb2;
            break;
        case OGL_PVRTC4:
            m_pDescription->m_eFormat = m_pHeader->dwAlphaBitMask ? TextureFormatPvrtcRgba4 : TextureFormatPvrtcRgb4;
            break;
        default:
            std::cout<<"[CParser_PVR::Load] Unsupported format for Texture Name : "<<_sName<<"\n";
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
    
    std::cout<<"[CParser_PVR::Load] Texture Name : "<<_sName<<" Texture Width : "<<m_pDescription->m_vSize.x<<" Texture Height : "<<m_pDescription->m_vSize.y<<" Texture MIPS : "<<m_pDescription->m_uiMIP<<"\n";
    m_eStatus = E_DONE_STATUS;
}

void CParser_PVR::Commit(void)
{
    int iWidth  = m_pDescription->m_vSize.x;
    int iHeight = m_pDescription->m_vSize.y;
    char* pData = m_pData + m_pHeader->dwHeaderSize;
    
    m_pSource = new CTexture::SSource();
    m_pSource->m_iWidth  = m_pDescription->m_vSize.x;
    m_pSource->m_iHeight = m_pDescription->m_vSize.y;
    
    glGenTextures( 1, &m_pSource->m_hTextureHanlde );
    glBindTexture( GL_TEXTURE_2D, m_pSource->m_hTextureHanlde );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    if (m_pDescription->m_bCompressed) 
    {
        for (int level = 0; iWidth > 0 && iHeight > 0; ++level) 
        {
            GLsizei iSize = std::max(32, iWidth * iHeight * m_pDescription->m_uiBPP / 8);
            glCompressedTexImage2D(GL_TEXTURE_2D, level, m_pDescription->m_glFormat, iWidth, iHeight, 0, iSize, pData);
            pData += iSize;
            iWidth >>= 1; iHeight >>= 1;
        }
    } 
    else
    {       
        glTexImage2D(GL_TEXTURE_2D, 0, m_pDescription->m_glFormat, iWidth, iHeight, 0, m_pDescription->m_glFormat, m_pDescription->m_glType, pData);
        //glHint(GL_GENERATE_MIPMAP_HINT, GL_NICEST);
        glHint(GL_GENERATE_MIPMAP_HINT, GL_FASTEST);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

}


