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

CShadowPlane* CParticleMgr::Add_ShadowPlane(void)
{
    CShadowPlane* pShadowPlane = new CShadowPlane();
    m_lShadowContainer.push_back(pShadowPlane);
   
    IResource::SResource tResource;
    tResource.m_sName = "shadow";
    tResource.m_eThread = IResource::E_THREAD_MAIN;
    tResource.m_eModel = IResource::E_STANDART_MODEL_NONE;
    tResource.m_bIsBatching = false;

    pShadowPlane->Load(tResource);
    
    return pShadowPlane;
}

void CParticleMgr::Remove_ShadowPlane(CShadowPlane *_pShadowPlane)
{
    // TODO
}

void CParticleMgr::Update(void)
{
    std::vector<CShadowPlane*>::iterator pBeginShadowIterator = m_lShadowContainer.begin();
    std::vector<CShadowPlane*>::iterator pEndShadowIterator = m_lShadowContainer.end();
    
    while(pBeginShadowIterator != pEndShadowIterator)
    {
        (*pBeginShadowIterator)->Update();
        ++pBeginShadowIterator;
    }
    
    std::vector<CParticleEmitter*>::iterator pBeginEmitterIterator = m_lEmitterContainer.begin();
    std::vector<CParticleEmitter*>::iterator pEndEmitterIterator = m_lEmitterContainer.end();
    
    while(pBeginEmitterIterator != pEndEmitterIterator)
    {
        (*pBeginEmitterIterator)->Update();
        ++pBeginEmitterIterator;
    }
}

void CParticleMgr::Render(INode::E_RENDER_MODE _eMode, CParticleMgr::E_PARTICLE_MODE_STEP _eStep)
{
    
    if(_eStep == E_PARTICLE_MODE_STEP_SHADOW)
    {
        std::vector<CShadowPlane*>::iterator pBeginShadowIterator = m_lShadowContainer.begin();
        std::vector<CShadowPlane*>::iterator pEndShadowIterator = m_lShadowContainer.end();
    
        while(pBeginShadowIterator != pEndShadowIterator)
        {
            (*pBeginShadowIterator)->Render(_eMode);
            ++pBeginShadowIterator;
        }
    }
    
    if(_eStep == E_PARTICLE_MODE_STEP_EMITTER)
    {
        std::vector<CParticleEmitter*>::iterator pBeginEmitterIterator = m_lEmitterContainer.begin();
        std::vector<CParticleEmitter*>::iterator pEndEmitterIterator = m_lEmitterContainer.end();
    
        while(pBeginEmitterIterator != pEndEmitterIterator)
        {
            (*pBeginEmitterIterator)->Render(_eMode);
            ++pBeginEmitterIterator;
        }
    }
}


