//
//  IResource.cpp
//  gEngine
//
//  Created by sergey.sergeev on 11/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "IResource.h"
#include "CResourceMgr.h"

IResource::IResource()
{
    m_iRefCount = 0;
}

IResource::~IResource()
{
    
}

void IResource::Release()
{
    CResourceMgr::Instance()->Unload(this);
}