//
//  CSequence.cpp
//  gEngine
//
//  Created by sergey.sergeev on 10/31/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CSequence.h"

CSequence::CSequence()
{
    m_uiRefCount = 0;
    m_bDone = false;
}

CSequence::~CSequence()
{
    std::vector<SFrame*>::iterator pBeginIterator = m_sequence.begin();
    std::vector<SFrame*>::iterator pEndIterator = m_sequence.end();
    while (pBeginIterator != pEndIterator) 
    {
        SFrame* pFrame = (*pBeginIterator);
        delete pFrame;
        ++pBeginIterator;
    }
    m_sequence.clear();
}