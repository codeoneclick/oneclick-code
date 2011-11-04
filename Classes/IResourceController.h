//
//  IResourceController.h
//  gEngine
//
//  Created by sergey.sergeev on 11/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_IResourceController_h
#define gEngine_IResourceController_h
#include "IResource.h"
#include "ILoader.h"
#include <pthread.h>
#include "stdlib.h"
#include <map>

class IResourceController
{
protected:
    pthread_mutex_t m_mutex;
    std::map<std::string, ILoader*> m_lTaskPool;
    std::map<std::string, IResource*> m_lContainer;
public:
    IResourceController();
    ~IResourceController();
    
    virtual void Update();
    virtual void Thread();
    virtual IResource* Load(std::string _sName, IResource::E_LOAD_THREAD _eThread) = 0;
    virtual void Unload(std::string _sName) = 0;
};


#endif
