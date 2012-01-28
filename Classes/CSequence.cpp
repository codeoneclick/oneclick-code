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
    m_eParser = IResource::E_SEQ_PARSER;
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

void CSequence::Set_Source(void *_pSource)
{
    SSource* pSource = static_cast<SSource*>(_pSource);
    m_lFrames = pSource->m_lFrames;
}

