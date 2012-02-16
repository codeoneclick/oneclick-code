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
#include "CSceneMgr.h"
#include "CLandscape.h"

class CWorld
{
private:
    CBuildingMgr* m_pBuildingMgr;
    CGameResourceMgr* m_pGameResourceMgr;
    CGameUnitMgr* m_pGameUnitMgr;
    CLandscape* m_pLandscape;
    CGameUnitHero* m_pHero;
    ICamera* m_pCamera;
    ILight* m_pLight;
    static CWorld* m_pInstance;
public:
    CWorld(void);
    ~CWorld(void);
    void Load(void);
    void Update(void);
    static CWorld* Instance(void);
};

#endif
