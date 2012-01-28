//
//  CColliderBox.h
//  gEngine
//
//  Created by sergey.sergeev on 1/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CColliderBox_h
#define gEngine_CColliderBox_h

#include "ICollider.h"

class CColliderBox : public ICollider
{
public:
    CColliderBox(const CVector3d &_vMax, const CVector3d &_vMin);
    virtual ~CColliderBox();
    virtual void Render(void);
};

#endif
