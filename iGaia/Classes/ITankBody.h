//
//  ITankBody.h
//  iGaia
//
//  Created by sergey sergeev on 7/2/12.
//
//

#ifndef __iGaia__ITankBody__
#define __iGaia__ITankBody__

#include <iostream>
#include "ITankPart.h"

class ITankBody : public ITankPart
{
protected:
    CModel* m_pBodyModel;
    
    CParticleEmitterFire* m_pBodySmokeEmitter;
    CParticleEmitterFire* m_pBodyFireEmitter;
    
    CParticleEmitter* m_pLeftExhaustSmokeEmitter;
    CParticleEmitter* m_pRightExhaustSmokeEmitter;
    
    float m_fBodyCurrentHealth;
    float m_fBodyTotalHealth;
    
public:
    ITankBody(void);
    virtual ~ITankBody(void);
    
    virtual void Load(void);
    virtual void Update(void);
    
    void Set_BodyHealth(float _fHealth);
    float Get_BodyHealth(void);
    
    void Set_Position(const glm::vec3& _vPosition);
    void Set_Rotation(const glm::vec3& _vRotation);
};

#endif /* defined(__iGaia__ITankBody__) */
