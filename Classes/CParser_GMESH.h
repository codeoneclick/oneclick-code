//
//  CParser_GMESH.h
//  gEngine
//
//  Created by sergey.sergeev on 12/4/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CParser_GMESH_h
#define gEngine_CParser_GMESH_h

#include "stdlib.h"
#include <string>
#include "CVector.h"
#include "CMesh.h"
#include "IParser.h"

class CParser_GMESH : public IParser
{
private:
    CMesh::SSource* m_pSource;
    char*           m_pData;
public:
    CParser_GMESH();
    ~CParser_GMESH();
    
    virtual void  Load(const std::string& _sName);
    virtual void* Get_Source() { return m_pSource; }
    virtual void  Commit();
};


#endif
