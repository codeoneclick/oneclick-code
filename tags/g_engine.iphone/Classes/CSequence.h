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
    std::vector<SFrame*> m_lFrames;
    unsigned int m_uiRefCount;
    bool m_bDone;
    std::string m_sName;
public:
    CSequence();
    ~CSequence();
    void Release();
    inline std::vector<SFrame*> Get_Frames() { return m_lFrames; }
    inline void Set_Frames(std::vector<SFrame*> _lFrames) { m_lFrames = _lFrames; }
    inline bool Get_Done() { return m_bDone;}
    inline void Set_Done(bool _value) { m_bDone = _value; }
    inline void IncRefCount() { m_uiRefCount++; }
    inline void DecRefCount() { m_uiRefCount--; }
    inline unsigned int Get_RefCount() { return m_uiRefCount; }
    inline void Set_Name(std::string _sName) { m_sName = _sName; }
    
};

#endif
