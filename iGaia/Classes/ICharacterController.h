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
#include "ITouchDelegate.h"
#include "CLandscape.h"
#include "CMathHelper.h"
#include <time.h>

#define k_MIN_HEIGHTMAP_VALUE -8.0f
#define k_EXHAUST_EMITTER_OFFSET  1.5f
#define k_EXHAUST_EMITTER_HEIGHT  1.5f
#define k_CROSS_FIRE_OFFSET 1.5f
#define k_CROSS_FIRE_HEIGHT 0.75f

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
    
    
    CModel* m_pBodyModel;
    CModel* m_pTowerModel;
    CModel* m_pLeftTrackModel;
    CModel* m_pRightTrackModel;
    
    CParticleEmitter* m_pExhaustSmokeEmitter;
    CDecal* m_pShadowDecal;
    CSpriteCross* m_pFireCross;
    
    CParticleEmitter* m_pLeftTrackSmokeEmitter;
    CParticleEmitter* m_pRightTrackSmokeEmitter;
    CParticleEmitter* m_pBodySmokeEmitter;
    
    CParticleEmitter* m_pLeftTrackFireEmitter;
    CParticleEmitter* m_pRightTrackFireEmitter;
    CParticleEmitter* m_pBodyFireEmitter;
    
    glm::vec3 m_vLeftTrackEmitterNodePosition;
    glm::vec3 m_vRightTrackEmitterNodePosition;
    glm::vec3 m_vBodyEmitterNodePosition;
    
    glm::vec3 m_vExhaustEmitterPosition;
    glm::vec3 m_vFireCrossEffectPosition;
    
    glm::vec4 m_vTransformHelper;
    glm::mat4x4 m_mRotationHelper;

public:
    ICharacterController(void);
    ~ICharacterController(void);
    virtual void Load(void) = 0;
    virtual void Update(void) = 0;
    virtual void Set_Position(const glm::vec3& _vPosition);
    virtual void Set_Rotation(const glm::vec3& _vRotation);
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