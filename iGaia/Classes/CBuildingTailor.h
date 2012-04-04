//
//  CBuildingTailor.h
//  iGaia
//
//  Created by sergey.sergeev on 2/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CBuildingTailor_h
#define iGaia_CBuildingTailor_h

#include "IBuilding.h"
class CBuildingTailor : public IBuilding
{
public:
    CBuildingTailor(void);
    ~CBuildingTailor(void);
    virtual void Load(void);
    virtual void Update(void);
};

#endif
