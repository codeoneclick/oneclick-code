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
#include "CSceneMgr.h"
#include "IDelegate.h"
#include "CLandscape.h"
#include <time.h>

class ICharacterController : public IDelegate
{
public:
    enum E_CHARACTER_CONTROLLER_STATE { E_CHARACTER_CONTROLLER_STATE_NONE = 0, E_CHARACTER_CONTROLLER_STATE_INC_MOVE, E_CHARACTER_CONTROLLER_STATE_DEC_MOVE };
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
public:
    ICharacterController(void);
    ~ICharacterController(void);
    virtual void Load(void) = 0;
    virtual void Update(void) = 0;
    virtual void Set_Position(const glm::vec3& _vPosition) = 0;
    virtual void Set_Rotation(const glm::vec3& _vRotation) = 0;
    glm::vec3 Get_Position(void) { return m_vPosition; }
    glm::vec3 Get_Rotation(void) { return m_vRotation; }
    virtual void Set_Light(ILight* _pLight) = 0;
    void MoveForward(void);
    void MoveBackward(void);
    void SteerRight(void);
    void SteerLeft(void);
};


#endif
