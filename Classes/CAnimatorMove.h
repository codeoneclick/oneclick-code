//
//  CAnimatorMove.h
//  gEngine
//
//  Created by sergey.sergeev on 2/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CAnimatorMove_h
#define gEngine_CAnimatorMove_h
#include "IAnimator.h"

class CAnimatorMove : public IAnimator
{
protected:
    CVector3d m_vStartPosition;
    CVector3d m_vEndPosition;
    float m_fStep;
public:
    CAnimatorMove(void);
    ~CAnimatorMove(void);
    void Init(INode* _pNode, IAnimatorDelegate* _pAnimatorDelegateOwner, const CVector3d& _vStartPosition, const CVector3d&  _vEndPosition, float _fStep);
    virtual void Start(void);
    virtual void Stop(void);
    virtual void Update(void);
    virtual void Remove(void);
};


#endif
