//
//  CBuildingMgr.h
//  iGaia
//
//  Created by sergey.sergeev on 2/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CBuildingMgr_h
#define iGaia_CBuildingMgr_h

#include <stdlib.h>
#include <map>

#include "IBuilding.h"
#include "CBuildingTemple.h"
#include "CBuildingWoodCutter.h"
#include "CBuildingMiner.h"
#include "CBuildingHunter.h"
#include "CBuildingTailor.h"
#include "CBuildingLeatherworker.h"
#include "CBuildingFarmer.h"
#include "CBuildingBlacksmith.h"

class CBuildingMgr
{
public:
    enum E_BUILDING_TYPE { E_BUILDING_TYPE_TEMPLE = 0, E_BUILDING_TYPE_WOODCUTTER, E_BUILDING_TYPE_MINER, E_BUILDING_TYPE_HUNTER, E_BUILDING_TYPE_TAILOR, E_BUILDING_TYPE_LETHERWORKER, E_BUILDING_TYPE_FARMER, E_BUILDING_TYPE_BLACKSMITH };
private:
    std::map<E_BUILDING_TYPE, IBuilding*> m_lContainer;
public:
    CBuildingMgr(void);
    ~CBuildingMgr(void);
    void Add_Building(E_BUILDING_TYPE _eType);
    void Remove_Building(E_BUILDING_TYPE _eType);
    IBuilding* Get_Building(E_BUILDING_TYPE _eType);
    void Update(void);
};

#endif
