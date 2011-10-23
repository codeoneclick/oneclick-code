#ifndef _MATRIX_H_
#define _MATRIX_H_
#include "Vector3d.h"

namespace math
{
struct Matrix4x4
{
	float m[16];
	Matrix4x4()
    {
		 for( int i = 0; i < 16; ++i ) 
			 m[i] = 0;
		 m[0]  = 1; 
		 m[5]  = 1; 
		 m[10] = 1;
		 m[15] = 1;
	}
};


__forceinline Matrix4x4 RotationX(float fValue)
{
        Matrix4x4 mValue;
        mValue.m[5] = cos(fValue); mValue.m[6] = sin(fValue); mValue.m[9] = -sin(fValue); mValue.m[10] = cos(fValue);
        return mValue;
}
__forceinline Matrix4x4 RotationY(float fValue)
{
        Matrix4x4 mValue;
        mValue.m[0] = cos(fValue); mValue.m[2] = -sin(fValue); mValue.m[8] = sin(fValue); mValue.m[10] = cos(fValue);
        return mValue;
}
__forceinline Matrix4x4 RotationZ(float fValue)
{
        Matrix4x4 mValue;
        mValue.m[0] = cos(fValue); mValue.m[1] = sin(fValue); mValue.m[4] = -sin(fValue); mValue.m[5] = cos(fValue);
        return mValue;
}
__forceinline Matrix4x4 Translation(const Vector3d& vValue)
{
        Matrix4x4 mValue;
        mValue.m[12] = vValue.x; mValue.m[13] = vValue.y; mValue.m[14] = vValue.z;
        return mValue;
}
__forceinline Matrix4x4 Scale(const Vector3d& vValue)
{
        Matrix4x4 mValue;
        mValue.m[0] = vValue.x; mValue.m[5] = vValue.y; mValue.m[10] = vValue.z;
        return mValue;
}

__forceinline float determinant(const Matrix4x4& mValue)
{
    float det;
    det =  mValue.m[0] * mValue.m[5] * mValue.m[10];
    det += mValue.m[4] * mValue.m[9] * mValue.m[2];
    det += mValue.m[8] * mValue.m[1] * mValue.m[6];
    det -= mValue.m[8] * mValue.m[5] * mValue.m[2];
    det -= mValue.m[4] * mValue.m[1] * mValue.m[10];
    det -= mValue.m[0] * mValue.m[9] * mValue.m[6];

    return det;
}

__forceinline Matrix4x4 Inverse(const Matrix4x4& mValue)
{
    Matrix4x4 mValueOut;
    float idet = 1.0f/determinant(mValue);

    mValueOut.m[0] =   (mValue.m[5] *  mValue.m[10] - mValue.m[9] *  mValue.m[6]) * idet;
    mValueOut.m[1] =  -(mValue.m[1] *  mValue.m[10] - mValue.m[9] *  mValue.m[2]) * idet;
    mValueOut.m[2] =   (mValue.m[1] *  mValue.m[6] -  mValue.m[5] *  mValue.m[2]) * idet;
    mValueOut.m[3] =    0.0;
    mValueOut.m[4] =  -(mValue.m[4] *  mValue.m[10] - mValue.m[8] *  mValue.m[6]) * idet;
    mValueOut.m[5] =   (mValue.m[0] *  mValue.m[10] - mValue.m[8] *  mValue.m[2]) * idet;
    mValueOut.m[6] =  -(mValue.m[0] *  mValue.m[6] -  mValue.m[4] *  mValue.m[2]) * idet;
    mValueOut.m[7] =    0.0;
    mValueOut.m[8] =   (mValue.m[4] *  mValue.m[9] -  mValue.m[8] *  mValue.m[5]) * idet;
    mValueOut.m[9] =  -(mValue.m[0] *  mValue.m[9] -  mValue.m[8] *  mValue.m[1]) * idet;
    mValueOut.m[10] =  (mValue.m[0] *  mValue.m[5] -  mValue.m[4] *  mValue.m[1]) * idet;
    mValueOut.m[11] =   0.0;
    mValueOut.m[12] = -(mValue.m[12] * mValueOut.m[0] +  mValue.m[13] * mValueOut.m[4] + mValue.m[14] * mValueOut.m[8]);
    mValueOut.m[13] = -(mValue.m[12] * mValueOut.m[1] +  mValue.m[13] * mValueOut.m[5] + mValue.m[14] * mValueOut.m[9]);
    mValueOut.m[14] = -(mValue.m[12] * mValueOut.m[2] +  mValue.m[13] * mValueOut.m[6] + mValue.m[14] * mValueOut.m[10]);
    mValueOut.m[15] =   1.0;

    return mValueOut;
}


__forceinline Matrix4x4 operator* (const Matrix4x4& mValue_01, const Matrix4x4& mValue_02) {
        Matrix4x4 mValue;
        for (int x = 0; x < 4; ++x)
                for (int y = 0; y < 4; ++y)
                {
                        mValue.m[x + y*4] = 0;
                        for (int i=0;i<4;++i) 
                                mValue.m[x + y*4] += mValue_01.m[i + y*4] * mValue_02.m[x + i*4];
                }
        return mValue;
}

__forceinline Matrix4x4 operator* (const Matrix4x4& mValue_01, const float fValue_02) {
        Matrix4x4 mValue;
        for (int x = 0; x < 4; ++x)
             for (int y = 0; y < 4; ++y)
				 mValue.m[x + y*4] = mValue_01.m[x + y*4]*fValue_02;

        return mValue;
}


__forceinline Vector3d operator* (const Matrix4x4& mValue_01, const Vector3d& vValue_02) 
{
		Vector3d vValue = Vector3d(0.0f,0.0f,0.0f);

		vValue.x = mValue_01.m[0] * vValue_02.x + mValue_01.m[4] * vValue_02.y + mValue_01.m[8] * vValue_02.z + mValue_01.m[12];
		vValue.y = mValue_01.m[1] * vValue_02.x + mValue_01.m[5] * vValue_02.y + mValue_01.m[9] * vValue_02.z + mValue_01.m[13];
		vValue.z = mValue_01.m[2] * vValue_02.x + mValue_01.m[6] * vValue_02.y + mValue_01.m[10] * vValue_02.z + mValue_01.m[14];
        return vValue;
}


__forceinline Vector3d operator* (const Vector3d& vValue_01, const Matrix4x4& mValue_02) 
{
		Vector3d vValue = Vector3d(0.0f,0.0f,0.0f);
		float wValue = 0.0f;
		wValue = mValue_02.m[12] + mValue_02.m[13] + mValue_02.m[14] + mValue_02.m[15];

		vValue.x = (mValue_02.m[0]*vValue_01.x + mValue_02.m[1]*vValue_01.y + mValue_02.m[2]*vValue_01.z + mValue_02.m[3]*1.0f)/wValue;
		vValue.y = (mValue_02.m[4]*vValue_01.x + mValue_02.m[5]*vValue_01.y + mValue_02.m[6]*vValue_01.z + mValue_02.m[7]*1.0f)/wValue;
		vValue.z = (mValue_02.m[8]*vValue_01.x + mValue_02.m[9]*vValue_01.y + mValue_02.m[10]*vValue_01.z + mValue_02.m[11]*1.0f)/wValue;
		
        return vValue;
}


__forceinline Matrix4x4 MatrixProjection(float fovY, float aspect, float zNear, float zFar)
{
        Matrix4x4 mValue;
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

__forceinline Matrix4x4 MatrixView(const Vector3d& Eye,const Vector3d& At,const Vector3d& Up)
{
        Matrix4x4 mValue;
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

static __forceinline Matrix4x4 Quaternion(const float _quaternion[4])
{
	Matrix4x4 mValue;

	float x = _quaternion[0];
	float y = _quaternion[1];
	float z = _quaternion[2];
	float w = _quaternion[3];

	float wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;
    float s  = 2.0f/(x*x + y*y + z*z + w*w); 
    x2 = x * s;    y2 = y * s;    z2 = z * s;
    xx = x * x2;   xy = x * y2;   xz = x * z2;
    yy = y * y2;   yz = y * z2;   zz = z * z2;
    wx = w * x2;   wy = w * y2;   wz = w * z2;

    mValue.m[0] = 1.0f - (yy + zz);
    mValue.m[4] = xy - wz;
    mValue.m[8] = xz + wy;

    mValue.m[1] = xy + wz;
    mValue.m[5] = 1.0f - (xx + zz);
    mValue.m[9] = yz - wx;

    mValue.m[2] = xz - wy;
    mValue.m[6] = yz + wx;
    mValue.m[10] = 1.0f - (xx + yy);

	return mValue;
}
};

#endif
