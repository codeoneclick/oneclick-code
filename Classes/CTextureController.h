//
//  CTextureController.h
//  gEngine
//
//  Created by Snow Leopard User on 24/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CTextureController_h
#define gEngine_CTextureController_h

#include "stdlib.h"
#include <string>
#include <map>
#include "CPVRLoader.h"
#include <pthread.h>

class CTextureController
{
public:
    enum E_LOAD_THREAD
    {
        E_THREAD_MAIN,
        E_THREAD_BACKGROUND,
    };
private:
    std::map<std::string, CTexture*>   m_container;
    std::map<std::string, CPVRLoader*> m_requestQueue;
    CPVRLoader::SPVRSource* m_pStub;
    pthread_mutex_t m_mutex;
public:
    CTextureController();
    ~CTextureController();
    void Update();
    void UpdateThread();
    CTexture* Get_Texture(std::string _sName, E_LOAD_THREAD _eThread);
    void Unload_Texture(std::string _sName);
};


#endif
