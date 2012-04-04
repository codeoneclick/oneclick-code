//
//  CGameUnitHero.h
//  iGaia
//
//  Created by sergey.sergeev on 2/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CGameUnitHero_h
#define iGaia_CGameUnitHero_h

#include "IGameUnit.h"
#include "IAnimatorDelegate.h"
#include "CLandscape.h"

class CGameUnitHero : public IGameUnit, IAnimatorDelegate
{
public:
    CGameUnitHero(void);
    ~CGameUnitHero(void);
    virtual void Load(void);
    virtual void Update(void);
    virtual void OnTouchEvent(IDelegate* _pDelegateOwner);
    virtual void OnAnimatorDone(IAnimator* _pAnimator);
    virtual void OnAnimatorRemove(IAnimator* _pAnimator);
};

#endif
