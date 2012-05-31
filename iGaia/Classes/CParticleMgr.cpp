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

CParticleEmmiterFire* CParticleMgr::Add_ParticleEmitterFire(unsigned int _iNumParticles,const glm::vec2& _vMinSize,const glm::vec2& _vMaxSize, int _iLifeTime)
{
    CParticleEmmiterFire* pParticleEmitter = new CParticleEmmiterFire();
    pParticleEmitter->Set_NumParticles(_iNumParticles);
    pParticleEmitter->Set_MinSize(_vMinSize);
    pParticleEmitter->Set_MaxSize(_vMinSize);
    pParticleEmitter->Set_LifeTime(_iLifeTime);
    m_lEmitterContainer.push_back(pParticleEmitter);
    pParticleEmitter->Load("emitter", IResource::E_THREAD_MAIN);
    return pParticleEmitter;
}

CCrossBoxEffect* CParticleMgr::Add_CrossBoxEffect(unsigned int _iNumTextureChunks, const glm::vec2 &_vSizeTextureChunk, const glm::vec2 &_vSizeTextureAtlas)
{
    CCrossBoxEffect* pEffect = new CCrossBoxEffect();
    pEffect->Set_NumTextureChunks(_iNumTextureChunks);
    pEffect->Set_SizeTextureChunk(_vSizeTextureChunk);
    pEffect->Set_SizeTextureAtlas(_vSizeTextureAtlas);
    m_lEffectContainer.push_back(pEffect);
    pEffect->Load("effect", IResource::E_THREAD_MAIN);
    return pEffect;
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
            break;
        }
        ++pBeginEmitterIterator;
    }
}

void CParticleMgr::Remove_Effect(INode *_pEffect)
{
    
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
    
    std::vector<INode*>::iterator pBeginEffectIterator = m_lEffectContainer.begin();
    std::vector<INode*>::iterator pEndEffectIterator = m_lEffectContainer.end();
    
    while(pBeginEffectIterator != pEndEffectIterator)
    {
        (*pBeginEffectIterator)->Update();
        ++pBeginEffectIterator;
    }

}

void CParticleMgr::Render(CShader::E_RENDER_MODE _eMode)
{
    std::vector<CParticleEmitter*>::iterator pBeginEmitterIterator = m_lEmitterContainer.begin();
    std::vector<CParticleEmitter*>::iterator pEndEmitterIterator = m_lEmitterContainer.end();
    
    while(pBeginEmitterIterator != pEndEmitterIterator)
    {
        (*pBeginEmitterIterator)->Render(_eMode);
        ++pBeginEmitterIterator;
    }
    
    std::vector<INode*>::iterator pBeginEffectIterator = m_lEffectContainer.begin();
    std::vector<INode*>::iterator pEndEffectIterator = m_lEffectContainer.end();
    
    while(pBeginEffectIterator != pEndEffectIterator)
    {
        (*pBeginEffectIterator)->Render(_eMode);
        ++pBeginEffectIterator;
    }
}

