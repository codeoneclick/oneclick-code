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
    
    m_pMapSource = NULL;
    m_pMapWave = NULL;
    
    m_uiLevelCells = 0;
    m_uiLevelRows = 0;
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
    m_uiLevelCells = m_pLevel->Get_CellCount();
    m_uiLevelRows = m_pLevel->Get_RowCount();
    m_pMapSource = new int*[m_uiLevelCells + 2];
    m_pMapWave = new int*[m_uiLevelCells + 2];
    
    for(unsigned int i = 0; i < (m_uiLevelCells + 2); i++)
    {
        m_pMapSource[i] = new int[m_uiLevelRows + 2];
        m_pMapWave[i] = new int[m_uiLevelRows + 2];
        for(unsigned int j = 0; j < (m_uiLevelCells + 2); j++)
        {
            m_pMapSource[i][j] = 0;
            m_pMapWave[i][j] = 0;
        }
    }

    //memset(m_pMapSource, 0x0, (m_uiLevelCells + 2) * (m_uiLevelCells + 2) * sizeof(int));
    //memset(m_pMapWave, 0x0, (m_uiLevelCells + 2) * (m_uiLevelCells + 2) * sizeof(int));
    
    unsigned int index = 0;
    for(unsigned int i = 1; i <= m_uiLevelCells; i++)
    {
        for(unsigned int j = 1; j <= m_uiLevelRows; j++)
        {
            m_pMapWave[i][j] = 0;
            CMatch3Cell* pNode = static_cast<CMatch3Cell*>(m_pLevel->GetChildAt(index));
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
    m_iStartIndex[0] = static_cast<int>(pNode->Get_Index().x);
    m_iStartIndex[1]= static_cast<int>(pNode->Get_Index().y);
    pNode = static_cast<CMatch3Cell*>(m_pEndInterserctedNode);
    m_iEndIndex[0] = static_cast<int>(pNode->Get_Index().x);
    m_iEndIndex[1] = static_cast<int>(pNode->Get_Index().y);
    
    m_pMapSource[m_iStartIndex[0]][m_iStartIndex[1]] = 1;
    m_pMapSource[m_iEndIndex[0]][m_iEndIndex[1]] = 2;
    
    
    //SetupCellPathValue(m_iStartIndex[0], m_iStartIndex[1], 1);
    
    DoWave();
    
    
    std::cout<<"[m_pMapSource] :\n";
    for(unsigned int i = 1; i <= m_uiLevelCells; i++)
    {
        for(unsigned int j = 1; j <= m_uiLevelRows; j++)
        {
            std::cout<<m_pMapSource[i][j];
        }
        std::cout<<"\n";
    }
    
    std::cout<<"[m_pMapWave] :\n";
    for(unsigned int i = 1; i <= m_uiLevelCells; i++)
    {
        for(unsigned int j = 1; j <= m_uiLevelRows; j++)
        {
            std::cout<<m_pMapWave[i][j]<<",";
        }
        std::cout<<"\n";
    }

    return false;
}

void CMatch3LogicController::DoWave()
{
    int index = 1;
    m_pMapWave[m_iStartIndex[0]][m_iStartIndex[1]] = index;
    while (index < m_uiLevelCells * m_uiLevelRows) 
    {
        for(int i = 1; i <= m_uiLevelCells; i++)
        {
            for(int j = 1; j <= m_uiLevelRows; j++)
            {
                if(m_pMapWave[i][j] == index && m_pMapSource[i][j] == 2)
                {
                    m_pMapWave[i][j] = index + 1;
                    return;
                }
                
                if(m_pMapWave[i][j] == index)
                {
                    if( m_pMapWave[i + 1][j] == 0 && m_pMapSource[i + 1][j] == 0)
                    {
                        m_pMapWave[i + 1][j] = index + 1;
                    }
                    
                    if( m_pMapWave[i - 1][j] == 0 && m_pMapSource[i - 1][j] == 0)
                    {
                        m_pMapWave[i - 1][j] = index + 1;
                    }
                    
                    if( m_pMapWave[i][j + 1] == 0 && m_pMapSource[i][j + 1] == 0)
                    {
                        m_pMapWave[i][j + 1] = index + 1;
                    }
                    
                    if( m_pMapWave[i][j - 1] == 0 && m_pMapSource[i][j - 1] == 0)
                    {
                        m_pMapWave[i][j - 1] = index + 1;
                    }
                }
            }
        }
        index++;
    }
}

void CMatch3LogicController::SetupCellPathValue(int _i, int _j, int _index)
{
    /*m_pMapWave[_i][_j] = _index;
    _index++;

    
    
    for(int i = (_i - 1); i <= (_i + 1); i++)
    {
        for(int j = (_j - 1); j <= (_j + 1); j++)
        {
            if( i >= 0 && j >= 0 && i < m_uiLevelCells && j < m_uiLevelRows)
            {
                if( m_pMapWave[i][j] == 0 && m_pMapSource[i][j] == 0)
                {
                    m_pMapWave[i][j] = _index;
                }
            }
        }
    }

    
    for(int i = (_i - 1); i <= (_i + 1); i++)
    {
        for(int j = (_j - 1); j <= (_j + 1); j++)
        {
            if( i >= 0 && j >= 0 && i < m_uiLevelCells && j < m_uiLevelRows)
            {
                if( m_pMapWave[i][j] == _index && m_pMapSource[i][j] == 0)
                {
                    SetupCellPathValue(i, j, _index);
                }
            }
        }
    }*/
}
           
void CMatch3LogicController::Move()
{
               
}






