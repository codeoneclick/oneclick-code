//
//  IAnimator.cpp
//  iGaia
//
//  Created by sergey.sergeev on 2/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "IAnimator.h"

IAnimator::IAnimator(void)
{
    m_pNode = NULL;
    m_pAnimatorDelegateOwner = NULL;
    m_bIsAnimated = false;
    m_bIsDone = false;
}

IAnimator::~IAnimator(void)
{
    
}