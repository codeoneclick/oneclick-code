//
//  CLevel.cpp
//  gEngine
//
//  Created by sergey.sergeev on 11/7/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CLevel.h"

CLevel::CLevel()
{
    
}

CLevel::~CLevel()
{
    
}

void CLevel::Load(unsigned int _uiCellCount, unsigned int _uiRowCount)
{
    m_uiCellCount = _uiCellCount;
    m_uiRowCount  = _uiRowCount;
    for(unsigned int i = 0; i < m_uiCellCount; ++i)
    {
        for(unsigned int j = 0; j < m_uiRowCount; ++j)
        {
            INode* node = new CShape();
            INode::SResourceParam param;
            param.m_vColor = Vector4d(0.0f, 1.0f, 0.0f, 1.0f);
            param.m_vSize.x = 24.0f;
            param.m_vSize.y = 24.0f;
            param.m_vPosition = Vector3d( i * 26.0f, j * 26.0f, 0.0f); 
            node->Load(param);
            this->AddChild(node);
        }
    }
}

void CLevel::Render()
{
    INode::Render();
}