//
//  CTextureController.h
//  gEngine
//
//  Created by Snow Leopard User on 24/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CTextureController_h
#define gEngine_CTextureController_h

#include "stdlib.h"
#include <string>
#include <map>
#include "CTexture.h"
#include "CPVRLoader.h"

class CTextureController
{
private:
    std::map<std::string, CPVRLoader::SPVR> m_container;
public:
    CTextureController();
    ~CTextureController();
    void Get_Texture(std::string _sName, CTexture* _pTexture);
};


#endif
