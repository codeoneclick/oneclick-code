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
    int** m_pMapCells;
    bool m_bLocked;
    bool FindPath();
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
