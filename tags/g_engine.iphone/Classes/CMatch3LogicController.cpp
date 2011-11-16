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
#include "CMatch3PathFind.h"

CMatch3LogicController* CMatch3LogicController::m_pInsatnce = NULL;

CMatch3LogicController::CMatch3LogicController()
{
    m_pStartIntersectedNode = NULL;
    m_pEndInterserctedNode = NULL;
    m_bLocked = false;
    m_bFind = false;
    
    m_pMapSource = NULL;
    
    m_iMapCells = 0;
    m_iMapRows = 0;
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
            if(m_pStartIntersectedNode != NULL)
            {
                m_pEndInterserctedNode = pNode;
            }
            break;
        default:
            break;
    }
}

void CMatch3LogicController::Set_Level(CMatch3Level *_pLevel)
{
    m_pLevel = _pLevel;
    m_iMapCells = m_pLevel->Get_CellCount();
    m_iMapRows = m_pLevel->Get_RowCount();
    m_pMapSource = new int*[m_iMapCells];
    
    for(unsigned int i = 0; i < m_iMapCells; i++)
    {
        m_pMapSource[i] = new int[m_iMapRows];
        for(unsigned int j = 0; j < m_iMapRows; j++)
        {
            m_pMapSource[i][j] = 0;
        }
    }
    Refresh();
}

void CMatch3LogicController::Update(float _fTime)
{
    if(m_pStartIntersectedNode != NULL && m_pEndInterserctedNode != NULL && !m_bFind)
    {
        CMatch3Cell* pStartNode = static_cast<CMatch3Cell*>(m_pStartIntersectedNode);
        CMatch3Cell* pEndNode = static_cast<CMatch3Cell*>(m_pEndInterserctedNode);

        m_bFind = CMatch3PathFind::Instance()->FindPath(m_pMapSource, m_iMapCells, m_iMapRows, pStartNode->Get_Index(), pEndNode->Get_Index()); //FindPath();
        if(m_bFind)
        {
            m_lPath = CMatch3PathFind::Instance()->Get_Path();
            StartMove();
        }
        else
        {
            m_pEndInterserctedNode = NULL;
        }
    }
    Move();
}

void CMatch3LogicController::StartMove()
{
    m_bLocked = true;
    int pCurrentNode[2]; 
    m_iMoveIndex = m_lPath.size() - 1;
    pCurrentNode[0] = m_lPath[m_iMoveIndex].x;
    pCurrentNode[1] = m_lPath[m_iMoveIndex].y;
    m_pCurrentMoveNode = m_pLevel->GetChildAt(pCurrentNode[0] * m_pLevel->Get_CellCount() + pCurrentNode[1]);
}

void CMatch3LogicController::EndMove()
{
    m_bLocked = false;
    m_bFind = false;
    static_cast<CMatch3Cell*>(m_pStartIntersectedNode)->Set_State(static_cast<CMatch3Cell*>(m_pEndInterserctedNode)->Get_State());
    m_pStartIntersectedNode = NULL;
    m_pEndInterserctedNode = NULL;
}

           
void CMatch3LogicController::Move()
{
    if(m_bFind)
    {
        CMatch3Cell *pNode = static_cast<CMatch3Cell*>(m_pCurrentMoveNode);
        std::cout<<pNode->Get_Index().x<<":::"<<pNode->Get_Index().y<<"\n";
        
        if(pNode->Get_MoveState() == CMatch3Cell::E_STAY)
        {
            pNode->Set_MoveState(CMatch3Cell::E_START_MOVE);
            pNode->Set_State(CMatch3Cell::E_CELL_01);
        }
        
        if(pNode->Get_MoveState() == CMatch3Cell::E_END_MOVE)
        {
            pNode->Set_State(CMatch3Cell::E_NONE); 
            m_iMoveIndex--;
            if(m_iMoveIndex < 0)
            {
                EndMove();
                return;
            }
            
            int pCurrentNode[2]; 
            pCurrentNode[0] = m_lPath[m_iMoveIndex].x;
            pCurrentNode[1] = m_lPath[m_iMoveIndex].y;
            m_pCurrentMoveNode = m_pLevel->GetChildAt(pCurrentNode[0] * m_pLevel->Get_CellCount() + pCurrentNode[1]);
        }
    }
}

void CMatch3LogicController::Refresh()
{
    unsigned int index = 0;
    for(unsigned int i = 0; i < m_iMapCells; i++)
    {
        for(unsigned int j = 0; j < m_iMapRows; j++)
        {
            CMatch3Cell* pNode = static_cast<CMatch3Cell*>(m_pLevel->GetChildAt(index));
            pNode->Set_MoveState(CMatch3Cell::E_STAY);
            switch (pNode->Get_State()) 
            {
                case CMatch3Cell::E_NONE :
                    m_pMapSource[i][j] = 0;
                    break;
                default:
                    m_pMapSource[i][j] = -1;
                    break;
            }
            index++;
        }
    }
}

void CMatch3LogicController::Generate()
{
    
}






