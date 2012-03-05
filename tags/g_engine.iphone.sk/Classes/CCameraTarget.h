//
//  CCameraTarget.h
//  gEngine
//
//  Created by sergey.sergeev on 12/29/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CCameraTarget_h
#define gEngine_CCameraTarget_h

#include "ICamera.h"
#include "INode.h"

class CCameraTarget : public ICamera
{ 
protected:
    INode* m_pTarget;
public:
    CCameraTarget(void);
    virtual ~CCameraTarget();
    virtual void Update(void);
    virtual void OnScreenMove(CVector2d _vMoveDirection);
    void Set_Target(INode* _pTarget) { m_pTarget = _pTarget; }
    INode* Get_Target(void) { return m_pTarget; }
};

#endif
