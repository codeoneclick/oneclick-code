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
public:
    struct SPVRSource
    {
        char* m_pData;
        SDescription* m_pDescription;
        GLuint m_uiHanlde;
        PVR_Texture_Header* m_pHeader;
    };
    
    enum E_STATUS
    {
        E_STATUS_NONE,
        E_STATUS_START,
        E_STATUS_ERROR,
        E_STATUS_DONE,
    };
    
private:
    SPVRSource* m_pSource;
    E_STATUS m_eStatus;
public:
    CPVRLoader();
    ~CPVRLoader();
    inline E_STATUS Get_Status() { return m_eStatus; }
    inline SPVRSource* Get_Source() { return m_pSource; }
    void Load(const char* _sName);
    void CommitVRAM();
};

#endif
