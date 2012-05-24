//
//  CCharacterControllerMain.h
//  iGaia
//
//  Created by sergey.sergeev on 2/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CCharacterControllerPlayer_h
#define iGaia_CCharacterControllerPlayer_h

#include "ICharacterController.h"
#include "CParticleEmitter.h"
#include "CDecal.h"

class CCharacterControllerPlayer : public ICharacterController
{
protected:
    CModel* m_pBodyModel;
    CModel* m_pTowerModel;
    CModel* m_pLeftTrackModel;
    CModel* m_pRightTrackModel;
    glm::vec3 m_vTowerModelTarget;
    E_CHARACTER_CONTROLLER_STATE m_eLeftTrackState;
    E_CHARACTER_CONTROLLER_STATE m_eRightTrackState;
    float m_fLeftTrackMoveOffset;
    float m_fRightTrackMoveOffset;
    CParticleEmitter* m_pExplosionEmitter;
    CDecal* m_pShadowDecal;
public:
    CCharacterControllerPlayer(void);
    ~CCharacterControllerPlayer(void);
    virtual void Load(void);
    virtual void Update(void);
    virtual void Set_Position(const glm::vec3& _vPosition);
    virtual void Set_Rotation(const glm::vec3& _vRotation);
    INode* Get_TargetForCamera(void) { return m_pBodyModel; }
    void Set_LeftTrackMoveOffset(float _fOffset) { m_fLeftTrackMoveOffset = _fOffset; }
    void Set_RightTrackMoveOffset(float _fOffset) { m_fRightTrackMoveOffset = _fOffset; }
    void Set_LeftTrackState(E_CHARACTER_CONTROLLER_STATE _eState) { m_eLeftTrackState = _eState; }
    void Set_RightTrackState(E_CHARACTER_CONTROLLER_STATE _eState) { m_eRightTrackState = _eState; }
    
    virtual void OnTouchEvent(ITouchDelegate* _pDelegateOwner);
};

#endif