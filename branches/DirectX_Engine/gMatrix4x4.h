#ifndef _G_MATRIX_H_
#define _G_MATRIX_H_

#include "gVector3D.h"

class gMatrix4x4
{
public :
	float m[16];
	__forceinline void Identity() { for (int i=0; i<16; ++i) m[i] = 0; m[0] = 1; m[5] = 1; m[10] = 1; m[15] = 1; }
	gMatrix4x4()
	{
		this->Identity();
	}
};

__forceinline gMatrix4x4 RotationX(float fValue)
{
	gMatrix4x4 mValue;
	mValue.m[5] = cos(fValue); mValue.m[6] = sin(fValue); mValue.m[9] = -sin(fValue); mValue.m[10] = cos(fValue);
	return mValue;
}
__forceinline gMatrix4x4 RotationY(float fValue)
{
	gMatrix4x4 mValue;
	mValue.m[0] = cos(fValue); mValue.m[2] = -sin(fValue); mValue.m[8] = sin(fValue); mValue.m[10] = cos(fValue);
	return mValue;
}
__forceinline gMatrix4x4 RotationZ(float fValue)
{
	gMatrix4x4 mValue;
	mValue.m[0] = cos(fValue); mValue.m[1] = sin(fValue); mValue.m[4] = -sin(fValue); mValue.m[5] = cos(fValue);
	return mValue;
}
__forceinline gMatrix4x4 Translation(const gVector3D& vValue)
{
	gMatrix4x4 mValue;
	mValue.m[12] = vValue.x; mValue.m[13] = vValue.y; mValue.m[14] = vValue.z;
	return mValue;
}
__forceinline gMatrix4x4 Scale(const gVector3D& vValue)
{
	gMatrix4x4 mValue;
	mValue.m[0] = vValue.x; mValue.m[5] = vValue.y; mValue.m[10] = vValue.z;
	return mValue;
}

__forceinline float determinant(const gMatrix4x4& mValue)
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

__forceinline gMatrix4x4 Inverse(const gMatrix4x4& mValue)
{

	gMatrix4x4 mValueOut;
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


__forceinline gMatrix4x4 operator* (const gMatrix4x4& mValue_01, const gMatrix4x4& mValue_02) {
	gMatrix4x4 mValue;
	for (int x = 0; x < 4; ++x)
		for (int y = 0; y < 4; ++y)
		{
			mValue.m[x + y*4] = 0;
			for (int i=0;i<4;++i) 
				mValue.m[x + y*4] += mValue_01.m[i + y*4] * mValue_02.m[x + i*4];
		}
	return mValue;
}


__forceinline gMatrix4x4 MatrixProjection(float fovY, float aspect, float zNear, float zFar)
{
	gMatrix4x4 mValue;
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

__forceinline gMatrix4x4 MatrixView(const gVector3D& Eye,const gVector3D& At,const gVector3D& Up)
{
	gMatrix4x4 mValue;
	gVector3D zAxis = Normalize(At - Eye);
	gVector3D xAxis = Normalize(CrossProduct(gVector3D(0.0f,1.0f,0.0f),zAxis));
	gVector3D yAxis = CrossProduct(zAxis,xAxis);
	
	mValue.m[0]  = xAxis.x; mValue.m[1]  = yAxis.x; mValue.m[2]  = zAxis.x;
	mValue.m[4]  = xAxis.y; mValue.m[5]  = yAxis.y; mValue.m[6]  = zAxis.y;
	mValue.m[8]  = xAxis.z; mValue.m[9]  = yAxis.z; mValue.m[10]  = zAxis.z;
	
	mValue.m[12]  = -DotProduct(xAxis, Eye); mValue.m[13]  = -DotProduct(yAxis, Eye); mValue.m[14]  = -DotProduct(zAxis, Eye);

	return mValue;
}

#endif