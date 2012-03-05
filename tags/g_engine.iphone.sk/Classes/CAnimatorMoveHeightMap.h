//
//  CAnimatorMoveHeightMap.h
//  gEngine
//
//  Created by sergey.sergeev on 2/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CAnimatorMoveHeightMap_h
#define gEngine_CAnimatorMoveHeightMap_h

#include "IAnimator.h"
#include "CHeightMapSetter.h"

class CAnimatorMoveHeightMap : public IAnimator
{
protected:
    CHeightMapSetter* m_pHeightMapSetterRef;
    CVector2d m_vStartPosition;
    CVector2d m_vEndPosition;
    float m_fStep;
public:
    CAnimatorMoveHeightMap(void);
    ~CAnimatorMoveHeightMap(void);
    void Init(INode* _pNode, IAnimatorDelegate* _pAnimatorDelegateOwner, CVector2d _vStartPosition, CVector2d _vEndPosition, float _fStep);
    virtual void Start(void);
    virtual void Stop(void);
    virtual void Update(void);
    virtual void Remove(void);
};


#endif
