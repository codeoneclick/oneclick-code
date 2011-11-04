//
//  ILoader.h
//  gEngine
//
//  Created by sergey.sergeev on 11/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_ILoader_h
#define gEngine_ILoader_h

#include "stdlib.h"
#include "string.h"


class ILoader
{
public:
    enum E_STATUS
    {
        E_STATUS_NONE,
        E_STATUS_START,
        E_STATUS_ERROR,
        E_STATUS_DONE,
    };
protected:
    E_STATUS m_eStatus;
public:
    ILoader();
    virtual ~ILoader();
    virtual void Load(const char* _sName) = 0;
    virtual void* Get_Source() = 0;
    virtual void Commit() = 0;
    inline E_STATUS Get_Status() { return m_eStatus; }
};

#endif
