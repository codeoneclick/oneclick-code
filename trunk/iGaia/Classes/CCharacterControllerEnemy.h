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
protected:
    CModel* m_pBodyModel;
    CModel* m_pTowerModel;
    CModel* m_pLeftTrackModel;
    CModel* m_pRightTrackModel;
    E_CHARACTER_CONTROLLER_STATE m_eLeftTrackState;
    E_CHARACTER_CONTROLLER_STATE m_eRightTrackState;
public:
    CCharacterControllerEnemy(void);
    ~CCharacterControllerEnemy(void);
    virtual void Load(void);
    virtual void Update(void);
    virtual void OnTouchEvent(IDelegate* _pDelegateOwner);
    virtual void OnPhysicEvent(INode* _pNode, glm::vec3 _vPosition, glm::vec3 _vRotation, glm::vec3 _vScale);
    virtual void Set_Position(const glm::vec3& _vPosition);
    virtual void Set_Rotation(const glm::vec3& _vRotation);
    virtual void Set_Light(ILight* _pLight);
    INode* Get_TargetForCamera(void) { return m_pBodyModel; }
    void Set_LeftTrackState(E_CHARACTER_CONTROLLER_STATE _eState) { m_eLeftTrackState = _eState; }
    void Set_RightTrackState(E_CHARACTER_CONTROLLER_STATE _eState) { m_eRightTrackState = _eState; }
};

#endif /* defined(__iGaia__CCharaterControllerEnemy__) */
