//
//  CResourceTree.h
//  iGaia
//
//  Created by sergey.sergeev on 2/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CResourceTree_h
#define iGaia_CResourceTree_h

#include "IGameResource.h"
#include "CModel.h"
#include "CSceneMgr.h"

class CResourceTree : public IGameResource
{
protected:
    CModel* m_pModel;
public:
    CResourceTree(void);
    ~CResourceTree(void);
    void Load(void);
    virtual void Update(void);
};

#endif
