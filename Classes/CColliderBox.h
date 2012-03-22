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
    CColliderBox(const glm::vec3 &_vMax, const glm::vec3 &_vMin);
    virtual ~CColliderBox();
    virtual void Render(void);
};

#endif
