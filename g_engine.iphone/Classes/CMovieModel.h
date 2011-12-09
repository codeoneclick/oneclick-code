//
//  CMovieModel.h
//  gEngine
//
//  Created by sergey.sergeev on 12/1/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CMovieModel_h
#define gEngine_CMovieModel_h
#include "INode.h"

class CMovieModel : public INode
{
protected:
    int m_iCurrentFrame;
    float m_fLastUpdateFrameTime;
    float m_fFrameTimeInterval;
    
    void UpdateFrames(float _fTime);
    void UpdateBones(float _fTime);
public:
    CMovieModel();
    virtual ~CMovieModel();
    virtual void Load(IResource::SResource _pReosurce);
    virtual void Intersect(bool _bItersected);
    virtual void Update(float _fTime);
    virtual void Render();
};


#endif
