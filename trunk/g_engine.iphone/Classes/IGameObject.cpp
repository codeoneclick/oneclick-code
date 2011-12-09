//
//  IGameObject.cpp
//  gEngine
//
//  Created by sergey.sergeev on 12/2/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "IGameObject.h"

IGameObject::IGameObject()
{
    m_vScale    = Vector3d(1.0f, 1.0f, 1.0f);
    m_vRotation = Vector3d(0.0f, 0.0f, 0.0f);
    m_vPosition = Vector3d(0.0f, 0.0f, 0.0f);
}

IGameObject::~IGameObject()
{

}