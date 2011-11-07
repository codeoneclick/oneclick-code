//
//  CMovieClip.h
//  gEngine
//
//  Created by sergey.sergeev on 11/7/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CMovieClip_h
#define gEngine_CMovieClip_h

#include "INode.h"
#include "CSequence.h"

class CMovieClip : public INode
{
protected:
    CSequence *m_pSequence;
    unsigned int m_iCurrentFrame;
    unsigned int m_iTotalFrames; 
    Vector2d m_vFrameTexcoord[2];
    bool     m_bStop;
public:
    CMovieClip();
    virtual ~CMovieClip();
    virtual void Update(float _fTime);
    virtual void Render();
    virtual void Load(INode::SResourceParam &_param);
    void NextFrame();
    void GotoAndStop(unsigned int _frame);
    void GotoAndPlay(unsigned int _frame);
    unsigned int Get_TotalFrames() { return m_iTotalFrames; }
    unsigned int Get_CurrentFrame() { return m_iCurrentFrame; }
};


#endif
