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
    INode* m_pCurrentMoveNode;
    CMatch3Level* m_pLevel;
    int m_iCurrentMoveIndex[2];
    int m_iMoveIndex;
    int m_iMapCells;
    int m_iMapRows;

    int** m_pMapSource;
    std::vector<Vector2d> m_lPath;
    bool m_bLocked;
    bool m_bFind;
    void Move();
    void StartMove();
    void EndMove();
    void Refresh();
    void Generate();
public:
    CMatch3LogicController();
    ~CMatch3LogicController();
    static CMatch3LogicController *Instnace();
    void Set_Level(CMatch3Level* _pLevel);
    void Interserction(INode* _pNode);
    void Update(float _fTime);
    inline bool Get_Lock() { return m_bLocked; }
};

#endif
