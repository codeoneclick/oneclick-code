//
//  CGameUnitMonk.h
//  iGaia
//
//  Created by sergey.sergeev on 2/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CGameUnitMonk_h
#define iGaia_CGameUnitMonk_h

#include "IGameUnit.h"
#include "IAnimatorDelegate.h"
#include "CLandscape.h"

class CGameUnitMonk : public IGameUnit, IAnimatorDelegate
{
public:
    CGameUnitMonk(void);
    ~CGameUnitMonk(void);
    virtual void Load(void);
    virtual void Update(void);
    virtual void OnTouchEvent(IDelegate* _pDelegateOwner);
    virtual void OnAnimatorDone(IAnimator* _pAnimator);
    virtual void OnAnimatorRemove(IAnimator* _pAnimator);
};


#endif
