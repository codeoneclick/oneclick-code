//
//  IGameUnit.h
//  gEngine
//
//  Created by sergey.sergeev on 2/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_IGameUnit_h
#define gEngine_IGameUnit_h

#include "CModel.h"
#include "CSceneMgr.h"

class IGameUnit
{
protected:
    CModel* m_pModel;
public:
    IGameUnit(void);
    ~IGameUnit(void);
    CModel* Get_Model(void) { return m_pModel; }
    virtual void Load(void) = 0;
    virtual void Update(void) = 0;
};


#endif