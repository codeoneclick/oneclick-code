//
//  CMathHelper.cpp
//  iGaia
//
//  Created by sergey sergeev on 6/6/12.
//
//

#include "CMathHelper.h"
#include <cmath>
#include <limits>

CMathHelper* CMathHelper::m_pInstance = NULL;

float CMathHelper::k_PI = 3.14f;
float CMathHelper::k_HALF_PI = 1.57f;

CMathHelper::CMathHelper(void)
{
    
}

CMathHelper::~CMathHelper(void)
{
    
}

CMathHelper* CMathHelper::Instance(void)
{
    if(m_pInstance == NULL)
    {
        m_pInstance = new CMathHelper();
    }
    
    return m_pInstance;
}

bool CMathHelper::IsFloatEqual(float _fValue_01, float _fValue_02)
{
    return std::fabs(_fValue_01 - _fValue_02) < std::numeric_limits<float>::epsilon();
}

bool CMathHelper::IsFloatEqualWithDelta(float _fValue_01, float _fValue_02, float _fDelta)
{
    return std::fabs(_fValue_01 - _fValue_02) < _fDelta;
}