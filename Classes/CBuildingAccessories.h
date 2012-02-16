//
//  CBuildingAccessories.h
//  gEngine
//
//  Created by sergey.sergeev on 2/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CBuildingAccessories_h
#define gEngine_CBuildingAccessories_h

#include "IBuilding.h"
class CBuildingAccessories : public IBuilding
{
public:
    CBuildingAccessories(void);
    ~CBuildingAccessories(void);
    virtual void Load(void);
    virtual void Update(void);
};


#endif
