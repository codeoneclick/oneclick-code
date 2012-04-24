//
//  CParticleSystem.h
//  iGaia
//
//  Created by code_oneclick on 4/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef __iGaia__CParticleSystem__
#define __iGaia__CParticleSystem__

#include <iostream>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_precision.hpp>

class CParticleSystem
{
public:
    struct SParticle
    {
        glm::vec3 m_vPosition;  
        glm::vec2 m_vSize;
        glm::vec3 m_vVelocity;  
        glm::u8vec4 m_vColor;   
        float m_fTime;         
    };
protected:
    struct SParticleDeclaration
    {
        glm::vec3 m_vPosition; // 12 bytes
        glm::vec2 m_vTexCoord; // 8 bytes
        glm::u8vec4 m_vColor;  // 4 bytes
    };

    SParticle* m_pParticles;
    SParticleDeclaration* m_pVertexBuffer;
    unsigned short* m_pIndexBuffer;
    unsigned short m_iMaxParticles;

    static const std::string k_SLOT_POSITION;
    static const std::string k_SLOT_TEXCOORD;
    static const std::string k_SLOT_COLOR;

    GLuint m_iShaderHandle;
    unsigned int m_iNumVertexes;
    unsigned int m_iSize;

    GLint m_iPositionSlot;
    GLint m_iTexcoordSlot;
    GLint m_iColorSlot;

public:
    CParticleSystem(unsigned short _iMaxParticles);
    ~CParticleSystem(void);
    void Update(void);
    void Set_ShaderRef(GLuint _iShaderHandler);
    unsigned short* Get_IndexBufferRef(void) { return m_pIndexBuffer; }
    unsigned int Get_NumIndexes(void) { return m_iMaxParticles * 6; }
    SParticle* Get_Particles(void) { return m_pParticles; }
    unsigned short Get_NumParticles(void) {  return m_iMaxParticles; }
    void Enable(void);
    void Disable(void);
};

#endif /* defined(__iGaia__CParticleSystem__) */
