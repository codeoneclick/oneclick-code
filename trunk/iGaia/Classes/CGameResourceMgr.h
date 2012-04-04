//
//  CGameResourceMgr.h
//  iGaia
//
//  Created by sergey.sergeev on 2/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CGameResourceMgr_h
#define iGaia_CGameResourceMgr_h

#include <stdlib.h>
#include <map>

#include "IGameResource.h"
#include "CResourceTree.h"
#include "CResourceAnimal.h"
#include "CResourceOre.h"
#include "CResourceWood.h"
#include "CResourceFood.h"
#include "CResourceLeather.h"
#include "CResourceMana.h"
#include "CResourceSteel.h"
#include "CResourceCloth.h"

class CGameResourceMgr
{
public:
    enum E_RESOURCE_TYPE { E_RESOURCE_TYPE_TREE = 0, E_RESOURCE_TYPE_ANIMAL, E_RESOURCE_TYPE_ORE, E_RESOURCE_TYPE_WOOD, E_RESOURCE_TYPE_FOOD, E_RESOURCE_TYPE_LEATHER, E_RESOURCE_TYPE_MANA, E_RESOURCE_TYPE_STEEL, E_RESOURCE_TYPE_CLOTH };
private:
    std::map<E_RESOURCE_TYPE, IGameResource*> m_lContainer;
public:
    CGameResourceMgr(void);
    ~CGameResourceMgr(void);
    int Get_ResourceCountByType(E_RESOURCE_TYPE _eType);
    void Set_ResourceCountByType(E_RESOURCE_TYPE _eType, int _iCount);
    void Inc_ResourceCountByType(E_RESOURCE_TYPE _eType, int _iIncValue);
    void Dec_ResourceCountByType(E_RESOURCE_TYPE _eType, int _iDecValue);
    void Update(void);
};

#endif
