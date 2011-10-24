//
//  CResourceController.h
//  gEngine
//
//  Created by Snow Leopard User on 24/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CResourceController_h
#define gEngine_CResourceController_h

#include "CShaderController.h"
#include "CTextureController.h"

class CResourceController
{
private:
    static CResourceController* m_resourceController;
    CTextureController* m_textureController;
    CShaderController* m_shaderController;
public:
    CResourceController();
    ~CResourceController();
    CResourceController* Instance();
    inline CTextureController* TextureController() { return m_textureController; }
    inline CShaderController* ShaderController() { return m_shaderController; }
};

#endif
