//
//  CRenderController.h
//  gEngine
//
//  Created by sergey.sergeev on 10/24/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CRenderController_h
#define gEngine_CRenderController_h

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <cmath>
#include <iostream>

class CRenderController
{
private:
    GLuint m_framebuffer;
    GLuint m_renderbuffer;
public:
    CRenderController(unsigned int _width, unsigned int _height);
    ~CRenderController();
    void BeginScene();
    void EndScene();
};


#endif
