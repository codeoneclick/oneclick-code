//
//  IResource.cpp
//  gEngine
//
//  Created by sergey.sergeev on 11/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "IResource.h"
#include "CResource.h"

IResource::IResource()
{
    m_uiRefCount = 0;
}

IResource::~IResource()
{
    
}

void IResource::Release()
{
    CResource::Instance()->Unload(this);
}