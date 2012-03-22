//
//  CColliderQuad.h
//  gEngine
//
//  Created by sergey.sergeev on 1/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CColliderQuad_h
#define gEngine_CColliderQuad_h

#include "ICollider.h"

class CColliderQuad : public ICollider
{
public:
    CColliderQuad(const glm::vec3 &_vPoint_01, const glm::vec3 &_vPoint_02, const glm::vec3 &_vPoint_03, const glm::vec3 &_vPoint_04);
    virtual ~CColliderQuad();
    virtual void Render(void);
};

#endif
