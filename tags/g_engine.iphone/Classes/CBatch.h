//
//  CBatch.h
//  gEngine
//
//  Created by sergey.sergeev on 10/25/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CBatch_h
#define gEngine_CBatch_h

#include "INode.h"

class CBatch : public INode
{
public:
    CBatch();
    ~CBatch();
    virtual void Update(float _fTime);
    virtual void Render();
};

#endif
