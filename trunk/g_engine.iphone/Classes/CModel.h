//
//  CModel.h
//  gEngine
//
//  Created by sergey.sergeev on 11/17/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CModel_h
#define gEngine_CModel_h

#include "INode.h"

class CModel : public INode
{
public:
    CModel();
    virtual ~CModel();
    virtual void Load(IResource::SResource _pReosurce);
    virtual void Intersect(bool _bIntersected);
    virtual void Update(float _fTime);
    virtual void Render();
};

#endif
