//
//  CResourceLeather.h
//  gEngine
//
//  Created by sergey.sergeev on 2/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CResourceLeather_h
#define gEngine_CResourceLeather_h

#include "IGameResource.h"

class CResourceLeather : public IGameResource
{
public:
    CResourceLeather(void);
    ~CResourceLeather(void);
    virtual void Update(void);
};

#endif
