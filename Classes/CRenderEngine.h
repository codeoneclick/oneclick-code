//
//  CRenderEngine.h
//  gEngine
//
//  Created by sergey.sergeev on 10/24/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CRenderEngine_h
#define gEngine_CRenderEngine_h

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <cmath>
#include <iostream>
#include "INode.h"

class CRenderEngine
{
private:
    GLuint m_framebuffer;
    GLuint m_renderbuffer;
public:
    CRenderEngine(unsigned int _width, unsigned int _height);
    ~CRenderEngine();
    void Render();
    void Update(float fTime);
};


#endif
