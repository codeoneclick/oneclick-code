//
//  CMatch3.h
//  gEngine
//
//  Created by sergey.sergeev on 11/7/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CMatch3_h
#define gEngine_CMatch3_h

#include "CRenderController.h"
#include "INode.h"
#include "CMatch3Level.h"

class CMatch3
{
private:
    INode* m_pGameContainer;
    INode* m_pLevel;
public:
    CMatch3();
    ~CMatch3();
    void Load();
    void Update(float _fTime);
    void Render();
};


#endif
