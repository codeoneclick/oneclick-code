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
    for(unsigned int i = 0; i < (m_iNumCells + 2); i++)
    {
        delete m_pMapSource[i];
        delete m_pMapWave[i];
    }

    delete m_pMapSource;
    delete m_pMapWave;
}

bool CPathFinder::FindPath(int** _pMapSource, int _iNumCells, int _iNumRows, Vector2d vStartNode, Vector2d vEndNode)
{
    m_lPath.clear();
    m_iNumCells = _iNumCells;
    m_iNumRows = _iNumRows;
    
    m_pStartIndex[0] = static_cast<int>(vStartNode.x);
    m_pStartIndex[1] = static_cast<int>(vStartNode.y);
    
    m_pEndIndex[0] = vEndNode.x;
    m_pEndIndex[1] = vEndNode.y;
    
    m_pMapSource = new int*[m_iNumCells + 2];
    m_pMapWave = new int*[m_iNumCells + 2];
    
    for(unsigned int i = 0; i < (m_iNumCells + 2); i++)
    {
        m_pMapSource[i] = new int[m_iNumRows + 2];
        m_pMapWave[i]   = new int[m_iNumRows + 2];
        for(unsigned int j = 0; j < (m_iNumRows + 2); j++)
        {
            m_pMapSource[i][j] = 0;
            m_pMapWave[i][j] = 0;
        }
    }
    
    for(unsigned int i = 1; i <= m_iNumCells; i++)
    {
        for(unsigned int j = 1; j <= m_iNumRows; j++)
        {
            m_pMapWave[i][j] = 0;
            m_pMapSource[i][j] = _pMapSource[i-1][j-1];
        }
    }
    
    m_pMapSource[m_pStartIndex[0]][m_pStartIndex[1]] = 1;
    m_pMapSource[m_pEndIndex[0]][m_pEndIndex[1]] = 2;
    
    if(DoWave())
    {
        if(TracePath())
        {
            std::cout<<"[m_pMapSource] :\n";
            for(int i = 1; i <= m_iNumCells; i++)
            {
                for(int j = 1; j <= m_iNumRows; j++)
                {
                    std::cout<<m_pMapSource[i][j];
                }
                std::cout<<"\n";
            }
            
            std::cout<<"[m_pMapWave] :\n";
            for(unsigned int i = 1; i <= m_iNumCells; i++)
            {
                for(unsigned int j = 1; j <= m_iNumRows; j++)
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
    m_pMapWave[m_pStartIndex[0]][m_pStartIndex[1]] = index;
    while (index < m_iNumCells * m_iNumRows) 
    {
        for(int i = 1; i <= m_iNumCells; i++)
        {
            for(int j = 1; j <= m_iNumRows; j++)
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
                        m_pMapWave[m_pEndIndex[0]][m_pEndIndex[1]] = index + 1;
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
    pCurrentNode[0] = m_pEndIndex[0];
    pCurrentNode[1] = m_pEndIndex[1];
    
    int pMinValueNode[2];
    pMinValueNode[0] = m_pEndIndex[0];
    pMinValueNode[1] = m_pEndIndex[1];
    
    int iMinValue = m_pMapWave[m_pEndIndex[0]][m_pEndIndex[1]];
    
    m_lPath.push_back(Vector2d(pCurrentNode[0], pCurrentNode[1]));
    
    int index = 0;
    while ( index < m_iNumCells * m_iNumRows ) 
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
        
        m_lPath.push_back(Vector2d(pCurrentNode[0], pCurrentNode[1]));
        
        index++;
    }
    return false;
}




