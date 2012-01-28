//
//  CVector.h
//  gEngine
//
//  Created by sergey.sergeev on 10/19/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CVector_h
#define gEngine_CVector_h

#include "math.h"

class Vector2d
 {
 public:
     union 
     {
         struct 
         {
             float x, y;
         };
         float v[2];
     };
 
     Vector2d() : x(float(0)), y(float(0)) {}
     Vector2d( const Vector2d& v ) : x(v.x), y(v.y) {}
     Vector2d( float _x, float _y ) : x(_x), y(_y) {}
     inline float length( void ) const { return (float)sqrt(x * x + y * y); }
 };

class Vector4d
{
public:
    union 
    {
        struct 
        {
            float x, y, z, w;
        };
        float v[4];
    };
    
    Vector4d() : x(float(0)), y(float(0)), z(float(0)), w(float(0)) {}
    Vector4d( const Vector4d& v ) : x(v.x), y(v.y), z(v.z), w(v.w) {}
    Vector4d( float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
};

class Vector3d
{
public:
    
    union 
    {
        struct 
        {
            float x, y, z;
        };
        float v[3];
    };
    
    Vector3d() : x(float(0)), y(float(0)), z(float(0)) {}
    Vector3d( const Vector3d& v ) : x(v.x), y(v.y), z(v.z) {}
    Vector3d( float _x, float _y, float _z ) : x(_x), y(_y), z(_z) {}
    
    inline const Vector3d operator * ( float f ) const { return Vector3d(x * f,y * f,z * f); }
    inline const Vector3d operator / ( float f ) const { return Vector3d(x / f,y / f,z / f); }
    inline const Vector3d operator + ( const Vector3d& v ) const { return Vector3d(x + v.x,y + v.y,z + v.z); }
    inline const Vector3d operator - () const { return Vector3d(-x,-y,-z); }
    inline const Vector3d operator - ( const Vector3d& v ) const { return Vector3d(x - v.x,y - v.y,z - v.z); }
    
    inline Vector3d& operator *= ( float f ) { return *this = *this * f; }
    inline Vector3d& operator /= ( float f ) { return *this = *this / f; }
    inline Vector3d& operator += ( const Vector3d& v ) { return *this = *this + v; }
    inline Vector3d& operator -= ( const Vector3d& v ) { return *this = *this - v; }
    
    inline operator float*() { return v; }
    inline operator const float*() const { return v; }
    
    inline float& operator[](int i) { return v[i]; }
    inline const float operator[](int i) const { return v[i]; }
    
    inline float length( void ) const { return (float)sqrt(x * x + y * y + z * z); }
    
    inline void normalize( void )
    {
        float _length = length();
        x /= _length;
        y /= _length;
        z /= _length;
    }
};

inline float dot( const Vector3d& v1,const Vector3d& v2 )
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
inline Vector3d cross( const Vector3d& v1,const Vector3d& v2 )
{
    return Vector3d(v1.y * v2.z - v1.z * v2.y,
                    v1.z * v2.x - v1.x * v2.z,
                    v1.x * v2.y - v1.y * v2.x );
}

#define MATH_PI 3.14159f
#define MATH_DEGREES 180.0f

inline float DegToRad(float _value)
{
    return _value * MATH_DEGREES / MATH_PI;
}

inline float RadToDeg(float _value)
{
    return _value * MATH_PI / MATH_DEGREES;
}


#endif
