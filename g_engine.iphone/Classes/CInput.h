//
//  CInput.h
//  gEngine
//
//  Created by sergey.sergeev on 10/31/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CInput_h
#define gEngine_CInput_h

#include "CVector.h"

class CInput
{
public:
    enum E_STATE 
    { 
        E_TOUCH = 0, 
        E_UNTOUCH, 
        E_MOVE 
    };
protected:
    static CInput* m_pInstance;
    E_STATE m_eOldState;
    E_STATE m_eCurrentState;
    Vector2d m_vStartCoord;
    Vector2d m_vEndCoord;
    bool     m_bClick;
    bool     m_bMove;
    Vector2d m_vMove;
    float m_fConstMoveLeght;
public:
    CInput();
    ~CInput();
    static CInput* Instance();
    inline E_STATE Get_State() { return m_eCurrentState; }
    inline void Set_State(E_STATE _eState) { m_eOldState = m_eCurrentState; m_eCurrentState = _eState; }
    void Set_StartCoord(int _x, int _y);
    void Set_EndCoord(int _x, int _y);
    inline Vector2d Get_Coord() { return m_vEndCoord; }
    bool Get_Click();
    Vector2d Get_Move();
};

#endif
