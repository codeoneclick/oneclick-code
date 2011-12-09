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

CInput* CInput::m_pInstance = NULL;

CInput::CInput()
{
    m_eCurrentState = E_UNTOUCH;
    m_eOldState = E_UNTOUCH;
    m_vStartCoord = Vector2d(0.0f, 0.0f);
    m_vEndCoord = Vector2d(0.0f, 0.0f);
    m_bClick = false;
    m_bMove = false;
    m_vMove = Vector2d(0.0f, 0.0f);
    m_fConstMoveLeght = 10.0f;
}

CInput::~CInput()
{
    
}

CInput* CInput::Instance()
{
    if(m_pInstance == NULL)
    {
        m_pInstance = new CInput();
    }
    
    return m_pInstance;
}

void CInput::Set_StartCoord(int _x, int _y)
{
    m_vStartCoord.x = _x;
    m_vStartCoord.y = abs(_y - CWindow::Get_Height());
}

void CInput::Set_EndCoord(int _x, int _y)
{
    m_vEndCoord .x = _x;
    m_vEndCoord .y = abs(_y - CWindow::Get_Height());
    m_bClick = true;
    m_bMove = true;
}

bool CInput::Get_Click()
{
    if(m_bClick && m_eCurrentState == E_UNTOUCH && m_eOldState == E_TOUCH)
    {
        m_bClick = !m_bClick;
        return !m_bClick;
    }
    return false;
}

Vector2d CInput::Get_Move()
{
    if(m_eCurrentState != E_MOVE)
    {
        return Vector2d(0.0f, 0.0f);
    }
    Vector2d vDirection = m_vStartCoord - m_vEndCoord;
    m_vStartCoord = m_vEndCoord;
    return vDirection;
}



















