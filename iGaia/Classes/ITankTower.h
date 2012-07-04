//
//  ITankTower.h
//  iGaia
//
//  Created by sergey sergeev on 7/2/12.
//
//

#ifndef __iGaia__ITankTower__
#define __iGaia__ITankTower__

#include <iostream>
#include "ITankPart.h"

class ITankTower : public ITankPart
{
protected:
    CModel* m_pTower;
    
    CParticleEmitterFire* m_pTowerSmokeEmitter;
    CParticleEmitterFire* m_pTowerFireEmitter;
    
    float m_fTowerCurrentHealth;
    float m_fTowerTotalHealth;
    
    glm::vec3 m_vTowerEmitterOffset;
    glm::vec3 m_vTowerGunOffset;
    
public:
    ITankTower(void);
    virtual ~ITankTower(void);
    
    virtual void Load(void);
    virtual void Update(void);
    
    void Set_TowerHealth(float _fHealth);
    float Get_TowerHealth(void);
    
    glm::vec3 Get_TowerGunOffset(void) { return m_vTowerGunOffset; }
    
    void Set_Position(const glm::vec3& _vPosition);
    void Set_Rotation(const glm::vec3& _vRotation);
};

#endif /* defined(__iGaia__ITankTower__) */
