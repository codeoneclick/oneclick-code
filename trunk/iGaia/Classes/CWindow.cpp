//
//  CWindow.cpp
//  iGaia
//
//  Created by sergey.sergeev on 12/5/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CWindow.h"

int CWindow::m_iScreenWidth  = 480;
int CWindow::m_iScreenHeight = 320;

int CWindow::m_iOffScreenWidth = 1024;
int CWindow::m_iOffScreenHeight = 768;

unsigned int CWindow::g_iTrianglesPerFrame = 0;
unsigned int CWindow::g_iFramesPerSecond = 0;



