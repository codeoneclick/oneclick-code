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
#include "CSequence.h"

class CDataController
{
private:    
    std::map<std::string, std::vector<CFXMLLoader::SFrame*> > m_container;
public:
    CDataController();
    ~CDataController();
    void Get_Sequence(std::string _sName, CSequence* _pSequence);
};

#endif
