//
//  CGLSLLoader.h
//  gEngine
//
//  Created by sergey.sergeev on 10/31/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CGLSLLoader_h
#define gEngine_CGLSLLoaderr_h

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include "stdlib.h"
#include <string>

class CGLSLLoader
{
public:
    struct SGLSLData
    {
        GLuint s_pHandle;
        GLuint s_vHandle;
        GLuint s_fHandle;
    };
private:
    GLuint Build(const char* _pSource, GLenum _eShader);
public:
    CGLSLLoader();
    ~CGLSLLoader();
    SGLSLData Load(const char *_vSource, const char*_fSource);
};

#endif
