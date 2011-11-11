//
//  CParser_SEQ.h
//  gEngine
//
//  Created by sergey.sergeev on 10/31/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CParser_SEQ_h
#define gEngine_CParser_SEQ_h

#include <map>
#include <vector>
#include "CVector.h"
#include "CSequence.h"
#include "IParser.h"

class CParser_SEQ : public IParser
{
private:
    CSequence::SSource* m_pSource;
    char* m_pData;
public:
    CParser_SEQ();
    ~CParser_SEQ();
    virtual void Load(const char* _sName);
    virtual void* Get_Source() { return m_pSource; }
    virtual void Commit() { };
};


#endif
