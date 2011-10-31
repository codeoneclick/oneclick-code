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

class CFXMLLoader
{
public:
    struct SFrame
    {
        Vector2d s_vPosition;
        Vector2d s_vSize;
    };
public:
    CFXMLLoader();
    ~CFXMLLoader();
    std::vector<SFrame*> Load(std::string _sName);
};


#endif
