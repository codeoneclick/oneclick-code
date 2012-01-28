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
#include "ILight.h"

class CGame
{
private:
    static CGame* m_game;
    INode* m_pNode;
    ILight* m_pLight;
public:
    CGame();
    ~CGame();
    static CGame* Instance(void);
    void Load(void);
    void Update(void);
    void Render(void);
};


#endif
