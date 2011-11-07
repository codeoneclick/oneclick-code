//
//  CShape.h
//  gEngine
//
//  Created by sergey.sergeev on 11/7/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CShape_h
#define gEngine_CShape_h

#include "INode.h"

class CShape : public INode
{
public:
    CShape();
    virtual ~CShape();
    virtual void Update(float _fTime);
    virtual void Render();
    virtual void Load(INode::SResourceParam &_param);
};


#endif
