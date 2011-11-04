//
//  CSequence.h
//  gEngine
//
//  Created by sergey.sergeev on 10/31/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CSequence_h
#define gEngine_CSequence_h
#include "IResource.h"
#include <vector>
#include "CVector.h"


class CSequence : public IResource
{
public:
    struct SFrame
    {
        Vector2d s_vPosition;
        Vector2d s_vSize;
    };
    
    struct SSource
    {
        std::vector<CSequence::SFrame*> m_lFrames;
    };

protected:
    std::vector<SFrame*> m_lFrames;
public:
    CSequence();
    ~CSequence();
    inline std::vector<SFrame*> Get_Frames() { return m_lFrames; }
    virtual void Set_Source(void* _pSource);
};

#endif
