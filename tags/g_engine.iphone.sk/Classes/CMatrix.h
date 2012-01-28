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

struct CMatrix4x4
{
    enum E_MATRIX { E_MATRIX_ZERO = 0, E_MATRIX_ONE };
    float m[16];
    
    CMatrix4x4()
    {
        memset(&m, 0x0, 16 * sizeof(float));
    }
    
    CMatrix4x4(E_MATRIX _value)
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

inline CMatrix4x4 operator* (const CMatrix4x4& _mValue_01, const CMatrix4x4& _mValue_02)
{
    CMatrix4x4 mValue(CMatrix4x4::E_MATRIX_ZERO);
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

inline CVector3d operator* (const CMatrix4x4& _mValue_01, const CVector3d& _vValue_02)
{
    return CVector3d(_mValue_01.m[0] * _vValue_02.x + _mValue_01.m[4] * _vValue_02.y + _mValue_01.m[ 8] * _vValue_02.z + _mValue_01.m[12],
                    _mValue_01.m[1] * _vValue_02.x + _mValue_01.m[5] * _vValue_02.y + _mValue_01.m[ 9] * _vValue_02.z + _mValue_01.m[13],
                    _mValue_01.m[2] * _vValue_02.x + _mValue_01.m[6] * _vValue_02.y + _mValue_01.m[10] * _vValue_02.z + _mValue_01.m[14] );
}

inline CVector4d operator* (const CMatrix4x4& _mValue_01, const CVector4d& _vValue_02)
{
    CVector4d vOut;
    vOut.x = _mValue_01.m[0] * _vValue_02.x + _mValue_01.m[4] * _vValue_02.y + _mValue_01.m[ 8] * _vValue_02.z + _mValue_01.m[12] * _vValue_02.w;
    vOut.y = _mValue_01.m[1] * _vValue_02.x + _mValue_01.m[5] * _vValue_02.y + _mValue_01.m[ 9] * _vValue_02.z + _mValue_01.m[13] * _vValue_02.w;
    vOut.z = _mValue_01.m[2] * _vValue_02.x + _mValue_01.m[6] * _vValue_02.y + _mValue_01.m[10] * _vValue_02.z + _mValue_01.m[14] * _vValue_02.w;
    vOut.w = _mValue_01.m[3] * _vValue_02.x + _mValue_01.m[7] * _vValue_02.y + _mValue_01.m[11] * _vValue_02.z + _mValue_01.m[15] * _vValue_02.w;
    return vOut;
}

inline CMatrix4x4 RotationX(float fValue)
{
    CMatrix4x4 mValue(CMatrix4x4::E_MATRIX_ONE);
    mValue.m[5] = cos(fValue); mValue.m[6] = sin(fValue); mValue.m[9] = -sin(fValue); mValue.m[10] = cos(fValue);
    return mValue;
}
inline CMatrix4x4 RotationY(float fValue)
{
    CMatrix4x4 mValue(CMatrix4x4::E_MATRIX_ONE);
    mValue.m[0] = cos(fValue); mValue.m[2] = -sin(fValue); mValue.m[8] = sin(fValue); mValue.m[10] = cos(fValue);
    return mValue;
}
inline CMatrix4x4 RotationZ(float fValue)
{
    CMatrix4x4 mValue(CMatrix4x4::E_MATRIX_ONE);
    mValue.m[0] = cos(fValue); mValue.m[1] = sin(fValue); mValue.m[4] = -sin(fValue); mValue.m[5] = cos(fValue);
    return mValue;
    
}

inline CMatrix4x4 Scale(const CVector3d& vValue)
{
    CMatrix4x4 mValue(CMatrix4x4::E_MATRIX_ONE);
    mValue.m[0] = vValue.x; mValue.m[5] = vValue.y; mValue.m[10] = vValue.z;
    return mValue;
    
}

inline CMatrix4x4 Translation(const CVector3d& _vValue)
{
    CMatrix4x4 mValue(CMatrix4x4::E_MATRIX_ONE);
    mValue.m[12] = _vValue.x; mValue.m[13] = _vValue.y;  mValue.m[14] = _vValue.z;
    return mValue;
}

inline CMatrix4x4 Ortho(float _fWidth,float _fHeight,float _fzNear,float _fzFar)
{	
    CMatrix4x4 mValue(CMatrix4x4::E_MATRIX_ZERO);
    mValue.m[0] = 2.0f / _fWidth;
    mValue.m[5] = 2.0f / _fHeight;
    mValue.m[10] = _fzNear;
    mValue.m[15] = _fzFar;
    return mValue;
}

inline CMatrix4x4 Projection(float fovY, float aspect, float zNear, float zFar)
{
    CMatrix4x4 mValue(CMatrix4x4::E_MATRIX_ONE);
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

inline CMatrix4x4 View(const CVector3d& Eye,const CVector3d& At,const CVector3d& Up)
{
    CMatrix4x4 mValue(CMatrix4x4::E_MATRIX_ONE);
    CVector3d zAxis = At - Eye;
    zAxis.Normalize();
    CVector3d xAxis = Cross(Up,zAxis);
    xAxis.Normalize();
    CVector3d yAxis = Cross(zAxis,xAxis);
    
    mValue.m[0]  = xAxis.x; mValue.m[1]  = yAxis.x; mValue.m[2]  = zAxis.x;
    mValue.m[4]  = xAxis.y; mValue.m[5]  = yAxis.y; mValue.m[6]  = zAxis.y;
    mValue.m[8]  = xAxis.z; mValue.m[9]  = yAxis.z; mValue.m[10]  = zAxis.z;
    
    mValue.m[12]  = -Dot(xAxis, Eye); mValue.m[13]  = -Dot(yAxis, Eye); mValue.m[14]  = -Dot(zAxis, Eye);
    
    return mValue;
}

inline float Determinant(const CMatrix4x4& _mValue)
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

inline CMatrix4x4 Inverse(const CMatrix4x4& _mValue)
{
    CMatrix4x4 mValueOut;
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

inline CMatrix4x4 Transpose(const CMatrix4x4& _mValue)
{
    CMatrix4x4 mValueOut;
    for(unsigned int i = 0; i < 4; ++i)
    {
        for(unsigned int j = 0; j < 4; ++j)
        {
            mValueOut.m[i + j * 4] = _mValue.m[j + i * 4];
        }
    }
    return mValueOut;
}

inline CVector3d Unproject(const CVector3d& _vValue, const CMatrix4x4& _mView, const CMatrix4x4& _mProjection, const int* _pViewport)
{
    CVector4d vValueExt = CVector4d(_vValue.x, _vValue.y, _vValue.z, 1.0f);
    CMatrix4x4 mWorld = CMatrix4x4(CMatrix4x4::E_MATRIX_ONE);
    CMatrix4x4 mInvertViewProjection = Inverse(_mProjection * _mView);
    vValueExt.x = (vValueExt.x - _pViewport[0]) * 2.0f / _pViewport[2] - 1.0f;
    vValueExt.y = (vValueExt.y - _pViewport[1]) * 2.0f / _pViewport[3] - 1.0f;
    vValueExt.z = vValueExt.z * 2.0f - 1.0f;
    
    CVector4d vValueTemp = mInvertViewProjection * vValueExt;
    
    vValueTemp.x /= vValueTemp.w;
    vValueTemp.y /= vValueTemp.w;
    vValueTemp.z /= vValueTemp.w;
    
    CVector3d vValueOut = CVector3d(vValueTemp.x, vValueTemp.y, vValueTemp.z);
    return vValueOut;
    
    /*CMatrix4x4 mWorld = CMatrix4x4(CMatrix4x4::E_MATRIX_ONE);
    CMatrix4x4 mInvertViewProjection = Inverse(mWorld * _mView * _mProjection);
    
    CVector3d vValueTemp;
    vValueTemp.x = (((_vValue.x - static_cast<float>(_pViewport[0])) / ( static_cast<float>(_pViewport[2]))) * 2.0f) - 1.0f;
    vValueTemp.y = (((_vValue.y - static_cast<float>(_pViewport[1])) / ( static_cast<float>(_pViewport[3]))) * 2.0f) - 1.0f;
    vValueTemp.z = (_vValue.z - 0.0f) / ( 1.0f - 0.0f);
    float fW = (((vValueTemp.x * mInvertViewProjection.m[12]) + (vValueTemp.y * mInvertViewProjection.m[13])) + (vValueTemp.z * mInvertViewProjection.m[14])) + mInvertViewProjection.m[15];
    
    return vValueTemp / fW;*/
}



#endif
