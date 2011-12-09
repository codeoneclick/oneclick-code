//
//  CCamera.h
//  gEngine
//
//  Created by sergey.sergeev on 10/24/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CCamera_h
#define gEngine_CCamera_h

#include "CMatrix.h"

class CCamera
{
private:
    static CCamera *m_pIntsance;

    Vector3d m_vPosition;
    Vector3d m_vRotation;
    Vector3d m_vLookAt;
    Vector3d m_vUp;
    
    Matrix4x4 m_mView;
    Matrix4x4 m_mProjection;
    
    float m_fFOV;
    float m_fFarPlane;
    float m_fNearPlane;
    float m_fMoveSpeed;
    float m_fDistanceToLookAt;
    float m_fHeightFromLookAt;
    
    void MoveForward();
    void MoveBackward();
    void MoveRight();
    void MoveLeft();
    
public:
    CCamera();
    ~CCamera();
    static CCamera *Instance();
    void Update(float _fTime);
    inline const Matrix4x4 Get_Projection() { return m_mProjection; }
    inline const Matrix4x4 Get_View() { return m_mView; }
    
    inline void Set_FOV(float _fFOV) { m_fFOV = _fFOV; }
    inline void Set_FarPlane(float _fFarPlane) { m_fFarPlane = _fFarPlane; }
    inline void Set_NearPlane(float _fNearPlane) { m_fNearPlane = _fNearPlane; }
    inline void Set_DistanceToLookAt(float _fDistanceToLookAt) { m_fDistanceToLookAt = _fDistanceToLookAt; }
    inline void Set_HeightFromLookAt(float _fHeightFromLookAt) { m_fHeightFromLookAt = _fHeightFromLookAt; }
    inline void Set_MoveSpeed(float _fMoveSpeed) { m_fMoveSpeed = _fMoveSpeed; } 
    
    inline Vector3d Get_Position() { return m_vPosition; }
    inline void Set_Position(const Vector3d& _vPosition) { m_vPosition = _vPosition; }
    
    inline Vector3d Get_Rotation() { return m_vRotation; }
    inline void Set_Rotation(const Vector3d& _fRotation) { m_vRotation = _fRotation; }
    
    inline Vector3d Get_LookAt() { return m_vLookAt; }
    inline void Set_LookAt(const Vector3d& _vLookAt) { m_vLookAt = _vLookAt; }
};


#endif
