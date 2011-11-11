//
//  CTextureMgr.h
//  gEngine
//
//  Created by Snow Leopard User on 24/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CTextureMgr_h
#define gEngine_CTextureMgr_h

#include "stdlib.h"
#include <string>
#include <map>
#include "CParser_PVR.h"
#include "IResourceMgr.h"


class CTextureMgr : public IResourceMgr
{
private:
    CTexture::SSource* m_pStub;
public:
    CTextureMgr();
    ~CTextureMgr();
    
    virtual IResource* Load(std::string _sName, IResource::E_THREAD _eThread);
    virtual void Unload(std::string _sName);
};


#endif
