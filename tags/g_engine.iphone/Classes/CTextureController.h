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
#include "CPVRLoader.h"
#include "IResourceController.h"


class CTextureController : public IResourceController
{
private:
    CTexture::SSource* m_pStub;
public:
    CTextureController();
    ~CTextureController();
    
    virtual IResource* Load(std::string _sName, IResource::E_LOAD_THREAD _eThread);
    virtual void Unload(std::string _sName);
};


#endif
