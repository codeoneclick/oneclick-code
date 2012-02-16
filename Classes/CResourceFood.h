//
//  CResourceFood.h
//  gEngine
//
//  Created by sergey.sergeev on 2/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CResourceFood_h
#define gEngine_CResourceFood_h

#include "IGameResource.h"

class CResourceFood : public IGameResource
{
public:
    CResourceFood(void);
    ~CResourceFood(void);
    virtual void Update(void);
};

#endif
