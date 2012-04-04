//
//  IBuilding.h
//  iGaia
//
//  Created by sergey.sergeev on 2/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_IBuilding_h
#define iGaia_IBuilding_h

#include "CModel.h"
#include "CSceneMgr.h"

class IBuilding
{
protected:
    CModel* m_pModel;
public:
    IBuilding(void);
    ~IBuilding(void);
    virtual void Load(void) = 0;
    virtual void Update(void) = 0;
};

#endif
