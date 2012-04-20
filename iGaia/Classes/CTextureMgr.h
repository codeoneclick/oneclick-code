//
//  CTextureMgr.h
//  iGaia
//
//  Created by Snow Leopard User on 24/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CTextureMgr_h
#define iGaia_CTextureMgr_h

#include "stdlib.h"
#include <string>
#include <map>
#include "CParser_PVR.h"
#include "IResourceMgr.h"
#include "IResourceLoaderDelegate.h"


class CTextureMgr : public IResourceMgr
{
private:
    CTexture::SSource* m_pStub;
public:
    CTextureMgr(void);
    ~CTextureMgr(void);
    
    virtual IResource* Load(std::string _sName, IResource::E_THREAD _eThread, IResourceLoaderDelegate* _pResourceLoaderDelegate);
    virtual void Unload(std::string _sName);
};


#endif
