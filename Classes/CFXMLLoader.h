//
//  CFXMLLoader.h
//  gEngine
//
//  Created by sergey.sergeev on 10/31/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CFXMLLoader_h
#define gEngine_CFXMLLoader_h

#include <map>
#include <vector>
#include "CVector.h"
#include "CSequence.h"
#include "ILoader.h"

class CFXMLLoader : public ILoader
{
private:
    CSequence::SSource* m_pSource;
    char* m_pData;
public:
    CFXMLLoader();
    ~CFXMLLoader();
    virtual void Load(const char* _sName);
    virtual void* Get_Source() { return m_pSource; }
    virtual void Commit() { };
};


#endif
