//
//  CSceneEngine.h
//  gEngine
//
//  Created by sergey.sergeev on 10/24/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CSceneEngine_h
#define gEngine_CSceneEngine_h

#include "CSprite.h"
#include "stdlib.h"
#include <string.h>
#include <map>
#include <Box2D/Box2D.h>

class CSceneEngine
{
private:
    static CSceneEngine *m_engine;
    std::map<std::string, INode*> m_source;
    b2World* m_pPhysicWorldController;
public:
    CSceneEngine();
    ~CSceneEngine();
    static CSceneEngine* Instance();
    void Update(float _fTime);
    void Render();
    INode *AddNode(CResourceController::SResource &_resource);
    INode *AddNode(CResourceController::SResource &_resource, INode *_node);
};


#endif
