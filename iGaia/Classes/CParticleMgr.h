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
class CParticleMgr
{
protected:
    std::vector<CParticleEmitter*> m_lEmitterContainer;
public:
    CParticleMgr(void);
    ~CParticleMgr(void);
    CParticleEmitter* Add_ParticleEmitter(void);
    void Remove_ParticleEmitter(CParticleEmitter* _pParticleEmitter);
    void Update(void);
    void Render(INode::E_RENDER_MODE _eMode);
};

#endif /* defined(__iGaia__CParticleMgr__) */