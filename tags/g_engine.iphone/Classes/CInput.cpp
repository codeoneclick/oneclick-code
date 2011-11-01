//
//  CInput.cpp
//  gEngine
//
//  Created by sergey.sergeev on 10/31/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CInput.h"

CInput* CInput::m_instance = NULL;

CInput::CInput()
{
    
}

CInput::~CInput()
{
    
}

CInput* CInput::Instance()
{
    if(m_instance == NULL)
    {
        m_instance = new CInput();
    }
    
    return m_instance;
}