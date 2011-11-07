//
//  CGame.h
//  gEngine
//
//  Created by Snow Leopard User on 26/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CGame_h
#define gEngine_CGame_h

#import "CRenderController.h"
#include "INode.h"
#include "CMatch3.h"

class CGame
{
private:
    static CGame* m_game;
    CRenderController* m_pRenderController;
    CMatch3* m_pGame_01;
public:
    CGame();
    ~CGame();
    static CGame* Instance();
    void Load(float _fWidth, float _fHeight);
    void Update(float _fTime);
    void Render();
};


#endif
