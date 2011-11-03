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

class CResource
{
public:
    friend void* UpdateThread(void *_pParam);
private:
    static CResource* m_pInstance;
    CTextureController* m_pTextureController;
    CShaderController* m_pShaderController;
    CDataController* m_pDataController;
    pthread_t m_thread;
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
    CResource();
    ~CResource();
    static CResource* Instance();
     void Update();
    
    CTexture* Get_Texture(std::string _sName, CTextureController::E_LOAD_THREAD _eThread);
    void Unload_Texture(std::string _sName);
    
    CSequence* Get_Sequence(std::string _sName, CDataController::E_LOAD_THREAD _eThread);
    void Unload_Sequence(std::string _sName);
    
    void Get_Shader(std::string _sName, CShader* _pShader);
    
   
};

#endif
