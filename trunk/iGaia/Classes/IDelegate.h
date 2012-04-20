//
//  IDelegate.h
//  iGaia
//
//  Created by sergey.sergeev on 2/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_IDelegate_h
#define iGaia_IDelegate_h

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class INode;
class IDelegate
{
public:
    IDelegate(void);
    ~IDelegate(void);
    virtual void OnTouchEvent(IDelegate* _pDelegateOwner) = 0;
    virtual void OnPhysicEvent(INode* _pNode, glm::vec3 _vPosition, glm::vec3 _vRotation, glm::vec3 _vScale) = 0;
};

#endif
