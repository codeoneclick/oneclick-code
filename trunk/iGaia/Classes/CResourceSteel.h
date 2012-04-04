//
//  CResourceSteel.h
//  iGaia
//
//  Created by sergey.sergeev on 2/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CResourceSteel_h
#define iGaia_CResourceSteel_h

#include "IGameResource.h"

class CResourceSteel : public IGameResource
{
public:
    CResourceSteel(void);
    ~CResourceSteel(void);
    virtual void Update(void);
};

#endif
