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
    E_AI_STATE m_eState;
    long m_iAIStateDuration;
    long m_iAIStateTimeStamp;
    glm::vec3 m_vTargetPoint;
    glm::vec3 m_vMoveDirection;
    
    long _Get_TimeStamp(void);
    bool _IsStateTimeElapsed(void);
    
    bool _MoveForwardAI(void);
    bool _MoveBackwardAI(void);
    bool _SteerRightAI(void);
    bool _SteerLeftAI(void);

public:
    CCharacterControllerEnemy(void);
    ~CCharacterControllerEnemy(void);
    void Load(void);
    void Update(void);
    INode* Get_TargetForCamera(void) { return m_pBodyModel; }
    void Set_AIState(E_AI_STATE _eState, long _iAIStateDuration);
    E_AI_STATE Get_AIState(void) { return m_eState; }
    void Set_AITargetPoint(glm::vec3 _vPoint) { m_vTargetPoint = _vPoint; }
    
    void OnTouchEvent(ITouchDelegate* _pDelegateOwner);
};

#endif /* defined(__iGaia__CCharaterControllerEnemy__) */
