//
//  CBuildingTemple.h
//  iGaia
//
//  Created by sergey.sergeev on 2/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CBuildingTemple_h
#define iGaia_CBuildingTemple_h

#include "IBuilding.h"
class CBuildingTample : public IBuilding
{
public:
    CBuildingTample(void);
    ~CBuildingTample(void);
    virtual void Load(void);
    virtual void Update(void);
};


#endif
