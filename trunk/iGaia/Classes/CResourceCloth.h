//
//  CResourceCloth.h
//  iGaia
//
//  Created by sergey.sergeev on 2/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CResourceCloth_h
#define iGaia_CResourceCloth_h

#include "IGameResource.h"

class CResourceCloth : public IGameResource
{
public:
    CResourceCloth(void);
    ~CResourceCloth(void);
    virtual void Update(void);
};

#endif
