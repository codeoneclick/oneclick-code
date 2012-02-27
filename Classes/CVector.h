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

#define MATH_RAD_TO_DEG 0.01745329f
#define MATH_DEG_TO_RAD 57.3248408f
#define MATH_PI 3.14159f
#define MATH_DEGREES 180.0f
#define MATH_EPS (1e-6f)

class CColor4
{
public:
    union 
    {
        struct 
        {
            unsigned char r, g, b, a;
        };
        unsigned char v[4];
    };
    
    CColor4() : r(0), g(0), b(0), a(0) {}
    CColor4( const CColor4& _color ) : r(_color.r), g(_color.g), b(_color.b), a(_color.a) {}
    CColor4( unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a ) : r(_r), g(_g), b(_b), a(_a) {}
};

class CVector2d
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
 
     CVector2d() : x(float(0)), y(float(0)) {}
     CVector2d( const CVector2d& v ) : x(v.x), y(v.y) {}
     CVector2d( float _x, float _y ) : x(_x), y(_y) {}
     
     inline const CVector2d operator * ( float f ) const { return CVector2d( x * f,y * f ); }
     inline const CVector2d operator / ( float f ) const { return CVector2d( x / f,y / f ); }
     inline const CVector2d operator + ( const CVector2d& v ) const { return CVector2d( x + v.x,y + v.y ); }
     inline const CVector2d operator - () const { return CVector2d( -x,-y ); }
     inline const CVector2d operator - ( const CVector2d& v ) const { return CVector2d( x - v.x,y - v.y ); }
     
     inline CVector2d& operator *= ( float f ) { return *this = *this * f; }
     inline CVector2d& operator /= ( float f ) { return *this = *this / f; }
     inline CVector2d& operator += ( const CVector2d& v ) { return *this = *this + v; }
     inline CVector2d& operator -= ( const CVector2d& v ) { return *this = *this - v; }
     
     inline operator float*() { return v; }
     inline operator const float*() const { return v; }
     
     inline float& operator[](int i) { return v[i]; }
     inline const float operator[](int i) const { return v[i]; }
     
     inline float Length( void ) const { return sqrtf( x * x + y * y ); }
};

class CVector4d
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
    
    CVector4d() : x(float(0)), y(float(0)), z(float(0)), w(float(0)) {}
    CVector4d( const CVector4d& v ) : x(v.x), y(v.y), z(v.z), w(v.w) {}
    CVector4d( float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
    
    inline const CVector4d operator * ( float f ) const { return CVector4d( x * f,y * f, z * f, w * f ); }
    inline const CVector4d operator / ( float f ) const { return CVector4d( x / f,y / f, z * f, w * f ); }
    inline const CVector4d operator + ( const CVector4d& v ) const { return CVector4d( x + v.x,y + v.y, z + v.z, w + v.w ); }
    inline const CVector4d operator - () const { return CVector4d( -x, -y, -z, -w ); }
    inline const CVector4d operator - ( const CVector4d& v ) const { return CVector4d( x - v.x,y - v.y, z - v.z, w - v.w ); }
    
    inline CVector4d& operator *= ( float f ) { return *this = *this * f; }
    inline CVector4d& operator /= ( float f ) { return *this = *this / f; }
    inline CVector4d& operator += ( const CVector4d& v ) { return *this = *this + v; }
    inline CVector4d& operator -= ( const CVector4d& v ) { return *this = *this - v; }
    
    inline operator float*() { return v; }
    inline operator const float*() const { return v; }
    
    inline float& operator[](int i) { return v[i]; }
    inline const float operator[](int i) const { return v[i]; }
};

class CVector3d
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
    
    CVector3d() : x(float(0)), y(float(0)), z(float(0)) {}
    CVector3d( const CVector3d& v ) : x(v.x), y(v.y), z(v.z) {}
    CVector3d( float _x, float _y, float _z ) : x(_x), y(_y), z(_z) {}
    
    inline const CVector3d operator * ( float f ) const { return CVector3d(x * f,y * f,z * f); }
    inline const CVector3d operator / ( float f ) const { return CVector3d(x / f,y / f,z / f); }
    inline const CVector3d operator + ( const CVector3d& v ) const { return CVector3d(x + v.x,y + v.y,z + v.z); }
    inline const CVector3d operator - () const { return CVector3d(-x,-y,-z); }
    inline const CVector3d operator - ( const CVector3d& v ) const { return CVector3d(x - v.x,y - v.y,z - v.z); }
    
    inline CVector3d& operator *= ( float f ) { return *this = *this * f; }
    inline CVector3d& operator /= ( float f ) { return *this = *this / f; }
    inline CVector3d& operator += ( const CVector3d& v ) { return *this = *this + v; }
    inline CVector3d& operator -= ( const CVector3d& v ) { return *this = *this - v; }
    
    inline operator float*() { return v; }
    inline operator const float*() const { return v; }
    
    inline float& operator[](int i) { return v[i]; }
    inline const float operator[](int i) const { return v[i]; }
    
    inline float Length( void ) const { return sqrtf(x * x + y * y + z * z); }
    
    inline void Normalize( void )
    {
        float _length = Length();
        x /= _length;
        y /= _length;
        z /= _length;
    }
};

inline bool IsEqual(const CVector2d& v1,const CVector2d& v2, float _fValue)
{
    CVector2d vEqual = v1 - v2;
    for(unsigned int i = 0; i < 2; ++i)
    {
        if(fabs(vEqual.v[i]) > _fValue)
        {
            return false;
        }
    }
    return true;
}

inline bool IsEqual(const CVector3d& v1,const CVector3d& v2, float _fValue)
{
    CVector3d vEqual = v1 - v2;
    for(unsigned int i = 0; i < 3; ++i)
    {
        if(fabs(vEqual.v[i]) > _fValue)
        {
            return false;
        }
    }
    return true;
}

inline CVector3d Lerp(const CVector3d& _vValue_01, const CVector3d& _vValue_02, float _fStep)
{
    CVector3d vValueOut = _vValue_01 + (_vValue_02 - _vValue_01) * _fStep;
    return vValueOut;
}

inline CVector2d Lerp(const CVector2d& _vValue_01, const CVector2d& _vValue_02, float _fStep)
{
    CVector2d vValueOut = _vValue_01 + (_vValue_02 - _vValue_01) * _fStep;
    return vValueOut;
}

inline float Dot( const CVector3d& v1,const CVector3d& v2 )
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
inline CVector3d Cross( const CVector3d& v1,const CVector3d& v2 )
{
    return CVector3d(v1.y * v2.z - v1.z * v2.y,
                     v1.z * v2.x - v1.x * v2.z,
                     v1.x * v2.y - v1.y * v2.x );
}

inline float AngleFromVectorToVector(CVector3d _vValue_01, CVector3d _vValue_02)
{
    float fVectorLength = sqrtf(pow(_vValue_02.x - _vValue_01.x, 2) + pow(_vValue_02.z - _vValue_01.z, 2));
    float angleX = MATH_PI * (_vValue_02.x - _vValue_01.x) / fVectorLength;
    float angleZ = MATH_PI * (_vValue_02.z - _vValue_01.z) / fVectorLength;
    float angleY = 0.0f;
    if (angleX > 0) 
        angleY = angleZ/2.0f;
    if (angleX < 0) 
        angleY = -angleZ/2.0f - MATH_PI;
    return  -angleY;
}

class CRay3d
{
public:
    CVector3d m_vDirection;
    CVector3d m_vOrigin;
    CVector3d m_vEnd;
};

#endif
