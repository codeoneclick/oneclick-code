//
//  CMeshMgr.h
//  iGaia
//
//  Created by sergey.sergeev on 11/28/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CMeshMgr_h
#define iGaia_CMeshMgr_h

#include "stdlib.h"
#include <string>
#include <map>
#include "CParser_MDL.h"
#include "IResourceMgr.h"
#include "IResourceLoaderDelegate.h"

class CMeshMgr : public IResourceMgr
{
private:
    CMesh::SSource* m_pStub;
public:
    CMeshMgr(void);
    ~CMeshMgr(void);
    
    virtual IResource* Load(std::string _sName, IResource::E_THREAD _eThread, IResourceLoaderDelegate* _pResourceLoaderDelegate);
    virtual void Unload(std::string _sName);
};

#endif
