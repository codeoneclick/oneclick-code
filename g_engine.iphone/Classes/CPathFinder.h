//
//  CPathFinder.h
//  gEngine
//
//  Created by sergey.sergeev on 11/15/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CPathFinder_h
#define gEngine_CPathFinder_h

#include "stdlib.h"
#include <vector>
#include "CVector.h"

class CPathFinder
{
private:
    static CPathFinder* m_pInstance;
    int** m_pMapSource;
    int** m_pMapWave;
    int m_iNumCells;
    int m_iNumRows;
    int m_pStartIndex[2]; 
    int m_pEndIndex[2];
    std::vector<Vector2d> m_lPath;
    bool DoWave();
    bool TracePath();
    void Clear();
public:
    CPathFinder();
    ~CPathFinder();
    static CPathFinder* Instance();
    bool FindPath(int** _pMapSource, int _iNumCells, int _iNumRows, Vector2d vStartNode, Vector2d vEndNode);
    std::vector<Vector2d> Get_Path() { return m_lPath; }
};


#endif
