//
//  CMatch3LogicController.cpp
//  gEngine
//
//  Created by sergey.sergeev on 11/7/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CMatch3LogicController.h"
#include "CMatch3Cell.h"

CMatch3LogicController* CMatch3LogicController::m_pInsatnce = NULL;

CMatch3LogicController::CMatch3LogicController()
{
    m_pStartIntersectedNode = NULL;
    m_pEndInterserctedNode = NULL;
    m_bLocked = false;
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

void CMatch3LogicController::Interserction(INode* _pNode)
{
    CMatch3Cell* pNode = static_cast<CMatch3Cell*>(_pNode);
    switch (pNode->Get_State()) 
    {
        case CMatch3Cell::E_CELL_01 :
        case CMatch3Cell::E_CELL_02 :
        case CMatch3Cell::E_CELL_03 :
            m_pStartIntersectedNode = pNode;
            break;
        case CMatch3Cell::E_NONE :
            m_pEndInterserctedNode = pNode;
            break;
        default:
            break;
    }
}

void CMatch3LogicController::Set_Level(CMatch3Level *_pLevel)
{
    m_pLevel = _pLevel;
    unsigned int uiLevelCells = m_pLevel->Get_CellCount();
    unsigned int uiLevelRows = m_pLevel->Get_RowCount();
    m_pMapCells = new int*[uiLevelCells];
    unsigned int index = 0;
    for(unsigned int i = 0; i < uiLevelCells; i++)
    {
        m_pMapCells[i] = new int[uiLevelRows];
        for(unsigned int j = 0; j < uiLevelRows; j++)
        {
            CMatch3Cell* pNode = static_cast<CMatch3Cell*>(m_pLevel->GetChildAt(index));
            switch (pNode->Get_State()) 
            {
                case CMatch3Cell::E_NONE :
                    m_pMapCells[i][j] = 0;
                    break;
                default:
                    m_pMapCells[i][j] = -1;
                    break;
            }
            index++;
        }
    }
}

void CMatch3LogicController::Update(float _fTime)
{
    if(m_pStartIntersectedNode != NULL && m_pEndInterserctedNode != NULL)
    {
        if(FindPath())
        {
            Move();
        }
        else
        {
            m_pEndInterserctedNode = NULL;
        }
    }
}

bool CMatch3LogicController::FindPath()
{
    CMatch3Cell* pNode = static_cast<CMatch3Cell*>(m_pStartIntersectedNode);
    m_pMapCells[static_cast<int>(pNode->Get_Index().x)][static_cast<int>(pNode->Get_Index().y)] = 1;
    pNode = static_cast<CMatch3Cell*>(m_pEndInterserctedNode);
    m_pMapCells[static_cast<int>(pNode->Get_Index().x)][static_cast<int>(pNode->Get_Index().y)] = 2;
    return false;
}
           
void CMatch3LogicController::Move()
{
               
}






