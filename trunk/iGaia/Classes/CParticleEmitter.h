//
//  CParticleEmitter.h
//  iGaia
//
//  Created by code_oneclick on 4/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef __iGaia__CParticleEmitter__
#define __iGaia__CParticleEmitter__

#include <iostream>
#include "INode.h"

class CParticleEmitter : public INode
{
protected:
    struct SParticle
    {
        glm::vec3 m_vPosition;
        glm::vec3 m_vRotation;
        glm::vec3 m_vScale;
        glm::vec2 m_vSize;
        glm::vec3 m_vVelocity;  
        glm::u8vec4 m_vColor;
        float m_fTime;         
    };
    float _Get_RandomFromRange(float _fMin, float _fMax);
    unsigned int m_iNumParticles;
    SParticle* m_pParticles;
public:
    CParticleEmitter(void);
    ~CParticleEmitter(void);
    virtual void Load(IResource::SResource _tResource);
    virtual void OnLoadDone(E_RESOURCE_TYPE _eType, IResource* pResource);
    virtual void OnTouchEvent(void);
    virtual void OnPhysicEventUpdate(glm::vec3 _vPosition, glm::vec3 _vRotation, glm::vec3 _vScale) { }
    virtual void Set_Shader(IResource::E_SHADER _eShader);
    virtual void Create_BoundingBox(void) { }
    virtual void Update(void);
    virtual void Render(E_RENDER_MODE _eMode);
};

#endif /* defined(__iGaia__CParticleEmitter__) */
