//
//  CMesh.cpp
//  gEngine
//
//  Created by sergey.sergeev on 11/28/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CMesh.h"

CMesh::CMesh()
{

}

CMesh::~CMesh()
{
    delete   m_pSource->m_pIB;
    delete[] m_pSource->m_pVB;
    delete m_pSource;
}

void CMesh::Set_Source(void *_pSource)
{
    m_pSource = static_cast<SSource*>(_pSource);
}
