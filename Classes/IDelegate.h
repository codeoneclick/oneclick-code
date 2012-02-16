//
//  IDelegate.h
//  gEngine
//
//  Created by sergey.sergeev on 2/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_IDelegate_h
#define gEngine_IDelegate_h

class IDelegate
{
public:
    IDelegate(void);
    ~IDelegate(void);
    virtual void OnTouchEvent(IDelegate* _pDelegateOwner) = 0;
};

#endif
