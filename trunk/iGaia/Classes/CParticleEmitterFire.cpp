//
//  ~CParticleEmitterFire.cpp
//  iGaia
//
//  Created by sergey sergeev on 5/31/12.
//
//

#include "CParticleEmitterFire.h"
#include "CTimer.h"

CParticleEmitterFire::CParticleEmitterFire(void)
{
    m_fMoveSpeed = 0.0f;
}

CParticleEmitterFire::~CParticleEmitterFire(void)
{
    
}

void CParticleEmitterFire::Load(const std::string &_sName, IResource::E_THREAD _eThread)
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

void CParticleEmitterFire::Update(void)
{
    for(unsigned short i = 0; i < m_iNumParticles; i++)
    {
        glm::vec3 vPosition = m_pParticles[i].m_vPosition;
        m_fMoveSpeed = _Get_RandomFromRange(0.0f, 250.0f) / 500.0f;
        vPosition.y += m_fMoveSpeed;
        m_pParticles[i].m_vPosition = vPosition;
        m_pParticles[i].m_vSize += m_vMinSize;
        int iCurrentTime = CTimer::Instance()->Get_TickCount();
        m_pParticles[i].m_vColor.a -= 15;
        if(m_pParticles[i].m_vPosition.y > m_fMaxY && m_bIsEnable)
        {
            m_pParticles[i].m_vPosition.y = 0.0f;
            m_pParticles[i].m_vSize = m_vMinSize;
            if((iCurrentTime - m_pParticles[i].m_iTime) > m_iLifeTime)
            {
                m_pParticles[i].m_iTime = CTimer::Instance()->Get_TickCount();
            }
            m_pParticles[i].m_vColor.a = 255;
        }
        else if(!m_bIsEnable && m_pParticles[i].m_vColor.a > 0 && m_pParticles[i].m_vPosition.y > m_fMaxY * 0.33f)
        {
            //m_pParticles[i].m_vColor.a -= 15;
        }
        
        if(m_pParticles[i].m_vColor.a == 0)
        {
            m_pParticles[i].m_vPosition.y = 128.0f;
        }
    }
    CParticleEmitter::Update();
}





