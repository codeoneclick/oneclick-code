//
//  CMatrix.h
//  gEngine
//
//  Created by sergey.sergeev on 10/19/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CMatrix_h
#define gEngine_CMatrix_h

#include "CVector.h"

#define MATH_PI 3.14159f
#define MATH_DEGREES 180.0f

struct Matrix4x4
{
    enum T_MATRIX { M_ZERO = 0, M_ONE };
    float m[16];
    
    Matrix4x4()
    {
        memset(&m, 0x0, 16 * sizeof(float));
    }
    
    Matrix4x4(T_MATRIX _value)
    {
        memset(&m, 0x0, 16 * sizeof(float));
        if(_value == M_ONE)
        {
            m[0]  = 1.0f; 
            m[5]  = 1.0f; 
            m[10] = 1.0f;
            m[15] = 1.0f;
        }
    }
};

inline Matrix4x4 operator* (const Matrix4x4& _mValue_01, const Matrix4x4& _mValue_02) {
    Matrix4x4 mValue(Matrix4x4::M_ZERO);
    for (int x = 0; x < 4; ++x)
    {
        for (int y = 0; y < 4; ++y)
        {
            for (int i=0;i<4;++i) 
            {
                mValue.m[x + y*4] += _mValue_01.m[i + y*4] * _mValue_02.m[x + i*4];
            }
        }
    }
    return mValue;
}

inline Matrix4x4 Rotation(float _fDegrees)
{
    float fRadians = _fDegrees * MATH_PI / MATH_DEGREES;
    float fSin = sinf(fRadians);
    float fCos = cosf(fRadians);
    Matrix4x4 mValue(Matrix4x4::M_ONE);
    mValue.m[0] = fCos; mValue.m[1] = fSin; mValue.m[4] = -fSin; mValue.m[5] = fCos;
    return mValue;
}

inline Matrix4x4 Scale(const Vector2d& _vValue)
{
    Matrix4x4 mValue(Matrix4x4::M_ONE);
    mValue.m[0] = _vValue.x; mValue.m[5] = _vValue.y; 
    return mValue;
}

inline Matrix4x4 Translation(const Vector3d& _vValue)
{
    Matrix4x4 mValue(Matrix4x4::M_ONE);
    mValue.m[12] = _vValue.x; mValue.m[13] = _vValue.y;  mValue.m[14] = _vValue.z;
    return mValue;
}

inline Matrix4x4 Orthographic(float _fWidth,float _fHeight,float _fzNear,float _fzFar)
{	
    Matrix4x4 mValue(Matrix4x4::M_ZERO);
    mValue.m[0] = 2.0f / _fWidth;
    mValue.m[5] = 2.0f / _fHeight;
    mValue.m[10] = _fzNear;
    mValue.m[15] = _fzFar;
    return mValue;
}


#endif
