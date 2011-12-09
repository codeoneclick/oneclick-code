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
    enum E_MATRIX { E_MATRIX_ZERO = 0, E_MATRIX_ONE };
    float m[16];
    
    Matrix4x4()
    {
        memset(&m, 0x0, 16 * sizeof(float));
    }
    
    Matrix4x4(E_MATRIX _value)
    {
        memset(&m, 0x0, 16 * sizeof(float));
        if(_value == E_MATRIX_ONE)
        {
            m[0]  = 1.0f; 
            m[5]  = 1.0f; 
            m[10] = 1.0f;
            m[15] = 1.0f;
        }
    }
};

inline Matrix4x4 operator* (const Matrix4x4& _mValue_01, const Matrix4x4& _mValue_02)
{
    Matrix4x4 mValue(Matrix4x4::E_MATRIX_ZERO);
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

inline Vector3d operator* (const Matrix4x4& _mValue_01, const Vector3d& _vValue_02)
{
    return Vector3d(_mValue_01.m[0] * _vValue_02.x + _mValue_01.m[4] * _vValue_02.y + _mValue_01.m[ 8] * _vValue_02.z + _mValue_01.m[12],
                    _mValue_01.m[1] * _vValue_02.x + _mValue_01.m[5] * _vValue_02.y + _mValue_01.m[ 9] * _vValue_02.z + _mValue_01.m[13],
                    _mValue_01.m[2] * _vValue_02.x + _mValue_01.m[6] * _vValue_02.y + _mValue_01.m[10] * _vValue_02.z + _mValue_01.m[14] );
}

inline Matrix4x4 RotationX(float fValue)
{
    Matrix4x4 mValue(Matrix4x4::E_MATRIX_ONE);
    mValue.m[5] = cos(fValue); mValue.m[6] = sin(fValue); mValue.m[9] = -sin(fValue); mValue.m[10] = cos(fValue);
    return mValue;
}
inline Matrix4x4 RotationY(float fValue)
{
    Matrix4x4 mValue(Matrix4x4::E_MATRIX_ONE);
    mValue.m[0] = cos(fValue); mValue.m[2] = -sin(fValue); mValue.m[8] = sin(fValue); mValue.m[10] = cos(fValue);
    return mValue;
}
inline Matrix4x4 RotationZ(float fValue)
{
    Matrix4x4 mValue(Matrix4x4::E_MATRIX_ONE);
    mValue.m[0] = cos(fValue); mValue.m[1] = sin(fValue); mValue.m[4] = -sin(fValue); mValue.m[5] = cos(fValue);
    return mValue;
    
}

inline Matrix4x4 Scale(const Vector3d& vValue)
{
    Matrix4x4 mValue(Matrix4x4::E_MATRIX_ONE);
    mValue.m[0] = vValue.x; mValue.m[5] = vValue.y; mValue.m[10] = vValue.z;
    return mValue;
    
}

inline Matrix4x4 Translation(const Vector3d& _vValue)
{
    Matrix4x4 mValue(Matrix4x4::E_MATRIX_ONE);
    mValue.m[12] = _vValue.x; mValue.m[13] = _vValue.y;  mValue.m[14] = _vValue.z;
    return mValue;
}

inline Matrix4x4 Orthographic(float _fWidth,float _fHeight,float _fzNear,float _fzFar)
{	
    Matrix4x4 mValue(Matrix4x4::E_MATRIX_ZERO);
    mValue.m[0] = 2.0f / _fWidth;
    mValue.m[5] = 2.0f / _fHeight;
    mValue.m[10] = _fzNear;
    mValue.m[15] = _fzFar;
    return mValue;
}

inline Matrix4x4 Projection(float fovY, float aspect, float zNear, float zFar)
{
    Matrix4x4 mValue(Matrix4x4::E_MATRIX_ONE);
    float yScale = 1/(tan(fovY/2));
    float xScale = yScale / aspect;
    
    mValue.m[0] = xScale;
    mValue.m[5] = yScale;
    mValue.m[10] = zFar/(zFar - zNear);
    mValue.m[11] = 1.0f;
    mValue.m[14] = -zNear*zFar/(zFar - zNear);
    mValue.m[15] = 0.0f;
    
    return mValue;
}

inline Matrix4x4 View(const Vector3d& Eye,const Vector3d& At,const Vector3d& Up)
{
    Matrix4x4 mValue(Matrix4x4::E_MATRIX_ONE);
    Vector3d zAxis = At - Eye;
    zAxis.normalize();
    Vector3d xAxis = cross(Vector3d(0.0f,1.0f,0.0f),zAxis);
    xAxis.normalize();
    Vector3d yAxis = cross(zAxis,xAxis);
    
    mValue.m[0]  = xAxis.x; mValue.m[1]  = yAxis.x; mValue.m[2]  = zAxis.x;
    mValue.m[4]  = xAxis.y; mValue.m[5]  = yAxis.y; mValue.m[6]  = zAxis.y;
    mValue.m[8]  = xAxis.z; mValue.m[9]  = yAxis.z; mValue.m[10]  = zAxis.z;
    
    mValue.m[12]  = -dot(xAxis, Eye); mValue.m[13]  = -dot(yAxis, Eye); mValue.m[14]  = -dot(zAxis, Eye);
    
    return mValue;
}

inline float Determinant(const Matrix4x4& _mValue)
{
    float fDeterminant;
    fDeterminant =  _mValue.m[0] * _mValue.m[5] * _mValue.m[10];
    fDeterminant += _mValue.m[4] * _mValue.m[9] * _mValue.m[2];
    fDeterminant += _mValue.m[8] * _mValue.m[1] * _mValue.m[6];
    fDeterminant -= _mValue.m[8] * _mValue.m[5] * _mValue.m[2];
    fDeterminant -= _mValue.m[4] * _mValue.m[1] * _mValue.m[10];
    fDeterminant -= _mValue.m[0] * _mValue.m[9] * _mValue.m[6];
    return fDeterminant;
}

inline Matrix4x4 Inverse(const Matrix4x4& _mValue)
{
    
    Matrix4x4 mValueOut;
    float fDeterminant = 1.0f / Determinant(_mValue);
    
    mValueOut.m[0] =   (_mValue.m[5] *  _mValue.m[10] - _mValue.m[9] *  _mValue.m[6]) * fDeterminant;
    mValueOut.m[1] =  -(_mValue.m[1] *  _mValue.m[10] - _mValue.m[9] *  _mValue.m[2]) * fDeterminant;
    mValueOut.m[2] =   (_mValue.m[1] *  _mValue.m[6] -  _mValue.m[5] *  _mValue.m[2]) * fDeterminant;
    mValueOut.m[3] =    0.0;
    mValueOut.m[4] =  -(_mValue.m[4] *  _mValue.m[10] - _mValue.m[8] *  _mValue.m[6]) * fDeterminant;
    mValueOut.m[5] =   (_mValue.m[0] *  _mValue.m[10] - _mValue.m[8] *  _mValue.m[2]) * fDeterminant;
    mValueOut.m[6] =  -(_mValue.m[0] *  _mValue.m[6] -  _mValue.m[4] *  _mValue.m[2]) * fDeterminant;
    mValueOut.m[7] =    0.0;
    mValueOut.m[8] =   (_mValue.m[4] *  _mValue.m[9] -  _mValue.m[8] *  _mValue.m[5]) * fDeterminant;
    mValueOut.m[9] =  -(_mValue.m[0] *  _mValue.m[9] -  _mValue.m[8] *  _mValue.m[1]) * fDeterminant;
    mValueOut.m[10] =  (_mValue.m[0] *  _mValue.m[5] -  _mValue.m[4] *  _mValue.m[1]) * fDeterminant;
    mValueOut.m[11] =   0.0;
    mValueOut.m[12] = -(_mValue.m[12] * mValueOut.m[0] +  _mValue.m[13] * mValueOut.m[4] + _mValue.m[14] * mValueOut.m[8]);
    mValueOut.m[13] = -(_mValue.m[12] * mValueOut.m[1] +  _mValue.m[13] * mValueOut.m[5] + _mValue.m[14] * mValueOut.m[9]);
    mValueOut.m[14] = -(_mValue.m[12] * mValueOut.m[2] +  _mValue.m[13] * mValueOut.m[6] + _mValue.m[14] * mValueOut.m[10]);
    mValueOut.m[15] =   1.0;
    
    return mValueOut;
}



#endif
