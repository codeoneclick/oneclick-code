//
//  CResourceMana.h
//  gEngine
//
//  Created by sergey.sergeev on 2/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CResourceMana_h
#define gEngine_CResourceMana_h

#include "IGameResource.h"

class CResourceMana : public IGameResource
{
public:
    CResourceMana(void);
    ~CResourceMana(void);
    virtual void Update(void);
};

#endif
