#ifndef _VECTOR3_H_
#define _VECTOR3_H_
#include <math.h>

class Vector3
{
public:

	union {
		struct {
			float x, y, z;
		};
		float v[3];
	};

	Vector3() : x(float(0)), y(float(0)), z(float(0)) {}
	Vector3( const Vector3& v ) : x(v.x), y(v.y), z(v.z) {}
	Vector3( float _x, float _y, float _z ) : x(_x), y(_y), z(_z) {}

	inline const Vector3 operator * ( float f ) const { return Vector3(x * f,y * f,z * f); }
	inline const Vector3 operator / ( float f ) const { return Vector3(x / f,y / f,z / f); }
	inline const Vector3 operator + ( const Vector3& v ) const { return Vector3(x + v.x,y + v.y,z + v.z); }
	inline const Vector3 operator - () const { return Vector3(-x,-y,-z); }
	inline const Vector3 operator - ( const Vector3& v ) const { return Vector3(x - v.x,y - v.y,z - v.z); }

	inline Vector3& operator *= ( float f ) { return *this = *this * f; }
	inline Vector3& operator /= ( float f ) { return *this = *this / f; }
	inline Vector3& operator += ( const Vector3& v ) { return *this = *this + v; }
	inline Vector3& operator -= ( const Vector3& v ) { return *this = *this - v; }

	inline operator float*() { return v; }
	inline operator const float*() const { return v; }

	inline float& operator[](int i) { return v[i]; }
	inline const float operator[](int i) const { return v[i]; }

	inline float length( void ) const { return (float)sqrt(x * x + y * y + z * z); }

	inline void normalize( void )
	{
		float inv = (float)sqrt(x * x + y * y + z * z);
		x *= inv;
		y *= inv;
		z *= inv;
	}
};

inline float dot( const Vector3& v1,const Vector3& v2 )
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
inline Vector3 cross( const Vector3& v1,const Vector3& v2 )
{
	return Vector3( v1.y * v2.z - v1.z * v2.y,
					v1.z * v2.x - v1.x * v2.z,
					v1.x * v2.y - v1.y * v2.x );
}

#endif