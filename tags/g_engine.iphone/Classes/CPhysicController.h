//
//  CPhysicController.h
//  gEngine
//
//  Created by sergey.sergeev on 10/27/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CPhysicController_h
#define gEngine_CPhysicController_h
#include "INode.h"

class CPhysicController
{
private:
    static CPhysicController* m_controller;
    b2World* m_pWorld;
public:
    CPhysicController();
    ~CPhysicController();
    static CPhysicController* Instance();
    void Update(float _fTime);
    inline b2World* World() { return m_pWorld; }
};


#endif
