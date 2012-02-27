//
//  CMeshMgr.h
//  gEngine
//
//  Created by sergey.sergeev on 11/28/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CMeshMgr_h
#define gEngine_CMeshMgr_h

#include "stdlib.h"
#include <string>
#include <map>
#include "CParser_MDL.h"
#include "IResourceMgr.h"

class CMeshMgr : public IResourceMgr
{
private:
    CMesh::SSource* m_pStub;
public:
    CMeshMgr();
    ~CMeshMgr();
    
    virtual IResource* Load(std::string _sName, IResource::E_THREAD _eThread);
    virtual void Unload(std::string _sName);
};

#endif
