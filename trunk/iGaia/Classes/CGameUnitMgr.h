//
//  CGameUnitMgr.h
//  iGaia
//
//  Created by sergey.sergeev on 2/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CGameUnitMgr_h
#define iGaia_CGameUnitMgr_h


#include <stdlib.h>
#include <map>
#include <vector>

#include "IGameUnit.h"
#include "CGameUnitHero.h"

class CGameUnitMgr
{
public:
    enum E_UNIT_TYPE { E_UNIT_TYPE_HERO = 0, E_UNIT_TYPE_WORKER};
private:
    std::map<E_UNIT_TYPE, IGameUnit*> m_lContainer;
public:
    CGameUnitMgr(void);
    ~CGameUnitMgr(void);
    void Add_Unit(E_UNIT_TYPE _eType);
    void Remove_Unit(E_UNIT_TYPE _eType);
    IGameUnit* Get_Unit(E_UNIT_TYPE _eType);
    void Update(void);
};

#endif
