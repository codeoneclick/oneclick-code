//
//  CBuildingFarmer.h
//  gEngine
//
//  Created by sergey.sergeev on 2/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CBuildingFarmer_h
#define gEngine_CBuildingFarmer_h

#include "IBuilding.h"
class CBuildingFarmer : public IBuilding
{
public:
    CBuildingFarmer(void);
    ~CBuildingFarmer(void);
    virtual void Load(void);
    virtual void Update(void);
};

#endif
