//
//  CBullet.h
//  iGaia
//
//  Created by sergey sergeev on 5/25/12.
//
//

#ifndef __iGaia__CBullet__
#define __iGaia__CBullet__

#include <iostream>
#include "CSceneMgr.h"

class CBullet
{
protected:
    glm::vec3 m_vPosition;
    glm::vec3 m_vRotation;
    CParticleEmitterFireTrail* m_pFireEmmiter;
    CParticleEmitter* m_pExplosionEmitter;
    INode* m_pModel;
    glm::vec3 m_vStartPoint;
    glm::vec3 m_vEndPoint;
    float m_fMoveSpeed;
    bool m_bIsDestroyed;
    void _MoveForward(void);
    void _SelfDestroy(void);
public:
    CBullet(void);
    ~CBullet(void);
    void Load(void);
    void Update(void);
    
    void Set_Position(const glm::vec3& _vPosition);
    glm::vec3 Get_Position(void) { return m_vPosition; }
    
    void Set_Rotation(const glm::vec3& _vRotation);
    glm::vec3 Get_Rotation(void) { return m_vRotation; }
    
    bool Get_Destroyed(void) { return m_bIsDestroyed; }
    
    void Set_StartPoint(const glm::vec3& _vPoint) { m_vStartPoint = _vPoint; }
    void Set_EndPoint(const glm::vec3& _vPoint) { m_vEndPoint = _vPoint; }
};

#endif /* defined(__iGaia__CBullet__) */
