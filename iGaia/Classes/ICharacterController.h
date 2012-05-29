//
//  ICharacterController.h
//  iGaia
//
//  Created by sergey.sergeev on 2/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_ICharacterController_h
#define iGaia_ICharacterController_h

#include "CModel.h"
#include "CShadowPlane.h"
#include "CSceneMgr.h"
#include "ITouchDelegate.h"
#include "CLandscape.h"
#include <time.h>

class ICharacterController : public ITouchDelegate
{
public:
    enum E_CHARACTER_CONTROLLER_STATE { E_CHARACTER_CONTROLLER_STATE_NONE = 0, E_CHARACTER_CONTROLLER_STATE_INC_MOVE, E_CHARACTER_CONTROLLER_STATE_DEC_MOVE };
    enum E_CHARACTER_CONTROLLER_MOVE_STATE { E_CHARACTER_CONTROLLER_MOVE_STATE_NONE = 0, E_CHARACTER_CONTROLLER_MOVE_STATE_FORWARD, E_CHARACTER_CONTROLLER_MOVE_STATE_BACKWARD };
    enum E_CHARACTER_CONTROLLER_STEER_STATE { E_CHARACTER_CONTROLLER_STEER_STATE_NONE = 0, E_CHARACTER_CONTROLLER_STEER_STATE_LEFT, E_CHARACTER_CONTROLLER_STEER_STATE_RIGHT };
    enum E_CHARACTER_CONTROLLER_STEER_TOWER_STATE { E_CHARACTER_CONTROLLER_STEER_STATE_TOWER_NONE = 0, E_CHARACTER_CONTROLLER_STEER_STATE_TOWER_LEFT, E_CHARACTER_CONTROLLER_STEER_STATE_TOWER_RIGHT };
protected:
    glm::vec3 m_vPosition;
    glm::vec3 m_vRotation;
    float _Get_RotationForPlane(glm::vec3 _vPoint_01, glm::vec3 _vPoint_02, glm::vec3 _vPoint_03);
    glm::vec2 _Get_RotationOnHeightmap(glm::vec3 _vPosition);
    float _GetRotationBetweenPoints(glm::vec3 _vPoint_01, glm::vec3 _vPoint_02);
    float m_fMaxMoveSpeed;
    float m_fMoveAcceleration;
    float m_fLeftTrackMoveSpeed;
    float m_fRightTrackMoveSpeed;
    float m_fMoveSpeed;
    float m_fSteerSpeed;
    float m_fTowerSteerSpeed;
    float m_fTowerRotationY;
    E_CHARACTER_CONTROLLER_MOVE_STATE m_eMoveState;
    E_CHARACTER_CONTROLLER_STEER_STATE m_eSteerState;
    E_CHARACTER_CONTROLLER_STEER_TOWER_STATE m_eSteerTowerState;
public:
    ICharacterController(void);
    ~ICharacterController(void);
    virtual void Load(void) = 0;
    virtual void Update(void) = 0;
    virtual void Set_Position(const glm::vec3& _vPosition) = 0;
    virtual void Set_Rotation(const glm::vec3& _vRotation) = 0;
    glm::vec3 Get_Position(void) { return m_vPosition; }
    glm::vec3 Get_Rotation(void) { return m_vRotation; }
    bool MoveForward(void);
    bool MoveBackward(void);
    bool SteerRight(void);
    bool SteerLeft(void);
    void Set_MoveState(E_CHARACTER_CONTROLLER_MOVE_STATE _eMoveState) { m_eMoveState = _eMoveState; }
    void Set_SteerState(E_CHARACTER_CONTROLLER_STEER_STATE _eSteerState) { m_eSteerState = _eSteerState; }
    void Set_SteerTowerState(E_CHARACTER_CONTROLLER_STEER_TOWER_STATE _eSteerTowerState) { m_eSteerTowerState = _eSteerTowerState; }
    
    virtual void OnTouchEvent(ITouchDelegate* _pDelegateOwner) = 0;
};


#endif
