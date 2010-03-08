#ifndef _G_VECTOR_H_
#define _G_VECTOR_H_

class gVector3D
{
public :
	
	float x,y,z;
	
	gVector3D() { this->x = 0.0f; this->y = 0.0f; this->z = 0.0f; }
	gVector3D(float x,float y,float z) { this->x = x; this->y = y; this->z =z;}
};

__forceinline gVector3D  operator- (const gVector3D& vValue) 
{ 
	return gVector3D(-vValue.x,-vValue.y,-vValue.z); 
}
__forceinline gVector3D  operator* (const gVector3D& vValue, float fValue)
{ 
	return gVector3D(vValue.x * fValue,vValue.y * fValue,vValue.z * fValue); 
}
__forceinline gVector3D  operator* (float fValue, const gVector3D& vValue) 
{ 
	return vValue*fValue; 
}
__forceinline gVector3D& operator*=(gVector3D& vValue, float fValue) 
{ 
	vValue.x *= fValue; vValue.y *= fValue; vValue.z *= fValue; 
	return vValue;
}
__forceinline gVector3D  operator/ (const gVector3D& vValue, float fValue)
{ 
	return gVector3D(vValue.x / fValue,vValue.y / fValue,vValue.z / fValue); 
}
__forceinline gVector3D& operator/=(gVector3D& vValue, float fValue) 
{ 
	vValue.x /= fValue; vValue.y /= fValue; vValue.z /= fValue; return vValue;
}

__forceinline gVector3D  operator+ (const gVector3D& vValue_01, const gVector3D& vValue_02)
{
	return gVector3D(vValue_01.x + vValue_02.x,vValue_01.y + vValue_02.y, vValue_01.z + vValue_02.z); 
}
__forceinline gVector3D& operator+=(gVector3D& vValue_01, const gVector3D& vValue_02)
{
	vValue_01.x += vValue_02.x; vValue_01.y += vValue_02.y; vValue_01.z += vValue_02.z;
	return vValue_01;
}
__forceinline gVector3D  operator- (const gVector3D& vValue_01, const gVector3D& vValue_02)
{
	return gVector3D(vValue_01.x - vValue_02.x,vValue_01.y - vValue_02.y, vValue_01.z - vValue_02.z); 
}
__forceinline gVector3D& operator-=(gVector3D& vValue_01, const gVector3D& vValue_02)
{
	vValue_01.x -= vValue_02.x; vValue_01.y -= vValue_02.y; vValue_01.z -= vValue_02.z;
	return vValue_01;
}

__forceinline float Length(const gVector3D& vValue)
{
	return sqrt(pow(vValue.x,2) + pow(vValue.y,2) + pow(vValue.z,2));
}

__forceinline gVector3D CrossProduct(gVector3D& vValue_01, const gVector3D& vValue_02)
{
	return gVector3D( vValue_01.y * vValue_02.z - vValue_01.z * vValue_02.y ,vValue_02.x * vValue_01.z - vValue_02.z * vValue_01.x ,vValue_01.x * vValue_02.y - vValue_01.y * vValue_02.x);
}
__forceinline float DotProduct(gVector3D& vValue_01, const gVector3D& vValue_02)
{
	return vValue_01.x*vValue_02.x + vValue_01.y*vValue_02.y + vValue_01.z*vValue_02.z;
}
	
__forceinline gVector3D Normalize(const gVector3D& vValue)
{
	return vValue / Length(vValue);
}

#endif