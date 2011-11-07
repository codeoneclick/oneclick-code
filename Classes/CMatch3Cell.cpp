//
//  CMatch3Cell.cpp
//  gEngine
//
//  Created by sergey.sergeev on 11/7/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CMatch3Cell.h"

CMatch3Cell::CMatch3Cell()
{
    
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
    Vector4d vColor;
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