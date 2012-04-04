//
//  CResourceWood.h
//  iGaia
//
//  Created by sergey.sergeev on 2/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CResourceWood_h
#define iGaia_CResourceWood_h

#include "IGameResource.h"

class CResourceWood : public IGameResource
{
public:
    CResourceWood(void);
    ~CResourceWood(void);
    virtual void Update(void);
};

#endif
