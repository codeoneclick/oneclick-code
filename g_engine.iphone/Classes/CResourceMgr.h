//
//  CResourceMgr.h
//  gEngine
//
//  Created by Snow Leopard User on 24/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CResourceMgr_h
#define gEngine_CResourceMgr_h

#include "CTextureMgr.h"
#include "CSequenceMgr.h"
#include "CMeshMgr.h"

#include "stdlib.h"
#include <map>

class CResourceMgr
{
public:
    friend void* UpdateThread(void *_pParam);
    std::map<IResource::E_MGR,IResourceMgr*> m_lMgr;
private:
    static CResourceMgr* m_pInstance;
    pthread_t m_thread;
public:   
    CResourceMgr();
    ~CResourceMgr();
    static CResourceMgr* Instance();
    void Update();
    IResource* Load(const std::string& _sName,IResource::E_MGR _eMgr, IResource::E_PARSER _eParser, IResource::E_THREAD _eThread);
    void Unload(IResource* _pResource);
};

#endif