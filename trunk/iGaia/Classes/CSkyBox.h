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
protected:
public:
    CSkyBox(void);
    ~CSkyBox(void);
    virtual void Load(IResource::SResource _tResource);
    virtual void OnLoadDone(E_RESOURCE_TYPE _eType, IResource* pResource);
    virtual void OnTouchEvent(void);
    virtual void OnPhysicEventUpdate(glm::vec3 _vPosition, glm::vec3 _vRotation, glm::vec3 _vScale) { }
    virtual void Create_BoundingBox(void) { }
    virtual void Update(void);
    virtual void Render(E_RENDER_MODE _eMode);
};

#endif /* defined(__iGaia__CSkyBox__) */
