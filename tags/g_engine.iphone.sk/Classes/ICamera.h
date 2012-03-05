//
//  CCamera.h
//  gEngine
//
//  Created by sergey.sergeev on 10/24/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_ICamera_h
#define gEngine_ICamera_h

#include "CMatrix.h"

class ICamera
{
protected:
    CVector3d m_vPosition;
    CVector3d m_vRotation;
    CVector3d m_vLookAt;
    CVector3d m_vUp;
    
    CMatrix4x4 m_mView;
    CMatrix4x4 m_mProjection;
    
    float m_fFovY;
    float m_fAspectRatio;
    float m_fFarPlane;
    float m_fNearPlane;
    float m_fMoveSpeed;
    float m_fDistanceToLookAt;
    float m_fHeightFromLookAt;
    
public:
    ICamera(void);
    virtual ~ICamera();
    
    void Init(int _iScreenWidth, int _iScreenHeight, float _fFovY, float _fFarPlane, float _fNearPlane);
    virtual void Update(void) = 0;
    
    virtual void OnScreenMove(CVector2d _vMoveDirection) = 0;
    
    const CMatrix4x4 Get_Projection(void) { return m_mProjection; }
    const CMatrix4x4 Get_View(void) { return m_mView; }
    
    void Set_FovY(float _fFovY) { m_fFovY = _fFovY; }
    void Set_FarPlane(float _fFarPlane) { m_fFarPlane = _fFarPlane; }
    void Set_NearPlane(float _fNearPlane) { m_fNearPlane = _fNearPlane; }
    void Set_DistanceToLookAt(float _fDistanceToLookAt) { m_fDistanceToLookAt = _fDistanceToLookAt; }
    float Get_DistanceToLookAt(void) { return m_fDistanceToLookAt; }
    void Set_HeightFromLookAt(float _fHeightFromLookAt) { m_fHeightFromLookAt = _fHeightFromLookAt; }
    float Get_HeightFromLookAt(void) { return m_fHeightFromLookAt; }
    void Set_AspectRation(float _fAspectRation) { m_fAspectRatio = _fAspectRation; }
    
    virtual CVector3d Get_Position(void) { return m_vPosition; }
    virtual void Set_Position(const CVector3d& _vPosition) { m_vPosition = _vPosition; }
    
    CVector3d Get_Rotation(void) { return m_vRotation; }
    void Set_Rotation(const CVector3d& _fRotation) { m_vRotation = _fRotation; }
    
    CVector3d Get_LookAt(void) { return m_vLookAt; }
    void Set_LookAt(const CVector3d& _vLookAt) { m_vLookAt = _vLookAt; }
};


#endif
