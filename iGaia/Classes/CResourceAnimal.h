//
//  CResourceAnimal.h
//  iGaia
//
//  Created by sergey.sergeev on 2/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CResourceAnimal_h
#define iGaia_CResourceAnimal_h

#include "IGameResource.h"
#include "CModel.h"
#include "CSceneMgr.h"

class CResourceAnimal : public IGameResource
{
protected:
    CModel* m_pModel;
public:
    CResourceAnimal(void);
    ~CResourceAnimal(void);
    void Load(void);
    virtual void Update(void);
};


#endif
