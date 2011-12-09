//
//  IResourceMgr.h
//  gEngine
//
//  Created by sergey.sergeev on 11/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_IResourceMgr_h
#define gEngine_IResourceMgr_h
#include "IResource.h"
#include "IParser.h"
#include <pthread.h>
#include "stdlib.h"
#include <map>

class IResourceMgr
{
protected:
    pthread_mutex_t m_mutex;
    std::map<std::string, IParser*> m_lTaskPool;
    std::map<std::string, IResource*> m_lContainer;
public:
    IResourceMgr();
    ~IResourceMgr();
    
    virtual void Update();
    virtual void Thread();
    virtual IResource* Load(std::string _sName, IResource::E_PARSER _eParser, IResource::E_THREAD _eThread) = 0;
    virtual void Unload(std::string _sName) = 0;
};


#endif
