//
//  CGame.h
//  gEngine
//
//  Created by Snow Leopard User on 26/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CGame_h
#define gEngine_CGame_h

#include "CRenderMgr.h"
#include "CSceneMgr.h"
#include "CLevel.h"


class CGame
{
private:
    static CGame* m_game;
    CLevel* m_pLevel;
public:
    CGame();
    ~CGame();
    static CGame* Instance();
    void Load();
    void Update(CSceneMgr::E_RENDER_STATE _eState, float _fTime);
    void Render(CSceneMgr::E_RENDER_STATE _eState);
};


#endif
