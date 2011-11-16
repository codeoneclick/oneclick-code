//
//  CMatch3PathFind.h
//  gEngine
//
//  Created by sergey.sergeev on 11/15/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CMatch3PathFind_h
#define gEngine_CMatch3PathFind_h

#include "stdlib.h"
#include <vector>
#include "CVector.h"

class CMatch3PathFind
{
private:
    static CMatch3PathFind* m_pInstance;
    int** m_pMapSource;
    int** m_pMapWave;
    int m_iMapCells;
    int m_iMapRows;
    int m_iStartIndex[2]; 
    int m_iEndIndex[2];
    std::vector<Vector2d> m_lPath;
    bool DoWave();
    bool TracePath();
    void Clear();
public:
    CMatch3PathFind();
    ~CMatch3PathFind();
    static CMatch3PathFind* Instance();
    bool FindPath(int** _pMapSource, int _iMapCells, int _iMapRows, Vector2d vStartNode, Vector2d vEndNode);
    std::vector<Vector2d> Get_Path() { return m_lPath; }
};


#endif
