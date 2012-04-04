//
//  CBuildingBlacksmith.h
//  iGaia
//
//  Created by sergey.sergeev on 2/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CBuildingBlacksmith_h
#define iGaia_CBuildingBlacksmith_h

#include "IBuilding.h"
class CBuildingBlacksmith : public IBuilding
{
public:
    CBuildingBlacksmith(void);
    ~CBuildingBlacksmith(void);
    virtual void Load(void);
    virtual void Update(void);
};


#endif
