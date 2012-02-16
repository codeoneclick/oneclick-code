//
//  CWorld.h
//  gEngine
//
//  Created by sergey.sergeev on 2/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CWorld_h
#define gEngine_CWorld_h

#include "CBuildingMgr.h"
#include "CGameResourceMgr.h"
#include "CGameUnitMgr.h"
#include "CLevel.h"
#include "CSceneMgr.h"

class CWorld
{
private:
    CBuildingMgr* m_pBuildingMgr;
    CGameResourceMgr* m_pGameResourceMgr;
    CGameUnitMgr* m_pGameUnitMgr;
    CLevel* m_pLevel;
    CGameUnitHero* m_pHero;
    ICamera* m_pCamera;
    ILight* m_pLight;
    static CWorld* m_pInstance;
public:
    CWorld(void);
    ~CWorld(void);
    CLevel* Get_Level(void) { return m_pLevel; }
    void Load(void);
    void Update(void);
    static CWorld* Instance(void);
};

#endif
