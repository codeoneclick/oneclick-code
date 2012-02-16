//
//  CBuildingMiner.h
//  gEngine
//
//  Created by sergey.sergeev on 2/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CBuildingMiner_h
#define gEngine_CBuildingMiner_h

#include "IBuilding.h"
class CBuildingMiner : public IBuilding
{
public:
    CBuildingMiner(void);
    ~CBuildingMiner(void);
    virtual void Load(void);
    virtual void Update(void);
};

#endif
