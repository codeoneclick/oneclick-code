//
//  CGameUnitHero.h
//  gEngine
//
//  Created by sergey.sergeev on 2/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CGameUnitHero_h
#define gEngine_CGameUnitHero_h

#include "IGameUnit.h"
class CGameUnitHero : public IGameUnit
{
public:
    CGameUnitHero(void);
    ~CGameUnitHero(void);
    virtual void Load(void);
    virtual void Update(void);
    virtual void OnTouchEvent(IDelegate* _pDelegateOwner);
};

#endif
