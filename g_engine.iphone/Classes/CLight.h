//
//  CLight.h
//  gEngine
//
//  Created by sergey.sergeev on 12/1/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CLight_h
#define gEngine_CLight_h

#include "CVector.h"

class CLight
{
protected:
    Vector3d m_vPosition;
    Vector3d m_vLightAt;
    Vector3d m_vRotation;
    Vector3d m_vDirection;
public:
    CLight();
    ~CLight();
    void Update();
    virtual void Set_Position(Vector3d _vPosition) { m_vPosition = _vPosition; }
    virtual Vector3d Get_Position() { return m_vPosition; }
    virtual void Set_Rotation(Vector3d _vRotation) { m_vRotation = _vRotation; }
    virtual Vector3d Get_Rotation() { return m_vRotation; }
    virtual void Set_LightAt(Vector3d _vLightAt) { m_vLightAt = _vLightAt; }
    virtual Vector3d Get_LightAt() { return m_vLightAt; }
    virtual Vector3d Get_Direction() { return m_vDirection; }
};

#endif
