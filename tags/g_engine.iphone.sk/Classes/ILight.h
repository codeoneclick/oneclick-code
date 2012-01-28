//
//  ILight.h
//  gEngine
//
//  Created by sergey.sergeev on 12/1/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_ILight_h
#define gEngine_ILight_h

#include "CVector.h"
#include "CMatrix.h"

class ILight
{
public:
    enum E_LIGHT_MODE { E_LIGHT_MODE_DIRECTION = 0, E_LIGHT_MODE_POINT };
protected:
    CVector3d m_vPosition;
    CVector3d m_vLightAt;
    CVector3d m_vRotation;
    CVector3d m_vDirection;
    CMatrix4x4 m_mWorld;
public:
    ILight(void);
    ~ILight(void);
    virtual void Update(void);
    virtual void Render(void);
    virtual void Set_Position(CVector3d _vPosition) { m_vPosition = _vPosition; }
    virtual CVector3d Get_Position() { return m_vPosition; }
    virtual void Set_Rotation(CVector3d _vRotation) { m_vRotation = _vRotation; }
    virtual CVector3d Get_Rotation() { return m_vRotation; }
    virtual void Set_LightAt(CVector3d _vLightAt) { m_vLightAt = _vLightAt; }
    virtual CVector3d Get_LightAt() { return m_vLightAt; }
    virtual CVector3d Get_Direction() { return m_vDirection; }
};

#endif
