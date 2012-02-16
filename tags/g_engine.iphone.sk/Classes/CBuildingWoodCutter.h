//
//  CBuildingWoodCutter.h
//  gEngine
//
//  Created by sergey.sergeev on 2/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CBuildingWoodCutter_h
#define gEngine_CBuildingWoodCutter_h

#include "IBuilding.h"
class CBuildingWoodCutter : public IBuilding
{
public:
    CBuildingWoodCutter(void);
    ~CBuildingWoodCutter(void);
    virtual void Load(void);
    virtual void Update(void);
};

#endif
