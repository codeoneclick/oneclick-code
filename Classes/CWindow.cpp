//
//  CWindow.cpp
//  gEngine
//
//  Created by sergey.sergeev on 10/31/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CWindow.h"

CWindow* CWindow::m_instance = NULL;

CWindow::CWindow()
{
    
}

CWindow::~CWindow()
{
    
}

CWindow* CWindow::Instance()
{
    if(m_instance == NULL)
    {
        m_instance = new CWindow();
    }
    
    return m_instance;
}

void CWindow::Init(unsigned int _uiWidth, unsigned int _uiHeight)
{
    m_uiWidth = _uiWidth;
    m_uiHeight = _uiHeight;
}