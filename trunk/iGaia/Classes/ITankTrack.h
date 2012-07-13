//
//  ITankTrack.h
//  iGaia
//
//  Created by sergey sergeev on 7/2/12.
//
//

#ifndef __iGaia__ITankTrack__
#define __iGaia__ITankTrack__

#include <iostream>
#include "ITankPart.h"

class ITankTrack : public ITankPart
{
protected:
    CModel* m_pLeftTrack;
    CModel* m_pRightTrack;
    
    CParticleEmitterFire* m_pLeftTrackSmokeEmitter;
    CParticleEmitterFire* m_pRightTrackSmokeEmitter;
    
    CParticleEmitterFire* m_pLeftTrackFireEmitter;
    CParticleEmitterFire* m_pRightTrackFireEmitter;
    
    float m_fLeftTrackCurrentHealth;
    float m_fRightTrackCurrentHealth;
    
    float m_fLeftTrackTotalHealth;
    float m_fRightTrackTotalHealth;
    
    glm::vec3 m_vLeftTrackEmitterOffset;
    glm::vec3 m_vRightTrackEmitterOffset;
    
    float m_fLeftTrackMoveOffset;
    float m_fRightTrackMoveOffset;
    
    glm::vec3 m_vLeftTrackMaxBound;
    glm::vec3 m_vLeftTrackMinBound;
    glm::vec3 m_vLeftTrackCenterBound;
    
    glm::vec3 m_vRightTrackMaxBound;
    glm::vec3 m_vRightTrackMinBound;
    glm::vec3 m_vRightTrackCenterBound;
    
public:
    ITankTrack(void);
    virtual ~ITankTrack(void);
    
    virtual void Load(void);
    virtual void Update(void);
    
    void Move_LeftTrack(float _fDelta);
    void Move_RightTrack(float _fDelta);
    
    void Set_LeftTrackHealth(float _fHealth);
    float Get_LeftTrackHealth(void);
    
    void Set_RightTrackHealth(float _fHealth);
    float Get_RightTrackHealth(void);
    
    void Set_Position(const glm::vec3& _vPosition);
    void Set_Rotation(const glm::vec3& _vRotation);
    
    inline glm::vec3 Get_LeftTrackTowerMaxBound(void)    { return m_vLeftTrackMaxBound; }
    inline glm::vec3 Get_LeftTrackTowerMinBound(void)    { return m_vLeftTrackMinBound; }
    inline glm::vec3 Get_LeftTrackTowerCenterBound(void) { return m_vLeftTrackCenterBound; }
    
    inline glm::vec3 Get_RightTrackTowerMaxBound(void)    { return m_vRightTrackMaxBound; }
    inline glm::vec3 Get_RightTrackTowerMinBound(void)    { return m_vRightTrackMinBound; }
    inline glm::vec3 Get_RightTrackTowerCenterBound(void) { return m_vRightTrackCenterBound; }
};

#endif /* defined(__iGaia__ITankTrack__) */
