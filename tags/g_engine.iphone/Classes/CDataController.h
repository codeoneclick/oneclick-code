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

class CDataController
{
private:    
    std::map<std::string, CSequence*> m_container;
public:
    CDataController();
    ~CDataController();
    CSequence* Get_Sequence(std::string _sName);
    void Unload_Sequence(std::string _sName);
};

#endif
