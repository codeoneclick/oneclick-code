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
#include "CDataController.h"

class CResourceController
{
private:
    static CResourceController* m_resourceController;
    CTextureController* m_textureController;
    CShaderController* m_shaderController;
    CDataController* m_dataController;
public:
    struct SResource
    {
        enum T_NODE { SPRITE = 0, DSPRITE };
        std::string s_sName;
        std::string s_sTexture;
        std::string s_sShader;
        Vector4d    s_vColor;
        Vector2d    s_vSize;
        Vector3d    s_vPosition;
        T_NODE      s_tNode;
    };
    CResourceController();
    ~CResourceController();
    static CResourceController* Instance();
    inline CTextureController* TextureController() { return m_textureController; }
    inline CShaderController* ShaderController() { return m_shaderController; }
    inline CDataController* DataController() { return m_dataController; }
};

#endif
