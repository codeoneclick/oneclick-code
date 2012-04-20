//
//  CVertexBuffer.h
//  iGaia
//
//  Created by sergey.sergeev on 10/19/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CVertexBuffer_h
#define iGaia_CVertexBuffer_h

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_precision.hpp>
#include <stdlib.h>

class CVertexBuffer
{
protected:
    static const std::string k_SLOT_POSITION;
    static const std::string k_SLOT_TEXCOORD;
    static const std::string k_SLOT_NORMAL;
    static const std::string k_SLOT_TANGENT;
    static const std::string k_SLOT_COLOR;
    
struct SVertex
{
    glm::vec3*    m_pPositionData;
    glm::vec2*    m_pTexCoordData;
    glm::u8vec4*  m_pNormalData;  
    glm::u8vec4*  m_pTangentData; 
    glm::u8vec4*  m_pColorData;
};

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
    ~CVertexBuffer(void);
    
    unsigned int Get_NumVertexes(void) { return  m_iNumVertexes; }
    
    glm::vec3*    Get_PositionData(void) { assert(m_pData.m_pPositionData == NULL); return m_pData.m_pPositionData; }
    glm::vec2*    Get_TexCoordData(void) { assert(m_pData.m_pTexCoordData == NULL); return m_pData.m_pTexCoordData; }
    glm::u8vec4*  Get_NormalData(void)   { assert(m_pData.m_pNormalData == NULL);   return m_pData.m_pNormalData;   }
    glm::u8vec4*  Get_TangentData(void)  { assert(m_pData.m_pTangentData == NULL);  return m_pData.m_pTangentData;  }
    glm::u8vec4*  Get_ColorData(void)    { assert(m_pData.m_pColorData == NULL);    return m_pData.m_pColorData;    }
    
    glm::vec3*    CreateOrReUse_PositionData(void);
    glm::vec2*    CreateOrReUse_TexCoordData(void);
    glm::u8vec4*  CreateOrReUse_NormalData(void);
    glm::u8vec4*  CreateOrReUse_TangentData(void);
    glm::u8vec4*  CreateOrReUse_ColorData(void);
    
    void Set_ShaderRef(GLuint _iShaderHandler);
    GLuint Get_ShaderRef(void) { return m_iShaderHandle; }
    
    static glm::u8vec4 CompressVEC3(const glm::vec3& _vUncopressed);
    static glm::vec3   UnCompressU8VEC4(const glm::u8vec4 _vCompressed);
    
    void Enable(void);
    void Disable(void);
    
    void Lock(void);
    void Unlock(void);
    
    void CommitToRAM(void);
    void CommitFromRAMToVRAM(void);
    
};

#endif
