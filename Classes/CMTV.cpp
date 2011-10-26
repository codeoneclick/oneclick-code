//
//  CMTV.cpp
//  gEngine
//
//  Created by sergey.sergeev on 10/21/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CMTV.h"

void *f_pthread_01(void *_value)
{
    while (true)
    {
        CMTV *obj = (CMTV*)_value;
        obj->Decrement();
        std::cout << "Decrement";
    }
}


void *f_pthread_02(void *_value)
{
    while (true)
    {
        CMTV *obj = (CMTV*)_value;
        obj->Increment();
        std::cout << "Increment";
    }
}

CMTV::CMTV()
{
    m_iterator = 0;
}

void CMTV::Run()
{
    int status = 0;
    status = pthread_create(&m_thread_01, NULL, f_pthread_01, (void*)this);
    status = pthread_create(&m_thread_02, NULL, f_pthread_02, (void*)this);
}