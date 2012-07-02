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
#include "CTankLightTrack.h"
#include <time.h>

#define k_MIN_HEIGHTMAP_VALUE -8.0f
#define k_EXHAUST_EMITTER_OFFSET_X  0.25f
#define k_EXHAUST_EMITTER_OFFSET_Z  1.1f
#define k_EXHAUST_EMITTER_HEIGHT  0.75f
#define k_CROSS_FIRE_OFFSET 1.5f
#define k_CROSS_FIRE_HEIGHT 0.75f
#define k_TRACK_EMITTER_HEIGHT 0.66f
#define k_TOWER_EMITTER_HEIGHT 0.75f

#define k_CROSS_FIRE_TIME_MAX 1000

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
    float _GetRotationBetweenPointsDot(glm::vec2 _vPoint_01, glm::vec2 _vPoint_02);
    
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
    
    int m_iLastCrossFireTime;
    
    CModel* m_pBodyModel;
    CModel* m_pTowerModel;
    ITankTrack* m_pTrack;
    
    //CModel* m_pLeftTrackModel;
    //CModel* m_pRightTrackModel;
    
    CParticleEmitter* m_pLeftExhaustSmokeEmitter;
    CParticleEmitter* m_pRightExhaustSmokeEmitter;
    CDecal* m_pShadowDecal;
    CDecal* m_pHealthDecal;
    CSpriteCross* m_pFireCross;
    
    //CParticleEmitter* m_pLeftTrackSmokeEmitter;
    //CParticleEmitter* m_pRightTrackSmokeEmitter;
    CParticleEmitter* m_pTowerSmokeEmitter;
    
    //CParticleEmitter* m_pLeftTrackFireEmitter;
    //CParticleEmitter* m_pRightTrackFireEmitter;
    CParticleEmitter* m_pTowerFireEmitter;
    
    //glm::vec3 m_vLeftTrackEmitterNodePosition;
    //glm::vec3 m_vRightTrackEmitterNodePosition;
    glm::vec3 m_vTowerEmitterNodePosition;
    
    glm::vec3 m_vLeftExhaustEmitterPosition;
    glm::vec3 m_vRightExhaustEmitterPosition;
    glm::vec3 m_vFireCrossEffectPosition;
    
    glm::vec4 m_vTransformHelper;
    glm::mat4x4 m_mRotationHelper;
    
    ICharacterController* m_pTarget;
    
    inline float _Get_WrapAngle(float _fValue, float _fMin, float _fMax)
    {
        float fDistance = _fMax - _fMin;
        float fTimes = static_cast<float>(floorf((_fValue - _fMin) / fDistance));
        return _fValue - (fTimes * fDistance);
    }
    void _SmoothRotation(void);
public:
    ICharacterController(void);
    ~ICharacterController(void);
    
    virtual void Load(void) = 0;
    virtual void Update(void) = 0;
    
    void Set_Position(const glm::vec3& _vPosition);
    void Set_Rotation(const glm::vec3& _vRotation);
    
    glm::vec3 Get_Position(void) { return m_vPosition; }
    glm::vec3 Get_Rotation(void) { return m_vRotation; }
    
    virtual bool MoveForward(void);
    virtual bool MoveBackward(void);
    virtual void SteerRight(void);
    virtual void SteerLeft(void);
    
    virtual void Shoot(void);
    
    void Set_MoveState(E_CHARACTER_CONTROLLER_MOVE_STATE _eMoveState) { m_eMoveState = _eMoveState; }
    void Set_SteerState(E_CHARACTER_CONTROLLER_STEER_STATE _eSteerState) { m_eSteerState = _eSteerState; }
    void Set_SteerTowerState(E_CHARACTER_CONTROLLER_STEER_TOWER_STATE _eSteerTowerState) { m_eSteerTowerState = _eSteerTowerState; }
    
    virtual void OnTouchEvent(ITouchDelegate* _pDelegateOwner) = 0;
    void Set_Target(ICharacterController* _pTarget) { m_pTarget = _pTarget; }
    ICharacterController* Get_Target(void) { return m_pTarget; }
};


#endif
