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
    int m_iMapCells;
    int m_iMapRows;
    int m_iStartIndex[2]; 
    int m_iEndIndex[2];
    std::vector<CVector2d> m_lPath;
    bool DoWave();
    bool TracePath();
    void Clear();
public:
    CPathFinder();
    ~CPathFinder();
    static CPathFinder* Instance();
    bool FindPath(int** _pMapSource, int _iMapCells, int _iMapRows, CVector2d vStartNode, CVector2d vEndNode);
    std::vector<CVector2d> Get_Path() { return m_lPath; }
};


#endif
