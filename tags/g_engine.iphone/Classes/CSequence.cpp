//
//  CSequence.cpp
//  gEngine
//
//  Created by sergey.sergeev on 10/31/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CSequence.h"
#include "CResource.h"

CSequence::CSequence()
{
    m_uiRefCount = 0;
    m_bDone = false;
}

CSequence::~CSequence()
{
    std::vector<SFrame*>::iterator pBeginIterator = m_lFrames.begin();
    std::vector<SFrame*>::iterator pEndIterator = m_lFrames.end();
    while (pBeginIterator != pEndIterator) 
    {
        SFrame* pFrame = (*pBeginIterator);
        delete pFrame;
        ++pBeginIterator;
    }
    m_lFrames.clear();
}

void CSequence::Release()
{
    CResource::Instance()->Unload_Sequence(m_sName);
}