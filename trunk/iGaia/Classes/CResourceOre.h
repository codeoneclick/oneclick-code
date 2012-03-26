//
//  CResourceOre.h
//  iGaia
//
//  Created by sergey.sergeev on 2/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CResourceOre_h
#define iGaia_CResourceOre_h

#include "IGameResource.h"
#include "CModel.h"
#include "CSceneMgr.h"

class CResourceOre : public IGameResource
{
protected:
    CModel* m_pModel;
public:
    CResourceOre(void);
    ~CResourceOre(void);
    void Load(void);
    virtual void Update(void);
};

#endif
