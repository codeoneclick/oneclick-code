//
//  CMatch3Cell.cpp
//  gEngine
//
//  Created by sergey.sergeev on 11/7/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CMatch3Cell.h"
#include "CInput.h"
#include "CMatch3LogicController.h"

CMatch3Cell::CMatch3Cell()
{
    m_eState = E_NONE;
}

CMatch3Cell::~CMatch3Cell()
{
    
}

void CMatch3Cell::Load(INode::SResourceParam &_param)
{
    CShape::Load(_param);
}

void CMatch3Cell::Set_State(CMatch3Cell::E_STATE _eState)
{
    m_eState = _eState;
    Vector4d vColor = Vector4d(0.0f,0.0f,0.0f,1.0f);
    Set_Color(vColor);
    switch (_eState)
    {
        case E_NONE:
            vColor = Vector4d(0.0f,1.0f,0.0f,1.0f);
            Set_Color(vColor);
            break;
        case E_EMPTY:
            vColor = Vector4d(1.0f,1.0f,1.0f,1.0f);
            Set_Color(vColor);
            break;
        default:
            break;
    }
}

void CMatch3Cell::Update(float _fTime)
{
    CShape::Update(_fTime);
    Intersection();
}

bool CMatch3Cell::Intersection()
{
    if(CInput::Instance()->Get_State() == CInput::E_TOUCH)
    {
        bool bIntersect = false;
        Vector2d vTouchPosition = CInput::Instance()->Get_Coord();
        Vector2d vGlobal2dPosition = Vector2d(Get_GlobalPosition().x, Get_GlobalPosition().y);
        if(vTouchPosition.x < (vGlobal2dPosition.x + m_vSize.x / 2) &&
           vTouchPosition.x > (vGlobal2dPosition.x - m_vSize.x / 2) &&
           vTouchPosition.y < (vGlobal2dPosition.y + m_vSize.y / 2) &&
           vTouchPosition.y > (vGlobal2dPosition.y - m_vSize.y / 2))
        {
            bIntersect = true;
            CMatch3LogicController::Instnace()->Interserction(this);
        }
        
        if(bIntersect)
        {
            Vector4d vColor;
            switch (m_eState)
            {
                case E_NONE:
                    vColor = Vector4d(0.0f,0.0f,1.0f,1.0f);
                    Set_Color(vColor);
                    break;
                case E_EMPTY:
                    vColor = Vector4d(1.0f,1.0f,1.0f,1.0f);
                    Set_Color(vColor);
                    break;
                default:
                    break;
            }
        }
    }
    return false;
}





