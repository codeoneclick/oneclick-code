//
//  CShadowPlane.h
//  iGaia
//
//  Created by sergey sergeev on 5/15/12.
//
//

#ifndef __iGaia__CShadowPlane__
#define __iGaia__CShadowPlane__

#include <iostream>
#include "INode.h"

class CShadowPlane : public INode
{
protected:
public:
    CShadowPlane(void);
    ~CShadowPlane(void);
    
    virtual void Load(IResource::SResource _tResource);
    virtual void OnLoadDone(E_RESOURCE_TYPE _eType, IResource* pResource);
    virtual void OnTouchEvent(void);
    virtual void OnPhysicEventUpdate(glm::vec3 _vPosition, glm::vec3 _vRotation, glm::vec3 _vScale) { }
    virtual void Create_BoundingBox(void) { }
    virtual void Update(void);
    virtual void Render(E_RENDER_MODE _eMode);
};

#endif /* defined(__iGaia__CShadowPlane__) */
