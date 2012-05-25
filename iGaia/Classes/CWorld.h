//
//  CWorld.h
//  iGaia
//
//  Created by sergey.sergeev on 2/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CWorld_h
#define iGaia_CWorld_h

#include "CBuildingMgr.h"
#include "CGameResourceMgr.h"
#include "CGameCharaterControllerMgr.h"
#include "CGameAIMgr.h"
#include "CLevel.h"
#include "CSceneMgr.h"
#include "CCharacterControllerPlayer.h"
#include "CGameShooterMgr.h"

#define k_CAMERA_DISTANCE_MODE_1 7.0f
#define k_CAMERA_DISTANCE_MODE_2 7.0f
#define k_CAMERA_HEIGHT_MODE_1 4.0f
#define k_CAMERA_HEIGHT_MODE_2 14.0f
#define k_CAMERA_DISPLACE_INC 0.5f

class CWorld
{
public:
    enum E_CAMERA_MODE { E_CAMERA_MODE_1 = 0, E_CAMERA_MODE_2 };
private:
    CBuildingMgr* m_pBuildingMgr;
    CGameResourceMgr* m_pGameResourceMgr;
    CGameCharaterControllerMgr* m_pCharaterControllerMgr;
    CGameShooterMgr* m_pGameShooterMgr;
    CGameAIMgr* m_pGameAIMgr;
    CLevel* m_pLevel;
    CCharacterControllerPlayer* m_pCharacterControllerPlayer;
    ICamera* m_pCamera;
    ILight* m_pLight;
    bool m_bIsHeroUnderControl;
    static CWorld* m_pInstance;
    E_CAMERA_MODE m_eCameraMode;
    unsigned int m_iCurrentCameraDistance;
    float m_iCurrentCameraHeight;
public:
    CWorld(void);
    ~CWorld(void);
    CLevel* Get_Level(void) { return m_pLevel; }
    CGameCharaterControllerMgr* Get_GameCharaterControllerMgr(void) { return m_pCharaterControllerMgr; }
    CGameAIMgr* Get_GameAIMgr(void) { return m_pGameAIMgr; }
    CGameShooterMgr* Get_GameShooterMgr(void) { return m_pGameShooterMgr; }
    CCharacterControllerPlayer* Get_PlayerCharacterController(void) { return m_pCharacterControllerPlayer; }
    void SwitchCameraModeToNext(void);
    void SwitchCameraMode(E_CAMERA_MODE _eCameraMode);
    void Load(void);
    void Update(void);
    static CWorld* Instance(void);
};

#endif
