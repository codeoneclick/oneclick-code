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
        glm::vec3 m_vDirection;
        glm::u8vec4 m_vColor;
        int m_iTime;
    };
    SParticle* m_pParticles;
     
    unsigned int m_iNumParticles;
    glm::vec2 m_vMinSize;
    glm::vec2 m_vMaxSize;
    int m_iLifeTime;

    float _Get_RandomFromRange(float _fMin, float _fMax);
    uint64_t _Get_TickCount(void);
public:
    CParticleEmitter(void);
    virtual ~CParticleEmitter(void);
    virtual void Load(const std::string& _sName, IResource::E_THREAD _eThread);
    void Create_BoundingBox(void) { }
    virtual void Update(void);
    void Render(CShader::E_RENDER_MODE _eMode);

    void OnTouchEvent(ITouchDelegate* _pDelegateOwner);
    void OnResourceLoadDoneEvent(IResource::E_RESOURCE_TYPE _eType, IResource* _pResource);

    void Set_NumParticles(unsigned int _iNumParticles) { m_iNumParticles = _iNumParticles; }
    void Set_MinSize(glm::vec2 _vSize) { m_vMinSize = _vSize; }
    void Set_MaxSize(glm::vec2 _vSize) { m_vMaxSize = _vSize; }
    void Set_LifeTime(int _fTime) { m_iLifeTime = _fTime; }
};

#endif /* defined(__iGaia__CParticleEmitter__) */
