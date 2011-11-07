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
        enum E_NODE { E_STATIC = 0, E_DYNAMIC };
        std::string s_sName;
        std::string s_sTexture;
        std::string s_sShader;
        Vector4d    s_vColor;
        Vector2d    s_vSize;
        Vector3d    s_vPosition;
        E_NODE      s_tNode;
    };
    CResource();
    ~CResource();
    static CResource* Instance();
     void Update();
    
    /*CTexture* Get_Texture(std::string _sName, CTextureController::E_LOAD_THREAD _eThread);
    void Unload_Texture(std::string _sName);
    
    CSequence* Get_Sequence(std::string _sName, CDataController::E_LOAD_THREAD _eThread);
    void Unload_Sequence(std::string _sName);*/
    
    CShader* Get_Shader(CShaderController::E_SHADER _eShader);
    
    IResource* Load(std::string _sName, IResource::E_PARSER _eParser, IResource::E_LOAD_THREAD _eThread);
    void Unload(IResource* _pResource);
};

#endif
