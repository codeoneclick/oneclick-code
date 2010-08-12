#ifndef _VECTOR_H_
#define _VECTOR_H_
#include <math.h>

namespace math
{
namespace vector
{
struct Vector3d
{
	union
	{
		struct { float x,y,z;      };
		struct { float r,g,b;      };
		struct { float value[3];   };
	};

	Vector3d()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	Vector3d(float x, float y, float z)
	{
		r = x;
		g = y;
		b = z;
	}
};

struct Vector2d
{
	union
	{
		struct { float x,y;      };
		struct { float u,v;      };
		struct { float value[2]; };
	};

	Vector2d()
	{
		x = 0;
		y = 0;
	}

	Vector2d(float x, float y)
	{
		u = x;
		v = y;
	}
};

struct Vector4d
{
	union
	{
		struct { float x,y,z,w;      };
		struct { float r,g,b,a;      };
		struct { float value[4];     };
	};

	Vector4d()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}

	Vector4d(float x, float y, float z, float w)
	{
		r = x;
		g = y;
		b = z;
		a = w;
	}
};

__forceinline Vector3d  operator-(const Vector3d& vValue) 
{ 
        return Vector3d(-vValue.x,-vValue.y,-vValue.z); 
}
__forceinline Vector3d  operator* (const Vector3d& vValue, float fValue)
{ 
        return Vector3d(vValue.x * fValue,vValue.y * fValue,vValue.z * fValue); 
}
__forceinline Vector3d  operator* (float fValue, const Vector3d& vValue) 
{ 
        return vValue*fValue; 
}
__forceinline Vector3d& operator*=(Vector3d& vValue, float fValue) 
{ 
        vValue.x *= fValue; vValue.y *= fValue; vValue.z *= fValue; 
        return vValue;
}
__forceinline Vector3d  operator/ (const Vector3d& vValue, float fValue)
{ 
        return Vector3d(vValue.x / fValue,vValue.y / fValue,vValue.z / fValue); 
}
__forceinline Vector3d& operator/=(Vector3d& vValue, float fValue) 
{ 
        vValue.x /= fValue; vValue.y /= fValue; vValue.z /= fValue; return vValue;
}

__forceinline Vector3d  operator+ (const Vector3d& vValue_01, const Vector3d& vValue_02)
{
        return Vector3d(vValue_01.x + vValue_02.x,vValue_01.y + vValue_02.y, vValue_01.z + vValue_02.z); 
}
__forceinline Vector3d& operator+=(Vector3d& vValue_01, const Vector3d& vValue_02)
{
        vValue_01.x += vValue_02.x; vValue_01.y += vValue_02.y; vValue_01.z += vValue_02.z;
        return vValue_01;
}
__forceinline Vector3d  operator- (const Vector3d& vValue_01, const Vector3d& vValue_02)
{
        return Vector3d(vValue_01.x - vValue_02.x,vValue_01.y - vValue_02.y, vValue_01.z - vValue_02.z); 
}
__forceinline Vector3d& operator-=(Vector3d& vValue_01, const Vector3d& vValue_02)
{
        vValue_01.x -= vValue_02.x; vValue_01.y -= vValue_02.y; vValue_01.z -= vValue_02.z;
        return vValue_01;
}

__forceinline float Length(const Vector3d& vValue)
{
        return sqrt(pow(vValue.x,2) + pow(vValue.y,2) + pow(vValue.z,2));
}

__forceinline Vector3d CrossProduct(Vector3d& vValue_01, const Vector3d& vValue_02)
{
        return Vector3d( vValue_01.y * vValue_02.z - vValue_01.z * vValue_02.y ,vValue_02.x * vValue_01.z - vValue_02.z * vValue_01.x ,vValue_01.x * vValue_02.y - vValue_01.y * vValue_02.x);
}
__forceinline float DotProduct(Vector3d& vValue_01, const Vector3d& vValue_02)
{
        return vValue_01.x*vValue_02.x + vValue_01.y*vValue_02.y + vValue_01.z*vValue_02.z;
}
        
__forceinline Vector3d Normalize(const Vector3d& vValue)
{
        return vValue / Length(vValue);
}

};
};

#endif
