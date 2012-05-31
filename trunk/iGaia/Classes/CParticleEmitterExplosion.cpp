//
//  CParticleEmitterExplosion.cpp
//  iGaia
//
//  Created by sergey sergeev on 5/31/12.
//
//

#include "CParticleEmitterExplosion.h"

CParticleEmitterExplosion::CParticleEmitterExplosion(void)
{
    m_fMoveSpeed = 0.0f;
}

CParticleEmitterExplosion::~CParticleEmitterExplosion(void)
{
    
}

void CParticleEmitterExplosion::Load(const std::string &_sName, IResource::E_THREAD _eThread)
{
    CParticleEmitter::Load(_sName, _eThread);
    
    unsigned int iNumParticlesPerAxis = m_iNumParticles / 3;
    float fStepAngle = 360.0f / iNumParticlesPerAxis;
    unsigned int index = 0;
    float fCurrentAngle = 0.0f;
    
    for(unsigned int i = 0; i < iNumParticlesPerAxis; ++i)
    {
        m_pParticles[index].m_vDirection.x += sinf(glm::radians(fCurrentAngle));
        m_pParticles[index].m_vDirection.y += cosf(glm::radians(fCurrentAngle));
        fCurrentAngle += fStepAngle;
        ++index;
    }
    
    fCurrentAngle = 0.0f;
    
    for(unsigned int i = 0; i < iNumParticlesPerAxis; ++i)
    {
        m_pParticles[index].m_vDirection.x += sinf(glm::radians(fCurrentAngle));
        m_pParticles[index].m_vDirection.z += cosf(glm::radians(fCurrentAngle));
        fCurrentAngle += fStepAngle;
        ++index;
    }
    
    fCurrentAngle = 0.0f;
    
    for(unsigned int i = 0; i < iNumParticlesPerAxis; ++i)
    {
        m_pParticles[index].m_vDirection.y += sinf(glm::radians(fCurrentAngle));
        m_pParticles[index].m_vDirection.z += cosf(glm::radians(fCurrentAngle));
        fCurrentAngle += fStepAngle;
        ++index;
    }
}

void CParticleEmitterExplosion::Update(void)
{
    for(unsigned short i = 0; i < m_iNumParticles; i++)
    {
        glm::vec3 vPosition = m_pParticles[i].m_vPosition;
        m_fMoveSpeed = _Get_RandomFromRange(0.0f, 250.0f) / 500.0f;
        vPosition.y += m_fMoveSpeed;
        m_pParticles[i].m_vPosition = vPosition;
        m_pParticles[i].m_vSize += m_vMinSize;
        int iCurrentTime = _Get_TickCount();
        if(m_pParticles[i].m_vPosition.y > 1.5f)
        {
            m_pParticles[i].m_vPosition.y = 0.0f;
            m_pParticles[i].m_vSize = m_vMinSize;
            if((iCurrentTime - m_pParticles[i].m_iTime) > m_iLifeTime)
            {
                m_pParticles[i].m_iTime = _Get_TickCount();
            }
        }
    }
    CParticleEmitter::Update();
}





