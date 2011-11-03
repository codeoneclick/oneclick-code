//
//  CFXMLLoader.h
//  gEngine
//
//  Created by sergey.sergeev on 10/31/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CFXMLLoader_h
#define gEngine_CFXMLLoader_h

#include "stdlib.h"
#include <string>
#include <map>
#include <vector>
#include "CVector.h"
#include "CSequence.h"

class CFXMLLoader
{
public:
    enum E_STATUS
    {
        E_STATUS_NONE,
        E_STATUS_START,
        E_STATUS_ERROR,
        E_STATUS_DONE,
    };
private:
    std::vector<CSequence::SFrame*> m_lFrames;
    E_STATUS m_eStatus;
public:
    CFXMLLoader();
    ~CFXMLLoader();
    void Load(std::string _sName);
    inline E_STATUS Get_Status() { return m_eStatus; }
    inline std::vector<CSequence::SFrame*> Get_Frames() { return m_lFrames; }
};


#endif
