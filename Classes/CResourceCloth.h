//
//  CResourceCloth.h
//  gEngine
//
//  Created by sergey.sergeev on 2/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CResourceCloth_h
#define gEngine_CResourceCloth_h

#include "IGameResource.h"

class CResourceCloth : public IGameResource
{
public:
    CResourceCloth(void);
    ~CResourceCloth(void);
    virtual void Update(void);
};

#endif
