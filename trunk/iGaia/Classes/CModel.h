//
//  CModel.h
//  iGaia
//
//  Created by sergey.sergeev on 11/17/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CModel_h
#define iGaia_CModel_h

#include "INode.h"

class CModel : public INode
{
public:
    CModel(void);
    ~CModel(void);
    virtual void Load(const std::string& _sName, IResource::E_THREAD _eThread);
    virtual void Update(void);
    virtual void Render(CShader::E_RENDER_MODE _eMode);
    
    virtual void OnTouchEvent(ITouchDelegate* _pDelegateOwner);
    virtual void OnResourceLoadDoneEvent(IResource::E_RESOURCE_TYPE _eType, IResource* _pResource);
};

#endif
