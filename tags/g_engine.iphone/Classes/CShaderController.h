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
protected:
    std::map<std::string, CGLSLLoader::SGLSLData> m_container;
public:
    CShaderController();
    ~CShaderController();
    void Get_Shader(std::string _sName, CShader* _pShader);
};

#endif
