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
    static CCamera *m_camera;
    float m_fWidth;
    float m_fHeight;
    

    Vector3d m_vPosition;
    Vector3d m_vRotation;
    Vector3d m_vLookAt;
    Vector3d m_vUp;
    
    Matrix4x4 m_mView;
    Matrix4x4 m_mProjection;
    
public:
    CCamera();
    ~CCamera();
    static CCamera *Instance();
    void Init(float _fWidth, float _fHeight); 
    void Update(float _fTime);
    inline float Get_Width() { return m_fWidth; }
    inline float Get_Height() { return m_fHeight; }
    inline Matrix4x4 Get_Projection() { return m_mProjection; }
    inline Matrix4x4 Get_View() { return m_mView; }
    inline Vector3d Get_Position() { return m_vPosition; }
    inline void Set_Position(Vector3d &_vPosition) { m_vPosition = _vPosition; }
    inline Vector3d Get_Rotation() { return m_vRotation; }
    inline void Set_Rotation(Vector3d _fRotation) { m_vRotation = _fRotation; }
};


#endif
