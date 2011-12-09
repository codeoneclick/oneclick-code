//
//  CParser_PVR.h
//  gEngine
//
//  Created by sergey.sergeev on 10/31/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CParser_PVR_h
#define gEngine_CParser_PVR_h

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include "PVRTTexture.h"
#include "CVector.h"
#include "CTexture.h"
#include "IParser.h"

class CParser_PVR : public IParser
{
protected:
    enum E_TEXTURE_FORMAT 
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
        E_TEXTURE_FORMAT m_eFormat;
        GLenum m_glFormat;
        GLenum m_glType;
        int m_uiBPP;
        Vector2d m_vSize;
        unsigned int m_uiMIP;
        bool m_bCompressed;
    };
    
private:
    CTexture::SSource* m_pSource;
    char* m_pData;
    SDescription* m_pDescription;
    PVR_Texture_Header* m_pHeader;
public:
    CParser_PVR();
    virtual ~CParser_PVR();
    virtual void* Get_Source() { return m_pSource; }
    virtual void Load(const std::string& _sName);
    virtual void Commit();
};

#endif
