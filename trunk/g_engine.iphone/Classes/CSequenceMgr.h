//
//  CSequenceMgr.h
//  gEngine
//
//  Created by sergey.sergeev on 10/28/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CSequenceMgr_h
#define gEngine_CSequenceMgrr_h
#include "CParser_SEQ.h"
#include "IResourceMgr.h"

class CSequenceMgr : public IResourceMgr
{
private:    
    CSequence::SSource* m_pStub;
public:
    CSequenceMgr();
    ~CSequenceMgr();
   
    virtual IResource* Load(std::string _sName, IResource::E_PARSER _eParser, IResource::E_THREAD _eThread);
    virtual void Unload(std::string _sName);
};

#endif
