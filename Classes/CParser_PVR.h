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
#include <glm/glm.hpp>
#include "CTexture.h"
#include "IParser.h"

class CParser_PVR : public IParser
{
protected:
    enum E_TEXTURE_FORMAT 
    {
        TextureFormatPvrtcRgb2,
        TextureFormatPvrtcRgba2,
        TextureFormatPvrtcRgb4,
        TextureFormatPvrtcRgba4,
    };
    
    struct SDescription
    {
        E_TEXTURE_FORMAT m_eFormat;
        GLenum m_glFormat;
        GLenum m_glType;
        int m_uiBPP;
        glm::vec2 m_vSize;
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
