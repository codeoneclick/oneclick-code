//
//  IAnimator.h
//  gEngine
//
//  Created by sergey.sergeev on 2/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_IAnimator_h
#define gEngine_IAnimator_h
#include "IAnimatorDelegate.h"
#include "INode.h"

class IAnimator
{
protected:
    IAnimatorDelegate* m_pAnimatorDelegateOwner;
    INode* m_pNode;
    bool m_bIsAnimated;
public:
    IAnimator(void);
    ~IAnimator(void);
    virtual void Start(void) = 0;
    virtual void Stop(void) = 0;
    virtual void Update(void) = 0;
};

#endif
