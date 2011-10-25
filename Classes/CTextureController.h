//
//  CTextureController.h
//  gEngine
//
//  Created by Snow Leopard User on 24/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CTextureController_h
#define gEngine_CTextureController_h

#include "PVRTTexture.h"
#include "stdlib.h"
#include <string>
#include <map>
#include "CTexture.h"

class CTextureController
{
private:
    std::map<std::string, CTexture*> m_container;
public:
    CTextureController();
    ~CTextureController();
    
    CTexture *Texture(std::string _sName);
};


#endif
