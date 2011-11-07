//
//  CSceneController.h
//  gEngine
//
//  Created by sergey.sergeev on 10/24/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CSceneController_h
#define gEngine_CSceneController_h

#include "CSprite.h"
#include "CShape.h"
#include "CMovieClip.h"
#include "stdlib.h"
#include <string.h>
#include <map>

class CSceneController
{
private:
    static CSceneController *m_instance;
    std::map<std::string, INode*> m_source;
public:
    CSceneController();
    ~CSceneController();
    static CSceneController* Instance();
    void Update(float _fTime);
    void Render();
    INode* AddNode(INode::SResourceParam &_param);
    INode* AddNode(INode::SResourceParam &_param, INode* _node);
    void   RemoveNode(INode* _node);
    void   RemoveNode(std::string _sName);
};


#endif
