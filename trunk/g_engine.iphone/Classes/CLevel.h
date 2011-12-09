//
//  CLevel.h
//  gEngine
//
//  Created by sergey.sergeev on 12/1/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CLevel_h
#define gEngine_CLevel_h

#include "CSector.h"
#include "CPlayer.h"

class CLevel
{
protected:
    enum E_GAME_STATE { E_GAME_STATE_PLAYER_STEP = 0, E_GAME_STATE_ENEMY_STEP };
    CSector*** m_pGround;
    int** m_pNavigationMap;
    CPlayer*   m_pPlayer;
    CPlayer*   m_pEnemy;
    unsigned char m_iWidth;
    unsigned char m_iHeight;
public:
    CLevel();
    ~CLevel();
    void Load(std::string _sName);
    void Update(float _fTime);
};

#endif
