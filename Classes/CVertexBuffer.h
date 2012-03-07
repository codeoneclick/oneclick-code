//
//  CVertexBuffer.h
//  gEngine
//
//  Created by sergey.sergeev on 10/19/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CVertexBuffer_h
#define gEngine_CVertexBuffer_h

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include "CVector.h"
#include <stdlib.h>

class CVertexBuffer
{
protected:
    struct SVertex
    {
        CVector3d*      m_pPositionData;
        CVector2d*      m_pTexCoordData;    
        CByteVector3d*  m_pNormalData;  
        CByteVector3d*  m_pTangentData; 
        CColor4*        m_pColorData;
    };
    
    static const std::string k_SLOT_POSITION;
    static const std::string k_SLOT_TEXCOORD;
    static const std::string k_SLOT_NORMAL;
    static const std::string k_SLOT_TANGENT;
    static const std::string k_SLOT_COLOR;
    
private:
    GLuint m_iHandle;
    GLuint m_iShaderHandle;
    unsigned int m_iNumVertexes;
    unsigned int m_iSize;
    bool m_bIsInVRAM;
    
    GLint m_iPositionSlot;
    GLint m_iTexcoordSlot;
    GLint m_iNormalSlot;
    GLint m_iTangentSlot;
    GLint m_iColorSlot;
    
    SVertex m_pData;
    char* m_pSource;
public:
    CVertexBuffer(unsigned int _iNumVertexes);
    ~CVertexBuffer();
    
    unsigned int Get_NumVertexes(void) { return  m_iNumVertexes; }
    
    CVector3d*      Get_PositionData(void) { return m_pData.m_pPositionData; }
    CVector2d*      Get_TexCoordData(void) { return m_pData.m_pTexCoordData; }
    CByteVector3d*  Get_NormalData(void)   { return m_pData.m_pNormalData;   }
    CByteVector3d*  Get_TangentData(void)  { return m_pData.m_pTangentData;  }
    CColor4*        Get_ColorData(void)   { return m_pData.m_pColorData; }
    
    CVector3d*      CreateOrReUse_PositionData(void);
    CVector2d*      CreateOrReUse_TexCoordData(void);
    CByteVector3d*  CreateOrReUse_NormalData(void);
    CByteVector3d*  CreateOrReUse_TangentData(void);
    CColor4*        CreateOrReUse_ColorData(void);

    void Set_ShaderRef(GLuint _iShaderHandler);
    GLuint Get_ShaderRef(void) { return m_iShaderHandle; }
    
    void Enable(void);
    void Disable(void);
    
    void Lock(void);
    void Unlock(void);
    
    void CommitToRAM(void);
    void CommitFromRAMToVRAM(void);
    
};

#endif
