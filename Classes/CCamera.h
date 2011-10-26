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
public:
    CCamera();
    ~CCamera();
    static CCamera *Instance();
    void Init(float _width, float _height);
    inline float Get_Width() { return m_fWidth; }
    inline float Get_Height() { return m_fHeight; }
public:
    Matrix4x4 m_mProjection;
    Matrix4x4 m_mView;
};


#endif
