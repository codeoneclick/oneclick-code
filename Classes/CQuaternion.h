//
//  CQuaternion.h
//  gEngine
//
//  Created by sergey.sergeev on 12/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CQuaternion_h
#define gEngine_CQuaternion_h

#include "math.h"
#include "CVector.h"

class CQuaternion
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
    
    CQuaternion() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}
    CQuaternion( const CQuaternion& _qValue ) : x(_qValue.x), y(_qValue.y), z(_qValue.z), w(_qValue.w) {}
    CQuaternion( float _x, float _y, float _z, float _w ) : x(_x), y(_y), z(_z), w(_w) {}

    inline const CQuaternion operator * ( float _fValue ) const { return CQuaternion(x * _fValue,y * _fValue,z * _fValue, w * _fValue); }
    inline const CQuaternion operator * ( const CQuaternion& _qValue ) const 
    { return CQuaternion(w * _qValue.x + x * _qValue.w + y * _qValue.z - z * _qValue.y, 
                         w * _qValue.y + y * _qValue.w + z * _qValue.x - x * _qValue.z,
                         w * _qValue.z + z * _qValue.w + x * _qValue.y - y * _qValue.x,
                         w * _qValue.w - x * _qValue.x - y * _qValue.y - z * _qValue.z); }
    
    inline const CQuaternion operator + ( const CQuaternion& _qValue ) const { return CQuaternion(x + _qValue.x,y + _qValue.y,z +_qValue.z, w + _qValue.w); }
    inline const CQuaternion operator - () const { return CQuaternion(-x,-y,-z, -w); }
};

inline CQuaternion Slerp(const CQuaternion& _qFrom, const CQuaternion& _qTo, float _fStep)
{
    CQuaternion qTemp;
    float fOmega, fCosom, fSinom, fScale_01, fScale_02;
    
    if(_fStep <= 0.0f)
    {
        return _qFrom;
    }
    else if(_fStep >= 1.0f)
    {
        return _qTo;
    }
    
    fCosom = _qFrom.x * _qTo.x + _qFrom.y * _qTo.y + _qFrom.z * _qTo.z + _qFrom.w * _qTo.w;
    
    if(fCosom < 0.0f)
    {
        qTemp = -_qTo;
        fCosom = -fCosom;
    }
    else
    {
        qTemp = _qTo;
    }
    
    if((1.0f - fCosom) > MATH_EPS)
    {
        fOmega = acosf(fCosom);
        fSinom = 1.0f / sinf(fOmega);
        fScale_01 = sinf((1.0f - _fStep) * fOmega) * fSinom;
        fScale_02 = sinf(_fStep * fOmega) * fSinom;
    }
    else
    {
        fScale_01 = 1.0f - _fStep;
        fScale_02 = _fStep;
    }
    
    return ((_qFrom * fScale_01) + (qTemp * fScale_02));
}



#endif
