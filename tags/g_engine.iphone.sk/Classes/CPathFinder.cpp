//
//  CPathFinder.cpp
//  gEngine
//
//  Created by sergey.sergeev on 11/15/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CPathFinder.h"

CPathFinder* CPathFinder::m_pInstance = NULL;

CPathFinder::CPathFinder()
{
    m_pMapWave = NULL;
    m_pMapSource = NULL;
}

CPathFinder::~CPathFinder()
{
    
}

CPathFinder* CPathFinder::Instance()
{
    if( m_pInstance == NULL )
    {
        m_pInstance = new CPathFinder();
    }
    
    return m_pInstance;
}

void CPathFinder::Clear()
{
    for(unsigned int i = 0; i < (m_iMapCells + 2); i++)
    {
        delete m_pMapSource[i];
        delete m_pMapWave[i];
    }

    delete m_pMapSource;
    delete m_pMapWave;
}

bool CPathFinder::FindPath(int** _pMapSource, int _iMapCells, int _iMapRows, CVector2d vStartNode, CVector2d vEndNode)
{
    m_iMapCells = _iMapCells;
    m_iMapRows = _iMapRows;
    
    m_iStartIndex[0] = vStartNode.x;
    m_iStartIndex[1] = vStartNode.y;
    
    m_iEndIndex[0] = vEndNode.x;
    m_iEndIndex[1] = vEndNode.y;
    
    m_pMapSource = new int*[m_iMapCells + 2];
    m_pMapWave = new int*[m_iMapCells + 2];
    
    for(unsigned int i = 0; i < (m_iMapCells + 2); i++)
    {
        m_pMapSource[i] = new int[m_iMapRows + 2];
        m_pMapWave[i] = new int[m_iMapRows + 2];
        for(unsigned int j = 0; j < (m_iMapRows + 2); j++)
        {
            m_pMapSource[i][j] = 0;
            m_pMapWave[i][j] = 0;
        }
    }
    
    for(unsigned int i = 1; i <= m_iMapCells; i++)
    {
        for(unsigned int j = 1; j <= m_iMapRows; j++)
        {
            m_pMapWave[i][j] = 0;
            m_pMapSource[i][j] = _pMapSource[i-1][j-1];
        }
    }
    
    m_pMapSource[m_iStartIndex[0]][m_iStartIndex[1]] = 1;
    m_pMapSource[m_iEndIndex[0]][m_iEndIndex[1]] = 2;
    
    if(DoWave())
    {
        if(TracePath())
        {
            std::cout<<"[m_pMapSource] :\n";
            for(int i = 1; i <= m_iMapCells; i++)
            {
                for(int j = 1; j <= m_iMapRows; j++)
                {
                    std::cout<<m_pMapSource[i][j];
                }
                std::cout<<"\n";
            }
            
            std::cout<<"[m_pMapWave] :\n";
            for(unsigned int i = 1; i <= m_iMapCells; i++)
            {
                for(unsigned int j = 1; j <= m_iMapRows; j++)
                {
                    std::cout<<m_pMapWave[i][j]<<",";
                }
                std::cout<<"\n";
            }
            Clear();
            return true;
        }
    }
    Clear();
    return false;
}


bool CPathFinder::DoWave()
{
    int index = 1;
    m_pMapWave[m_iStartIndex[0]][m_iStartIndex[1]] = index;
    while (index < m_iMapCells * m_iMapRows) 
    {
        for(int i = 1; i <= m_iMapCells; i++)
        {
            for(int j = 1; j <= m_iMapRows; j++)
            {
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
                    
                    if(m_pMapSource[i + 1][j] == 2 || m_pMapSource[i - 1][j] == 2 || m_pMapSource[i][j + 1] == 2 || m_pMapSource[i][j - 1] == 2)
                    {
                        m_pMapWave[m_iEndIndex[0]][m_iEndIndex[1]] = index + 1;
                        return true;
                    }
                }
            }
        }
        index++;
    }
    return false;
}


bool CPathFinder::TracePath()
{
    int pCurrentNode[2]; 
    pCurrentNode[0] = m_iEndIndex[0];
    pCurrentNode[1] = m_iEndIndex[1];
    
    int pMinValueNode[2];
    pMinValueNode[0] = m_iEndIndex[0];
    pMinValueNode[1] = m_iEndIndex[1];
    
    int iMinValue = m_pMapWave[m_iEndIndex[0]][m_iEndIndex[1]];
    
    m_lPath.push_back(CVector2d(pCurrentNode[0], pCurrentNode[1]));
    
    int index = 0;
    while ( index < m_iMapCells * m_iMapRows ) 
    {
        if( m_pMapWave[pCurrentNode[0] + 1][pCurrentNode[1]] < iMinValue && m_pMapWave[pCurrentNode[0] + 1][pCurrentNode[1]] != 0  && m_pMapSource[pCurrentNode[0] + 1][pCurrentNode[1]] > 0)
        {
            iMinValue = m_pMapWave[pCurrentNode[0] + 1][pCurrentNode[1]];
            pMinValueNode[0] = pCurrentNode[0] + 1;
            pMinValueNode[1] = pCurrentNode[1];
        }
        
        if( m_pMapWave[pCurrentNode[0] - 1][pCurrentNode[1]] < iMinValue && m_pMapWave[pCurrentNode[0] - 1][pCurrentNode[1]] != 0 )
        {
            iMinValue = m_pMapWave[pCurrentNode[0] - 1][pCurrentNode[1]];
            pMinValueNode[0] = pCurrentNode[0] - 1;
            pMinValueNode[1] = pCurrentNode[1];
        }
        
        if( m_pMapWave[pCurrentNode[0]][pCurrentNode[1] + 1] < iMinValue && m_pMapWave[pCurrentNode[0]][pCurrentNode[1] + 1] != 0 )
        {
            iMinValue = m_pMapWave[pCurrentNode[0]][pCurrentNode[1] + 1];
            pMinValueNode[0] = pCurrentNode[0];
            pMinValueNode[1] = pCurrentNode[1] + 1;
        }
        
        if( m_pMapWave[pCurrentNode[0]][pCurrentNode[1] - 1] < iMinValue && m_pMapWave[pCurrentNode[0]][pCurrentNode[1] - 1] != 0 )
        {
            iMinValue = m_pMapWave[pCurrentNode[0]][pCurrentNode[1] - 1];
            pMinValueNode[0] = pCurrentNode[0];
            pMinValueNode[1] = pCurrentNode[1] - 1;
        }
        
        pCurrentNode[0] = pMinValueNode[0];
        pCurrentNode[1] = pMinValueNode[1];
        
        if( m_pMapWave[pCurrentNode[0]][pCurrentNode[1]] == 1 )
        {
            return true;
        }
        
        m_lPath.push_back(CVector2d(pCurrentNode[0], pCurrentNode[1]));
        
        index++;
    }
    return false;
}




