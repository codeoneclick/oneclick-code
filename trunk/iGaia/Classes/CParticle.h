//
//  CParticle.h
//  iGaia
//
//  Created by code_oneclick on 4/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef __iGaia__CParticle__
#define __iGaia__CParticle__

#include <iostream>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_precision.hpp>
#include <stdlib.h>

class CParticle
{
public:
    glm::vec2 m_vCorner;
    glm::vec3 m_vPosition;
    glm::vec3 m_vVelocity;
    glm::u8vec4 m_vColor;
    float m_fTime;
public:
    CParticle(void);
    ~CParticle(void);
    void Update(void);
};

#endif /* defined(__iGaia__CParticle__) */
