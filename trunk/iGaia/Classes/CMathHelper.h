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
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
    
    float Get_RotationForPlane(glm::vec3 _vPoint_01, glm::vec3 _vPoint_02, glm::vec3 _vPoint_03);
    glm::vec2 Get_RotationOnHeightmap(glm::vec3 _vPosition);
    float Get_RotationBetweenPoints(glm::vec3 _vPoint_01, glm::vec3 _vPoint_02);
    float Get_RotationBetweenPointsDot(glm::vec2 _vPoint_01, glm::vec2 _vPoint_02);
};

#endif /* defined(__iGaia__CMathHelper__) */
