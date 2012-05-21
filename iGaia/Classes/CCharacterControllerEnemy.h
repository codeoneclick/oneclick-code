//
//  CCharacterControllerEnemy.h
//  iGaia
//
//  Created by code_oneclick on 4/20/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef __iGaia__CCharacterControllerEnemy__
#define __iGaia__CCharacterControllerEnemy__

#include <iostream>
#include "ICharacterController.h"

class CCharacterControllerEnemy : public ICharacterController
{
public:
    enum E_AI_STATE { E_AI_STATE_NONE = 0, E_AI_STATE_STAND, E_AI_STATE_MOVE, E_AI_STATE_CHASE, E_AI_STATE_CHASE_ATTACK, E_AI_STATE_BACK, E_AI_STATE_BACK_ATTACK };
protected:
    CModel* m_pBodyModel;
    CModel* m_pTowerModel;
    CModel* m_pLeftTrackModel;
    CModel* m_pRightTrackModel;
    E_AI_STATE m_eState;
    long m_iAIStateDuration;
    long m_iAIStateTimeStamp;
    glm::vec3 m_vTargetPoint;
    
    long _Get_TimeStamp(void);
    bool _IsStateTimeElapsed(void);
public:
    CCharacterControllerEnemy(void);
    ~CCharacterControllerEnemy(void);
    virtual void Load(void);
    virtual void Update(void);
    virtual void Set_Position(const glm::vec3& _vPosition);
    virtual void Set_Rotation(const glm::vec3& _vRotation);
    INode* Get_TargetForCamera(void) { return m_pBodyModel; }
    void Set_AIState(E_AI_STATE _eState, long _iAIStateDuration);
    E_AI_STATE Get_AIState(void) { return m_eState; }
    void Set_AITargetPoint(glm::vec3 _vPoint) { m_vTargetPoint = _vPoint; }
    
    virtual void OnTouchEvent(ITouchDelegate* _pDelegateOwner);
};

#endif /* defined(__iGaia__CCharaterControllerEnemy__) */
