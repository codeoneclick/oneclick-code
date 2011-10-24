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

class CSprite : public INode
{
public:
    CSprite();
    ~CSprite();
    virtual void Update(float _fTime);
    virtual void Render();
    virtual void Load(std::string _name, float _width, float _height);
public:
    float m_fWidth;
    float m_fHeight;
};

#endif
