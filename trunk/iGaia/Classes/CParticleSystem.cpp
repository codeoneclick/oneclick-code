//
//  CParticleSystem.cpp
//  iGaia
//
//  Created by code_oneclick on 4/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "CParticleSystem.h"

const std::string CParticleSystem::k_SLOT_POSITION   = "IN_SLOT_Position";
const std::string CParticleSystem::k_SLOT_TEXCOORD   = "IN_SLOT_TexCoord";
const std::string CParticleSystem::k_SLOT_COLOR      = "IN_SLOT_Color";

CParticleSystem::CParticleSystem(unsigned short _iMaxParticles)
{
    m_iMaxParticles = _iMaxParticles;
    m_pVertexBuffer = new SParticleDeclaration[4 * m_iMaxParticles];
    
    m_pParticles = new SParticle[m_iMaxParticles];
    for(unsigned int index = 0; index < m_iMaxParticles; index++)
    {
        m_pParticles[index].m_vPosition = glm::vec3(0.0f, 0.0f, 0.0f);
        m_pParticles[index].m_vVelocity = glm::vec3(0.0f, 0.0f, 0.0f);
        m_pParticles[index].m_vColor = glm::u8vec4(0, 0, 0, 0);
        m_pParticles[index].m_fTime = 0.0f;
        m_pParticles[index].m_vSize = glm::vec2(0.5f, 0.5f);
        
        m_pVertexBuffer[index * 4 + 0].m_vPosition = glm::vec3(m_pParticles[index].m_vPosition.x - m_pParticles[index].m_vSize.x, m_pParticles[index].m_vPosition.y, m_pParticles[index].m_vPosition.z - m_pParticles[index].m_vSize.y);
        m_pVertexBuffer[index * 4 + 1].m_vPosition = glm::vec3(m_pParticles[index].m_vPosition.x + m_pParticles[index].m_vSize.x, m_pParticles[index].m_vPosition.y, m_pParticles[index].m_vPosition.z - m_pParticles[index].m_vSize.y);;
        m_pVertexBuffer[index * 4 + 2].m_vPosition = glm::vec3(m_pParticles[index].m_vPosition.x + m_pParticles[index].m_vSize.x, m_pParticles[index].m_vPosition.y, m_pParticles[index].m_vPosition.z + m_pParticles[index].m_vSize.y);;
        m_pVertexBuffer[index * 4 + 3].m_vPosition = glm::vec3(m_pParticles[index].m_vPosition.x - m_pParticles[index].m_vSize.x, m_pParticles[index].m_vPosition.y, m_pParticles[index].m_vPosition.z + m_pParticles[index].m_vSize.y);;
        
        m_pVertexBuffer[index * 4 + 0].m_vTexCoord = glm::vec2(-1.0f, -1.0f);
        m_pVertexBuffer[index * 4 + 1].m_vTexCoord = glm::vec2( 1.0f, -1.0f);
        m_pVertexBuffer[index * 4 + 2].m_vTexCoord = glm::vec2( 1.0f,  1.0f);
        m_pVertexBuffer[index * 4 + 3].m_vTexCoord = glm::vec2(-1.0f,  1.0f);
        
        m_pVertexBuffer[index * 4 + 0].m_vColor = m_pParticles[index].m_vColor;
        m_pVertexBuffer[index * 4 + 1].m_vColor = m_pParticles[index].m_vColor;
        m_pVertexBuffer[index * 4 + 2].m_vColor = m_pParticles[index].m_vColor;
        m_pVertexBuffer[index * 4 + 3].m_vColor = m_pParticles[index].m_vColor;
    }
    
    m_pIndexBuffer = new unsigned short[m_iMaxParticles * 6];
    for(unsigned int index = 0; index < m_iMaxParticles; index++)
    {
        m_pIndexBuffer[index * 6 + 0] = static_cast<unsigned short>(index * 4 + 0);
        m_pIndexBuffer[index * 6 + 1] = static_cast<unsigned short>(index * 4 + 1);
        m_pIndexBuffer[index * 6 + 2] = static_cast<unsigned short>(index * 4 + 2);
        
        m_pIndexBuffer[index * 6 + 3] = static_cast<unsigned short>(index * 4 + 0);
        m_pIndexBuffer[index * 6 + 4] = static_cast<unsigned short>(index * 4 + 2);
        m_pIndexBuffer[index * 6 + 5] = static_cast<unsigned short>(index * 4 + 3);
    }
    
    m_iSize = sizeof(SParticleDeclaration);
}

CParticleSystem::~CParticleSystem(void)
{
    
}

void CParticleSystem::Set_ShaderRef(GLuint _iShaderHandler)
{
    m_iShaderHandle = _iShaderHandler;
    m_iPositionSlot = glGetAttribLocation(m_iShaderHandle, k_SLOT_POSITION.c_str());
    m_iTexcoordSlot = glGetAttribLocation(m_iShaderHandle, k_SLOT_TEXCOORD.c_str());
    m_iColorSlot    = glGetAttribLocation(m_iShaderHandle, k_SLOT_COLOR.c_str());
}

void CParticleSystem::Enable(void)
{
    glBindBuffer(GL_ARRAY_BUFFER, NULL);
    
    const GLvoid* pPositionSource = NULL;
    const GLvoid* pTexcoordSource = NULL;

    const GLvoid* pColorSource    = NULL;
    
    pPositionSource = &m_pVertexBuffer[0].m_vPosition;
    pTexcoordSource = &m_pVertexBuffer[0].m_vTexCoord;
    pColorSource    = &m_pVertexBuffer[0].m_vColor;
    
    if(m_iPositionSlot >= 0) 
    {
        glVertexAttribPointer(m_iPositionSlot, 3, GL_FLOAT, GL_FALSE, m_iSize, pPositionSource);
        glEnableVertexAttribArray(m_iPositionSlot);
    }
    if(m_iTexcoordSlot >= 0)
    {
        glVertexAttribPointer(m_iTexcoordSlot, 2, GL_FLOAT, GL_FALSE, m_iSize, pTexcoordSource);
        glEnableVertexAttribArray(m_iTexcoordSlot); 
    }
    if(m_iColorSlot >= 0)
    {
        glVertexAttribPointer(m_iColorSlot,  4, GL_UNSIGNED_BYTE, GL_TRUE, m_iSize, pColorSource);
        glEnableVertexAttribArray(m_iColorSlot);
    }
}

void CParticleSystem::Disable(void)
{
    if(m_iPositionSlot >= 0)
    {
        glDisableVertexAttribArray(m_iPositionSlot);
    }
    if(m_iTexcoordSlot >= 0)
    {
        glDisableVertexAttribArray(m_iTexcoordSlot); 
    }
    if(m_iColorSlot >= 0)
    {
        glDisableVertexAttribArray(m_iColorSlot);
    }
}

void CParticleSystem::Update(void)
{
    for(unsigned int index = 0; index < m_iMaxParticles; index++)
    {
        m_pVertexBuffer[index * 4 + 0].m_vPosition = glm::vec3(m_pParticles[index].m_vPosition.x - m_pParticles[index].m_vSize.x, m_pParticles[index].m_vPosition.y, m_pParticles[index].m_vPosition.z - m_pParticles[index].m_vSize.y);
        m_pVertexBuffer[index * 4 + 1].m_vPosition = glm::vec3(m_pParticles[index].m_vPosition.x + m_pParticles[index].m_vSize.x, m_pParticles[index].m_vPosition.y, m_pParticles[index].m_vPosition.z - m_pParticles[index].m_vSize.y);;
        m_pVertexBuffer[index * 4 + 2].m_vPosition = glm::vec3(m_pParticles[index].m_vPosition.x + m_pParticles[index].m_vSize.x, m_pParticles[index].m_vPosition.y, m_pParticles[index].m_vPosition.z + m_pParticles[index].m_vSize.y);;
        m_pVertexBuffer[index * 4 + 3].m_vPosition = glm::vec3(m_pParticles[index].m_vPosition.x - m_pParticles[index].m_vSize.x, m_pParticles[index].m_vPosition.y, m_pParticles[index].m_vPosition.z + m_pParticles[index].m_vSize.y);;
        
        m_pVertexBuffer[index * 4 + 0].m_vColor = m_pParticles[index].m_vColor;
        m_pVertexBuffer[index * 4 + 1].m_vColor = m_pParticles[index].m_vColor;
        m_pVertexBuffer[index * 4 + 2].m_vColor = m_pParticles[index].m_vColor;
        m_pVertexBuffer[index * 4 + 3].m_vColor = m_pParticles[index].m_vColor;
    }
}





