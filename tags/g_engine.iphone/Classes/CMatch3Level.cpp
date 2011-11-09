//
//  CMatch3Level.cpp
//  gEngine
//
//  Created by sergey.sergeev on 11/7/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CMatch3Level.h"
#include "CMatch3LogicController.h"


CMatch3Level::CMatch3Level()
{
    
}

CMatch3Level::~CMatch3Level()
{
    
}

void CMatch3Level::Load(unsigned int _uiCellCount, unsigned int _uiRowCount)
{
    m_pParser = new CMatch3MapParser();
    std::string sName = "map_01.data";
    m_pParser->Parse(sName.c_str());
    m_uiCellCount = m_pParser->Get_CellCount();
    m_uiRowCount  = m_pParser->Get_RowCount();
    unsigned int index = 0;
    for(unsigned int i = 0; i < m_uiCellCount; ++i)
    {
        for(unsigned int j = 0; j < m_uiRowCount; ++j)
        {
            CMatch3Cell* node = new CMatch3Cell();
            INode::SResourceParam param;
            param.m_vColor = Vector4d(0.0f, 0.0f, 0.0f, 1.0f);
            param.m_vSize.x = 24.0f;
            param.m_vSize.y = 24.0f;
            param.m_vPosition = Vector3d( i * 26.0f, j * 26.0f, 0.0f); 
            node->Load(param);
            std::cout<<m_pParser->Get_MapData()[index];
            node->Set_State(m_pParser->Get_MapData()[index]);
            node->Set_Index(Vector2d(i,j));
            AddChild(node);
            index++;
        }
    }
    CMatch3LogicController::Instnace()->Set_Level(this);
}

void CMatch3Level::Update(float _fTime)
{
    INode::Update(_fTime);
}

void CMatch3Level::Render()
{
    INode::Render();
}

