//
//  CMatch3Cell.h
//  gEngine
//
//  Created by sergey.sergeev on 11/7/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CMatch3Cell_h
#define gEngine_CMatch3Cell_h
#include "CShape.h"

class CMatch3Cell : public CShape
{
public:
    enum E_STATE { E_NONE = 1, E_EMPTY, E_LOCK, E_CELL_01, E_CELL_02, E_CELL_03, E_BONUS_01, E_BONUS_02, E_BONUS_03 };
    enum E_MOVE_STATE { E_STAY = 1, E_START_MOVE, E_END_MOVE };
private:
    E_STATE m_eState;
    E_MOVE_STATE m_eMoveState;
    Vector2d m_vIndex;
    bool Intersection();
    int  kMoveTimeDelay;
    long m_iStartMoveTimeStamp;
public:
    CMatch3Cell();
    ~CMatch3Cell();
    void Set_State(E_STATE _eState);
    inline E_STATE Get_State() { return m_eState; }
    virtual void Load(INode::SResourceParam &_param);
    virtual void Update(float _fTime);
    inline Vector2d Get_Index() { return m_vIndex; }
    inline void Set_Index(Vector2d _vIndex) { m_vIndex = _vIndex; }
    void Set_MoveState(E_MOVE_STATE _eMoveState);
    inline E_MOVE_STATE Get_MoveState() { return m_eMoveState; }
};


#endif
