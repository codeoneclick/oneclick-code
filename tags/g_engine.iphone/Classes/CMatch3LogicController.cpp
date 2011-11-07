//
//  CMatch3LogicController.cpp
//  gEngine
//
//  Created by sergey.sergeev on 11/7/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CMatch3LogicController.h"

CMatch3LogicController* CMatch3LogicController::m_pInsatnce = NULL;

CMatch3LogicController::CMatch3LogicController()
{
    
}

CMatch3LogicController::~CMatch3LogicController()
{
    
}

CMatch3LogicController* CMatch3LogicController::Instnace()
{
    if( m_pInsatnce == NULL)
    {
        m_pInsatnce = new CMatch3LogicController();
    }
    
    return m_pInsatnce;
}