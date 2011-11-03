//
//  CDataController.h
//  gEngine
//
//  Created by sergey.sergeev on 10/28/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CDataController_h
#define gEngine_CDataController_h
#include "CFXMLLoader.h"
#include <pthread.h>

class CDataController
{
public:
    enum E_LOAD_THREAD
    {
        E_THREAD_MAIN,
        E_THREAD_BACKGROUND,
    };
private:    
    std::map<std::string, CSequence*> m_lContainer;
    std::map<std::string, CFXMLLoader*> m_lTaskPool;
    std::vector<CSequence::SFrame*> m_pStub;
    pthread_mutex_t m_mutex;
public:
    CDataController();
    ~CDataController();
    void Update();
    void UpdateThread();
    CSequence* Get_Sequence(std::string _sName, E_LOAD_THREAD _eThread);
    void Unload_Sequence(std::string _sName);
};

#endif
