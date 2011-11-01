//
//  CFXMLLoader.h
//  gEngine
//
//  Created by sergey.sergeev on 10/31/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CFXMLLoader_h
#define gEngine_CFXMLLoader_h

#include "stdlib.h"
#include <string>
#include <map>
#include <vector>
#include "CVector.h"
#include "CSequence.h"

class CFXMLLoader
{
public:
    CFXMLLoader();
    ~CFXMLLoader();
    CSequence* Load(std::string _sName);
};


#endif
