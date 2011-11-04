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
#include "IResourceController.h"

class CDataController : public IResourceController
{
private:    
    CSequence::SSource* m_pStub;
public:
    CDataController();
    ~CDataController();
   
    virtual IResource* Load(std::string _sName, IResource::E_LOAD_THREAD _eThread);
    virtual void Unload(std::string _sName);
};

#endif
