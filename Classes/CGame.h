//
//  CGame.h
//  gEngine
//
//  Created by Snow Leopard User on 26/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CGame_h
#define gEngine_CGame_h

#import "CRenderEngine.h"

class CGame
{
private:
    static CGame* m_game;
    CRenderEngine* m_pRenderController;
public:
    CGame();
    ~CGame();
    static CGame* Instance();
    void Load(float _fWidth, float _fHeight);
    void Update(float _fTime);
    void Render();
};


#endif
