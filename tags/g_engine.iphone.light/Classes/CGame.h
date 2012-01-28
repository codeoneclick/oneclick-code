//
//  CGame.h
//  gEngine
//
//  Created by Snow Leopard User on 26/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CGame_h
#define gEngine_CGame_h

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include "CModel.h"

class CGame
{
private:
    static CGame* m_game;
    GLuint m_hFrameBuffer;
    GLuint m_hRenderBuffer;
    GLuint m_hDepthBuffer;
    CModel* m_pMesh;
public:
    CGame();
    ~CGame();
    static CGame* Instance();
    void Load(float _fWidth, float _fHeight);
    void Update(float _fTime);
    void Render();
    void Set_Effect(unsigned int _iIndex);
    void Set_Model(unsigned int _iIndex);
};


#endif
