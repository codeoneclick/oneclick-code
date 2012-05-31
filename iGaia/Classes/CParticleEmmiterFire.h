//
//  CParticleEmmiterFire.h
//  iGaia
//
//  Created by sergey sergeev on 5/31/12.
//
//

#ifndef __iGaia__CParticleEmmiterFire__
#define __iGaia__CParticleEmmiterFire__

#include <iostream>
#include "CParticleEmitter.h"
class CParticleEmmiterFire : public CParticleEmitter
{
protected:
    float m_fMoveSpeed;
public:
    CParticleEmmiterFire(void);
    ~CParticleEmmiterFire(void);
    
    void Load(const std::string& _sName, IResource::E_THREAD _eThread);
    void Update(void);
};


#endif /* defined(__iGaia__CParticleEmmiterFire__) */
