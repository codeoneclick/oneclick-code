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
private:
    E_STATE m_eState;
    static CInput* m_instance;
    Vector2d m_vTouchCoord; 
public:
    CInput();
    ~CInput();
    static CInput* Instance();
    inline E_STATE Get_State() { return m_eState; }
    inline void Set_State(E_STATE _eState) { m_eState = _eState; }
    void Set_Coord(float _x, float _y);
    inline Vector2d Get_Coord() { return m_vTouchCoord; }
};

#endif
