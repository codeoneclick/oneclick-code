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
protected:
    CShader* m_pShaderScreenNormalMap;
    CShader* m_pShaderShadowMap;
public:
    CModel(void);
    virtual ~CModel();
    virtual void Load(IResource::SResource _tResource);
    virtual void OnTouchEvent(void);
    virtual void OnPhysicEventUpdate(glm::vec3 _vPosition, glm::vec3 _vRotation, glm::vec3 _vScale);
    virtual void Update(void);
    virtual void Render(E_RENDER_MODE _eMode);
    virtual void OnLoadDone(E_RESOURCE_TYPE _eType, IResource* pResource);
};

#endif
