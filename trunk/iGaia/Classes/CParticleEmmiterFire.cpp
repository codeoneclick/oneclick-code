//
//  CParticleEmmiterFire.cpp
//  iGaia
//
//  Created by sergey sergeev on 5/31/12.
//
//

#include "CParticleEmmiterFire.h"

CParticleEmmiterFire::CParticleEmmiterFire(void)
{
    m_fMoveSpeed = 0.0f;
}

CParticleEmmiterFire::~CParticleEmmiterFire(void)
{
    
}

void CParticleEmmiterFire::Load(const std::string &_sName, IResource::E_THREAD _eThread)
{
    CParticleEmitter::Load(_sName, _eThread);
    
    for(unsigned short i = 0; i < m_iNumParticles; i++)
    {
        glm::vec3 vPosition = m_pParticles[i].m_vPosition;
        float fOffset = _Get_RandomFromRange(0.0f, 0.33f);
        vPosition.x = fOffset;
        fOffset = _Get_RandomFromRange(0.0f, 0.33f);
        vPosition.z = fOffset;
        m_pParticles[i].m_vPosition = vPosition;
    }
}

void CParticleEmmiterFire::Update(void)
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