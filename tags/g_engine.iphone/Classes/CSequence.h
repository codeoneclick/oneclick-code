//
//  CSequence.h
//  gEngine
//
//  Created by sergey.sergeev on 10/31/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CSequence_h
#define gEngine_CSequence_h
#include "CFXMLLoader.h"

class CSequence
{
protected:
    std::vector<CFXMLLoader::SFrame*> m_sequence;
public:
    CSequence();
    ~CSequence();
    inline std::vector<CFXMLLoader::SFrame*> Get_Sequence() { return m_sequence; }
    inline void Set_Sequence(std::vector<CFXMLLoader::SFrame*> _sequence) { m_sequence = _sequence; }
};

#endif
