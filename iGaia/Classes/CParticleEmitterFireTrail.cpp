//
//  CParticleEmitterFireTrail.cpp
//  iGaia
//
//  Created by sergey sergeev on 6/12/12.
//
//

#include "CParticleEmitterFireTrail.h"

CParticleEmitterFireTrail::CParticleEmitterFireTrail(void)
{
    m_fMoveSpeed = 0.0f;
}

CParticleEmitterFireTrail::~CParticleEmitterFireTrail(void)
{
    
}

void CParticleEmitterFireTrail::Load(const std::string &_sName, IResource::E_THREAD _eThread)
{
    CParticleEmitter::Load(_sName, _eThread);
    
    for(unsigned short i = 0; i < m_iNumParticles; i++)
    {
        m_pParticles[i].m_vPosition = glm::vec3(0.0f, 0.0f, 0.0f);
        m_pParticles[i].m_vSize = m_vMaxSize;
    }
}

void CParticleEmitterFireTrail::Update(void)
{
    for(unsigned short i = 0; i < m_iNumParticles; i += 6)
    {
        glm::vec3 vPosition = m_pParticles[i + 0].m_vPosition;
        m_fMoveSpeed = _Get_RandomFromRange(0.0f, 150.0f) / 500.0f;
        vPosition.x += m_fMoveSpeed;
        m_pParticles[i + 0].m_vPosition = vPosition;
        
        vPosition = m_pParticles[i + 1].m_vPosition;
        m_fMoveSpeed = _Get_RandomFromRange(0.0f, 150.0f) / 500.0f;
        vPosition.x -= m_fMoveSpeed;
        m_pParticles[i + 1].m_vPosition = vPosition;

        vPosition = m_pParticles[i + 2].m_vPosition;
        m_fMoveSpeed = _Get_RandomFromRange(0.0f, 150.0f) / 500.0f;
        vPosition.y += m_fMoveSpeed;
        m_pParticles[i + 2].m_vPosition = vPosition;

        vPosition = m_pParticles[i + 3].m_vPosition;
        m_fMoveSpeed = _Get_RandomFromRange(0.0f, 150.0f) / 500.0f;
        vPosition.y -= m_fMoveSpeed;
        m_pParticles[i + 3].m_vPosition = vPosition;
        
        vPosition = m_pParticles[i + 4].m_vPosition;
        m_fMoveSpeed = _Get_RandomFromRange(0.0f, 150.0f) / 500.0f;
        vPosition.z += m_fMoveSpeed;
        m_pParticles[i + 4].m_vPosition = vPosition;
        
        vPosition = m_pParticles[i + 5].m_vPosition;
        m_fMoveSpeed = _Get_RandomFromRange(0.0f, 150.0f) / 500.0f;
        vPosition.z -= m_fMoveSpeed;
        m_pParticles[i + 5].m_vPosition = vPosition;

        for(unsigned short j = i; j < (i + 6); ++j)
        {
            m_pParticles[j].m_vSize += m_vMinSize * 0.2f;
            
            unsigned char iDelta = 15;
            
            if(m_pParticles[j].m_vColor.a >= iDelta)
            {
                m_pParticles[j].m_vColor.a -= iDelta;
                //m_pParticles[j].m_vPosition = glm::vec3(0.0f, 0.0f, 0.0f);
                //m_pParticles[j].m_vColor.a = 255;
                //m_pParticles[j].m_vSize = m_vMaxSize;
            }
        }
    }
    CParticleEmitter::Update();
}
