//
//  CInput.cpp
//  gEngine
//
//  Created by sergey.sergeev on 10/31/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CInput.h"
#include "CWindow.h"

CInput* CInput::m_instance = NULL;

CInput::CInput()
{
    m_eState = E_UNTOUCH;
    m_vTouchCoord = Vector2d(0.0f, 0.0f);
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

void CInput::Set_Coord(float _x, float _y)
{
    m_vTouchCoord.x = _x - CWindow::Instance()->Get_Width() / 2;
    m_vTouchCoord.y = -(_y - CWindow::Instance()->Get_Height() / 2);
}