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

#define COMPRESS_VEC(s, ...) { \
NSString *dbgMessage = [NSString stringWithFormat : (s), ##__VA_ARGS__];\
NSString *dbgTitle = [NSString stringWithFormat:@"%s:(%d)", __PRETTY_FUNCTION__, __LINE__];\
NSLog(@"%s\t%@", [dbgTitle UTF8String], dbgMessage); \
}

class CVertexBuffer
{
public:
    
    /*class CCompressedVec
    {
    public:
        union 
        {
            struct 
            {
                unsigned char x, y, z, w;
            };
            unsigned char v[4];
        };
        
        CCompressedVec(void) : x(0), y(0), z(0), w(0) {}
        CCompressedVec(const CCompressedVec& _vVector ) : x(_vVector.x), y(_vVector.y), z(_vVector.z), w(0) {}
        CCompressedVec(unsigned char _x, unsigned char _y, unsigned char _z) : x(_x), y(_y), z(_z), w(0) {}
        CCompressedVec(const glm::vec3& _vVector) 
        {
            glm::vec3 vNormalized = glm::normalize(_vVector);
            
            x = static_cast<unsigned char>((vNormalized.x + 1.0f) * 0.5f * 255.0f);
            y = static_cast<unsigned char>((vNormalized.y + 1.0f) * 0.5f * 255.0f);
            z = static_cast<unsigned char>((vNormalized.z + 1.0f) * 0.5f * 255.0f);
            w = 0;
            
            vNormalized.x = static_cast<float>(x / (255.0f * 0.5f) - 1.0f);
            vNormalized.y = static_cast<float>(y / (255.0f * 0.5f) - 1.0f);
            vNormalized.z = static_cast<float>(z / (255.0f * 0.5f) - 1.0f);
        };
    };*/
    
    struct SVertex
    {
        glm::vec3*    m_pPositionData;
        glm::vec2*    m_pTexCoordData;
        glm::u8vec4*  m_pNormalData;  
        glm::u8vec4*  m_pTangentData; 
        glm::u8vec4*  m_pColorData;
    };
protected:
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
    
    static glm::u8vec4 CompressVector(const glm::vec3& _vUncopressed);
    
    void Enable(void);
    void Disable(void);
    
    void Lock(void);
    void Unlock(void);
    
    void CommitToRAM(void);
    void CommitFromRAMToVRAM(void);
    
};

#endif
