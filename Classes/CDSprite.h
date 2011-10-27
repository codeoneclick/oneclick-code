//
//  CDSprite.h
//  gEngine
//
//  Created by sergey.sergeev on 10/27/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CDSprite_h
#define gEngine_CDSprite_h
#include "CSprite.h"

class CDSprite : public CSprite
{
public:
    CDSprite();
    ~CDSprite();
    virtual void Load(CResourceController::SResource &_resource);
    virtual void Set_Position(Vector3d &_vPosition);
    virtual void Set_Rotation(float _fRotation);
    virtual void Set_Scale(Vector2d &_vScale);
};


#endif
