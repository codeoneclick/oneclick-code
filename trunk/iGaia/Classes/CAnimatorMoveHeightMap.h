//
//  CAnimatorMoveHeightMap.h
//  iGaia
//
//  Created by sergey.sergeev on 2/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CAnimatorMoveHeightMap_h
#define iGaia_CAnimatorMoveHeightMap_h

#include "IAnimator.h"
#include "CHeightMapSetter.h"

class CAnimatorMoveHeightMap : public IAnimator
{
protected:
    CHeightMapSetter* m_pHeightMapSetterRef;
    glm::vec2 m_vStartPosition;
    glm::vec2 m_vEndPosition;
    float m_fStep;
public:
    CAnimatorMoveHeightMap(void);
    ~CAnimatorMoveHeightMap(void);
    void Init(INode* _pNode, IAnimatorDelegate* _pAnimatorDelegateOwner, glm::vec2 _vStartPosition, glm::vec2 _vEndPosition, float _fStep);
    virtual void Start(void);
    virtual void Stop(void);
    virtual void Update(void);
    virtual void Remove(void);
};


#endif
