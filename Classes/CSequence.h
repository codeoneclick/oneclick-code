//
//  CSequence.h
//  gEngine
//
//  Created by sergey.sergeev on 10/31/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CSequence_h
#define gEngine_CSequence_h
#include "stdlib.h"
#include <string>
#include <map>
#include <vector>
#include "CVector.h"

class CSequence
{
public:
    struct SFrame
    {
        Vector2d s_vPosition;
        Vector2d s_vSize;
    };

protected:
    std::vector<SFrame*> m_sequence;
    unsigned int m_uiRefCount;
    bool m_bDone;
public:
    CSequence();
    ~CSequence();
    inline std::vector<SFrame*> Get_Sequence() { return m_sequence; }
    inline void Set_SequenceLine(std::vector<SFrame*> _sequence) { m_sequence = _sequence; }
    inline bool Get_Done() { return m_bDone;}
    inline void Set_Done(bool _value) { m_bDone = _value; }
    inline void IncRefCount() { m_uiRefCount++; }
    inline void DecRefCount() { m_uiRefCount--; }
    inline unsigned int Get_RefCount() { return m_uiRefCount; }
};

#endif
