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
        E_STATE_TOUCH = 0, 
        E_STATE_UNTOUCH, 
        E_STATE_MOVE 
    };
protected:
    static CInput* m_pInstance;
    E_STATE m_eState;
    CVector2d m_vStartTouchPoint;
    CVector2d m_vEndTouchPoint;
public:
    CInput();
    ~CInput();
    static CInput* Instance();
    void Set_State(E_STATE _eState, CVector2d _vTouchPoint);
    CVector2d Get_TouchPoint(void) { return m_vStartTouchPoint; }
};

#endif
