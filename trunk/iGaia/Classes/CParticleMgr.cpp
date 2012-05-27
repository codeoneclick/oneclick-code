//
//  CParticleMgr.cpp
//  iGaia
//
//  Created by code_oneclick on 4/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "CParticleMgr.h"

CParticleMgr::CParticleMgr(void)
{

}


CParticleMgr::~CParticleMgr(void)
{
    
}

CParticleEmitter* CParticleMgr::Add_ParticleEmitter(void)
{
    CParticleEmitter* pParticleEmitter = new CParticleEmitter();
    m_lEmitterContainer.push_back(pParticleEmitter);
    
    pParticleEmitter->Load("emitter", IResource::E_THREAD_MAIN);

    return pParticleEmitter;
}

void CParticleMgr::Remove_ParticleEmitter(CParticleEmitter *_pParticleEmitter)
{
    std::vector<CParticleEmitter*>::iterator pBeginEmitterIterator = m_lEmitterContainer.begin();
    std::vector<CParticleEmitter*>::iterator pEndEmitterIterator = m_lEmitterContainer.end();
    
    while(pBeginEmitterIterator != pEndEmitterIterator)
    {
        if((*pBeginEmitterIterator) == _pParticleEmitter)
        {
            m_lEmitterContainer.erase(pBeginEmitterIterator);
            delete _pParticleEmitter;
            _pParticleEmitter = NULL;
            return;
        }
        ++pBeginEmitterIterator;
    }
}

void CParticleMgr::Update(void)
{
    std::vector<CParticleEmitter*>::iterator pBeginEmitterIterator = m_lEmitterContainer.begin();
    std::vector<CParticleEmitter*>::iterator pEndEmitterIterator = m_lEmitterContainer.end();
    
    while(pBeginEmitterIterator != pEndEmitterIterator)
    {
        (*pBeginEmitterIterator)->Update();
        ++pBeginEmitterIterator;
    }
}

void CParticleMgr::Render(INode::E_RENDER_MODE _eMode)
{
    std::vector<CParticleEmitter*>::iterator pBeginEmitterIterator = m_lEmitterContainer.begin();
    std::vector<CParticleEmitter*>::iterator pEndEmitterIterator = m_lEmitterContainer.end();
    
    while(pBeginEmitterIterator != pEndEmitterIterator)
    {
        (*pBeginEmitterIterator)->Render(_eMode);
        ++pBeginEmitterIterator;
    }
}


