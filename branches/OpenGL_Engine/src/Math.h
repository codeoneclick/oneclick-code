#ifndef _MATH_H_
#define _MATH_H_

namespace Math
{
	namespace Matrix
	{
		struct Matrix4x4
		{
			float m[16];
		};
	}

	namespace Vector
	{
		/////////////////////////////////////////////////////////////////////
		struct Vector2d
		{
			union
			{
				struct { float x,y;      };
				struct { float u,v;      };
				struct { float value[2]; };
			};
		};
		struct Vector3d
		{
			union
			{
				struct { float x,y,z;      };
				struct { float r,g,b;      };
				struct { float value[3];   };
			};
		};
		struct Vector4d
		{
			union
			{
				struct { float x,y,z,w;      };
				struct { float r,g,b,a;      };
				struct { float value[4];     };
			};
		};
		/////////////////////////////////////////////////////////////////////

		__forceinline void Add(const Vector3d* value_01,const Vector3d* value_02,Vector3d* value_res)
		{
			value_res->x = value_01->x + value_02->x; 
			value_res->y = value_01->y + value_02->y; 
			value_res->z = value_01->z + value_02->z; 
		}

		__forceinline void Sub(const Vector3d* value_01,const Vector3d* value_02,Vector3d* value_res)
		{
			value_res->x = value_01->x - value_02->x; 
			value_res->y = value_01->y - value_02->y; 
			value_res->z = value_01->z - value_02->z; 
		}

		__forceinline void Scale(const Vector3d* value_01,float value_02,Vector3d* value_res)
		{
			value_res->x = value_01->x*value_02; 
			value_res->y = value_01->y*value_02; 
			value_res->z = value_01->z*value_02; 
		}

		__forceinline void Cross(const Vector3d* value_01,const Vector3d* value_02,Vector3d* value_res)
		{
			value_res->x = value_01->y * value_02->z - value_01->z * value_02->y; 
			value_res->y = value_02->x * value_01->z - value_02->z * value_01->x; 
			value_res->z = value_01->x * value_02->y - value_01->y * value_02->x;
		}
		__forceinline float DotProduct(const Vector3d* value_01, const Vector3d* value_02)
		{
			return value_01->x*value_02->x + value_01->y*value_02->y + value_01->z*value_02->z;
		}

		__forceinline float Length(const Vector3d* value_01)
		{
			return sqrt(value_01->x*value_01->x + value_01->y*value_01->y + value_01->z*value_01->z);
		}

		__forceinline void Normalize(const Vector3d* value_01,Vector3d* value_02)
		{
			float vectorLength = Length(value_01);
			value_02->x = value_01->x / vectorLength;
			value_02->y = value_01->y / vectorLength;
			value_02->z = value_01->z / vectorLength;
		}
	}
}

#endif