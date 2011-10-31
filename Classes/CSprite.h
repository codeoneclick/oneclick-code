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
protected:
    CSequence *m_pSequence;
    unsigned int m_iCurrentFrame;
    unsigned int m_iTotalFrames; 
    Vector2d m_vFrameTexcoord[2];
public:
    CSprite();
    virtual ~CSprite();
    virtual void Update(float _fTime);
    virtual void Render();
    virtual void Load(CResourceController::SResource &_resource);
    void NextFrame();
public:
    float m_fWidth;
    float m_fHeight;
};

#endif
