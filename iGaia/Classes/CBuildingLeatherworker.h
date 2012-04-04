//
//  CBuildingLeatherworker.h
//  iGaia
//
//  Created by sergey.sergeev on 2/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CBuildingLeatherworker_h
#define iGaia_CBuildingLeatherworker_h

#include "IBuilding.h"
class CBuildingLeatherworker : public IBuilding
{
public:
    CBuildingLeatherworker(void);
    ~CBuildingLeatherworker(void);
    virtual void Load(void);
    virtual void Update(void);
};

#endif
