//
//  CShaderComposite.h
//  gEngine
//
//  Created by Snow Leopard User on 24/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CShaderComposite_h
#define gEngine_CShaderComposite_h

#include "stdlib.h"
#include <string>
#include <map>
#include "CShader.h"
#include "CParser_GLSL.h"

class CShaderComposite
{
private:
    static CShaderComposite* m_pInstance;
public:
    enum E_SHADER { E_COLOR = 0, E_TEXTURE };
protected:
    std::map<E_SHADER, CParser_GLSL::SGLSLData> m_container;
public:
    CShaderComposite();
    ~CShaderComposite();
    static CShaderComposite* Instance();
    CShader* Get_Shader(E_SHADER _eShader);
};

#endif
