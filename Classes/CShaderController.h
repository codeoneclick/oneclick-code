//
//  CShaderController.h
//  gEngine
//
//  Created by Snow Leopard User on 24/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CShaderController_h
#define gEngine_CShaderController_h

#include "stdlib.h"
#include <string>
#include <map>
#include "CShader.h"
#include "CGLSLLoader.h"

class CShaderController
{
public:
    enum E_SHADER { E_COLOR = 0, E_TEXTURE };
protected:
    std::map<E_SHADER, CGLSLLoader::SGLSLData> m_container;
public:
    CShaderController();
    ~CShaderController();
    CShader* Get_Shader(E_SHADER _eShader);
};

#endif
