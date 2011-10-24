//
//  CMTV.h
//  gEngine
//
//  Created by sergey.sergeev on 10/21/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CMTV_h
#define gEngine_CMTV_h
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <vector.h>

class CMTV
{
private:
    volatile std::vector<std::string> m_source;
    volatile int m_iterator;
    pthread_t m_thread_01;
    pthread_t m_thread_02;
public:
    CMTV();
    void Increment() { m_iterator++; }
    void Decrement() { m_iterator--; }
    void Run();
};

#endif
