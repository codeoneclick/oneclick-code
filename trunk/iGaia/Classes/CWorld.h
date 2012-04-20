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
#include "CLevel.h"
#include "CSceneMgr.h"
#include "CCharacterControllerPlayer.h"

class CWorld
{
private:
    CBuildingMgr* m_pBuildingMgr;
    CGameResourceMgr* m_pGameResourceMgr;
    CGameCharaterControllerMgr* m_pCharaterControllerMgr;
    CLevel* m_pLevel;
    CCharacterControllerPlayer* m_pCharacterControllerPlayer;
    ICamera* m_pCamera;
    ILight* m_pLight;
    bool m_bIsHeroUnderControl;
    static CWorld* m_pInstance;
public:
    CWorld(void);
    ~CWorld(void);
    CLevel* Get_Level(void) { return m_pLevel; }
    CGameCharaterControllerMgr* Get_GameCharaterControllerMgr(void) { return m_pCharaterControllerMgr; }
    CCharacterControllerPlayer* Get_PlayerCharacterController(void) { return m_pCharacterControllerPlayer; }
    void Load(void);
    void Update(void);
    static CWorld* Instance(void);
};

#endif
