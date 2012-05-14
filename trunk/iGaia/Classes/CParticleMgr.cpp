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
    m_lContainer.push_back(pParticleEmitter);
    
    IResource::SResource tResource;
    tResource.m_sName = "emitter";
    tResource.m_eThread = IResource::E_THREAD_MAIN;
    tResource.m_eModel = IResource::E_STANDART_MODEL_NONE;
    tResource.m_bIsBatching = false;
    
    pParticleEmitter->Load(tResource);

    return pParticleEmitter;
}

void CParticleMgr::Remove_ParticleEmitter(CParticleEmitter *_pParticleEmitter)
{
    // TODO
}

void CParticleMgr::Update(void)
{
    std::vector<CParticleEmitter*>::iterator pBeginIterator = m_lContainer.begin();
    std::vector<CParticleEmitter*>::iterator pEndIterator = m_lContainer.end();
    
    while(pBeginIterator != pEndIterator)
    {
        (*pBeginIterator)->Update();
        ++pBeginIterator;
    }
}

void CParticleMgr::Render(INode::E_RENDER_MODE _eMode)
{
    std::vector<CParticleEmitter*>::iterator pBeginIterator = m_lContainer.begin();
    std::vector<CParticleEmitter*>::iterator pEndIterator = m_lContainer.end();
    
    while(pBeginIterator != pEndIterator)
    {
        (*pBeginIterator)->Render(_eMode);
        ++pBeginIterator;
    }
}