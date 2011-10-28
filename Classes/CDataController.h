//
//  CDataController.h
//  gEngine
//
//  Created by sergey.sergeev on 10/28/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CDataController_h
#define gEngine_CDataController_h

#include "stdlib.h"
#include <string>
#include <map>
#include <vector>
#include "CVector.h"

class CDataController
{
public:
    struct SSpriteData
    {
        struct SAnimation
        {
            Vector2d s_vPosition;
            Vector2d s_vSize;
        };
        std::vector<SAnimation> s_sequence;
    };
private:    
    std::map<std::string, SSpriteData*> m_spriteDataContainer;
    void Load(std::string _sName, SSpriteData* _pSprite);
public:
    CDataController();
    ~CDataController();
    SSpriteData* SpriteData(std::string _sName);
};


#endif
