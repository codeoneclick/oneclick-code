//
//  IAnimatorDelegate.h
//  iGaia
//
//  Created by sergey.sergeev on 2/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_IAnimatorDelegate_h
#define iGaia_IAnimatorDelegate_h

class IAnimator;

class IAnimatorDelegate
{
public:
    IAnimatorDelegate(void);
    ~IAnimatorDelegate(void);
    virtual void OnAnimatorDone(IAnimator* pAnimator) = 0;
    virtual void OnAnimatorRemove(IAnimator* pAnimator) = 0;
};


#endif
