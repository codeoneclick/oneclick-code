//
//  CParticleMgr.h
//  iGaia
//
//  Created by code_oneclick on 4/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef __iGaia__CParticleMgr__
#define __iGaia__CParticleMgr__

#include <iostream>
#include "CParticleEmitter.h"
#include "CShadowPlane.h"
class CParticleMgr
{
public:
    enum E_PARTICLE_MODE_STEP { E_PARTICLE_MODE_STEP_EMITTER = 0, E_PARTICLE_MODE_STEP_SHADOW };
protected:
    std::vector<CParticleEmitter*> m_lEmitterContainer;
    std::vector<CShadowPlane*> m_lShadowContainer;
public:
    CParticleMgr(void);
    ~CParticleMgr(void);
    CParticleEmitter* Add_ParticleEmitter(void);
    CShadowPlane* Add_ShadowPlane(void);
    void Remove_ParticleEmitter(CParticleEmitter* _pParticleEmitter);
    void Remove_ShadowPlane(CShadowPlane* _pShadowPlane);
    void Update(void);
    void Render(INode::E_RENDER_MODE _eMode, E_PARTICLE_MODE_STEP _eStep);
};

#endif /* defined(__iGaia__CParticleMgr__) */
