//
//  IGameScene.h
//  iGaia
//
//  Created by sergey sergeev on 7/4/12.
//
//

#ifndef __iGaia__IGameScene__
#define __iGaia__IGameScene__

#include "CGameCharaterControllerMgr.h"
#include "CGameAIMgr.h"
#include "ILevel.h"
#include "CSceneMgr.h"
#include "CCharacterControllerPlayer.h"
#include "CGameShooterMgr.h"

class IGameScene
{
protected:
    CGameCharaterControllerMgr* m_pCharaterControllerMgr;
    CGameShooterMgr* m_pGameShooterMgr;
    CGameAIMgr* m_pGameAIMgr;
    ILevel* m_pLevel;
    CCharacterControllerPlayer* m_pCharacterControllerPlayer;
    ICamera* m_pCamera;
    ILight* m_pLight;
public:
    IGameScene(void);
    virtual ~IGameScene(void);
    ILevel* Get_Level(void) { return m_pLevel; }
    CGameCharaterControllerMgr* Get_GameCharaterControllerMgr(void) { return m_pCharaterControllerMgr; }
    CGameAIMgr* Get_GameAIMgr(void) { return m_pGameAIMgr; }
    CGameShooterMgr* Get_GameShooterMgr(void) { return m_pGameShooterMgr; }
    CCharacterControllerPlayer* Get_PlayerCharacterController(void) { return m_pCharacterControllerPlayer; }
    virtual void Load(void);
    virtual void Unload(void);
    virtual void Update(void);
};

#endif /* defined(__iGaia__IGameScene__) */
