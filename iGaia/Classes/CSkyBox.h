//
//  CSkyBox.h
//  iGaia
//
//  Created by sergey sergeev on 4/26/12.
//
//

#ifndef __iGaia__CSkyBox__
#define __iGaia__CSkyBox__

#include <iostream>
#include "INode.h"

class CSkyBox : public INode
{
public:
    CSkyBox(void);
    ~CSkyBox(void);
    virtual void Load(const std::string& _sName, IResource::E_THREAD _eThread);
    virtual void Create_BoundingBox(void) { }
    virtual void Update(void);
    virtual void Render(E_RENDER_MODE _eMode);
    
    virtual void OnTouchEvent(ITouchDelegate* _pDelegateOwner);
    virtual void OnResourceLoadDoneEvent(IResource::E_RESOURCE_TYPE _eType, IResource* _pResource);
};

#endif /* defined(__iGaia__CSkyBox__) */