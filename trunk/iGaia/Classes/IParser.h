//
//  IParser.h
//  iGaia
//
//  Created by sergey.sergeev on 11/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_IParser_h
#define iGaia_IParser_h

#include "stdlib.h"
#include <string.h>

class IParser
{
public:
    enum E_STATUS
    {
        E_NONE_STATUS,
        E_START_STATUS,
        E_ERROR_STATUS,
        E_DONE_STATUS,
    };
protected:
    E_STATUS m_eStatus;
public:
    IParser();
    virtual ~IParser();
    virtual void  Load(const std::string& _sName) = 0;
    virtual void* Get_Source() = 0;
    virtual void  Commit() = 0;
    inline E_STATUS Get_Status() { return m_eStatus; }
};

#endif
