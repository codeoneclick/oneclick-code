//
//  CSprite.h
//  gEngine
//
//  Created by sergey.sergeev on 10/24/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CSprite_h
#define gEngine_CSprite_h

#include "INode.h"
#include "CSequence.h"

class CSprite : public INode
{
public:
    CSprite();
    virtual ~CSprite();
    virtual void Update(float _fTime);
    virtual void Render();
    virtual void Load(INode::SResourceParam &_param);
};

#endif