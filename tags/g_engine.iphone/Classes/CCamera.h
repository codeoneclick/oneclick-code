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
    
    Vector2d     m_vScale;
    Vector3d     m_vPosition;
    float        m_fRotation;
    
    Matrix4x4 *m_mProjection;
    Matrix4x4 *m_mView;
    
    Matrix4x4 m_mScale;
    Matrix4x4 m_mRotation;
    Matrix4x4 m_mTranslation;
    
public:
    CCamera();
    ~CCamera();
    static CCamera *Instance();
    void Update(float _fTime);
    inline float Get_Width() { return m_fWidth; }
    inline float Get_Height() { return m_fHeight; }
    inline Matrix4x4* Projection() { return m_mProjection; }
    inline Matrix4x4* View() { return m_mView; }
    inline Vector3d Get_Position() { return m_vPosition; }
    inline void Set_Position(Vector3d &_vPosition) { m_vPosition = _vPosition; }
    inline float Get_Rotation() { return m_fRotation; }
    inline void Set_Rotation(float _fRotation) { m_fRotation = _fRotation; }
    inline Vector2d Get_Scale() { return m_vScale; }
    inline void Set_Scale(Vector2d &_vScale) { m_vScale = _vScale; }
};


#endif
