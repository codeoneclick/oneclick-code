//
//  IAnimatorDelegate.h
//  gEngine
//
//  Created by sergey.sergeev on 2/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_IAnimatorDelegate_h
#define gEngine_IAnimatorDelegate_h

class IAnimatorDelegate
{
public:
    IAnimatorDelegate(void);
    ~IAnimatorDelegate(void);
    virtual void OnAnimatorDone(IAnimatorDelegate* _pAnimatorDelegateOwner) = 0;
};


#endif
