//
//  CMathHelper.h
//  iGaia
//
//  Created by sergey sergeev on 6/6/12.
//
//

#ifndef __iGaia__CMathHelper__
#define __iGaia__CMathHelper__

#include <iostream>

class CMathHelper
{
protected:
    static CMathHelper* m_pInstance;
public:
    static float k_PI;
    static float k_HALF_PI;
    CMathHelper(void);
    ~CMathHelper(void);
    static CMathHelper* Instance(void);
    bool IsFloatEqual(float _fValue_01, float _fValue_02);
    bool IsFloatEqualWithDelta(float _fValue_01, float _fValue_02, float _fDelta);
};

#endif /* defined(__iGaia__CMathHelper__) */
