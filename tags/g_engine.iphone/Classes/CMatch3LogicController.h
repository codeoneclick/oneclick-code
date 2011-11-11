//
//  CMatch3LogicController.h
//  gEngine
//
//  Created by sergey.sergeev on 11/7/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CMatch3LogicController_h
#define gEngine_CMatch3LogicController_h

#include "INode.h"
#include "CMatch3Level.h"

class CMatch3LogicController
{
private:
    static CMatch3LogicController* m_pInsatnce;
    INode* m_pStartIntersectedNode;
    INode* m_pEndInterserctedNode;
    CMatch3Level* m_pLevel;
    int m_iStartIndex[2]; 
    int m_iEndIndex[2];     
    unsigned int m_uiLevelCells;
    unsigned int m_uiLevelRows;

    int** m_pMapSource;
    int** m_pMapWave;
    std::vector<Vector2d> m_lPath;
    bool m_bLocked;
    bool FindPath();
    void SetupCellPathValue(int _i, int _j, int _index);
    void Move();
public:
    CMatch3LogicController();
    ~CMatch3LogicController();
    static CMatch3LogicController *Instnace();
    void Set_Level(CMatch3Level* _pLevel);
    void Interserction(INode* _pNode);
    void Update(float _fTime);
};

#endif
