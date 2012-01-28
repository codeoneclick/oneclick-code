//
//  CLightPoint.h
//  gEngine
//
//  Created by sergey.sergeev on 1/25/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CLightPoint_h
#define gEngine_CLightPoint_h

#include "ILight.h"
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include "CMesh.h"
#include "CShader.h"

class CLightPoint : public ILight
{
protected:
    static const CVector3d k_Size;
    CVector3d m_vMin;
    CVector3d m_vMax;
    CVector2d m_vDistanceToLightAt;
    CShader* m_pShader;
    CMesh* m_pMesh;
    bool m_bIsVisible;
public:
    CLightPoint(void);
    virtual ~CLightPoint(void);
    virtual void Update(void);
    virtual void Render(void);
    void Set_Visible(bool _bValue) { m_bIsVisible = _bValue; }
};


#endif
