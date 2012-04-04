//
//  CBuildingHunter.h
//  iGaia
//
//  Created by sergey.sergeev on 2/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CBuildingHunter_h
#define iGaia_CBuildingHunter_h

#include "IBuilding.h"
class CBuildingHunter : public IBuilding
{
public:
    CBuildingHunter(void);
    ~CBuildingHunter(void);
    virtual void Load(void);
    virtual void Update(void);
};

#endif
