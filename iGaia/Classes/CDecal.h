//
//  CDecal.h
//  iGaia
//
//  Created by sergey sergeev on 5/20/12.
//
//

#ifndef __iGaia__CDecal__
#define __iGaia__CDecal__

#include <iostream>
#include "INode.h"

class CDecal : public INode
{
protected:
public:
    CDecal(void);
    ~CDecal(void);
    
    virtual void Load(const std::string& _sName, IResource::E_THREAD _eThread);
    virtual void Update(void);
    virtual void Render(E_RENDER_MODE _eMode);
    
    virtual void OnTouchEvent(ITouchDelegate* _pDelegateOwner);
    virtual void OnResourceLoadDoneEvent(IResource::E_RESOURCE_TYPE _eType, IResource* _pResource);
};

#endif /* defined(__iGaia__CDecal__) */
