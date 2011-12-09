//
//  CDataController.cpp
//  gEngine
//
//  Created by sergey.sergeev on 10/28/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CSequenceMgr.h"

CSequenceMgr::CSequenceMgr()
{
    CParser_SEQ* pParser = new CParser_SEQ();
    pParser->Load("Untitled_default.xml");
    m_pStub = static_cast<CSequence::SSource*>(pParser->Get_Source());
}

CSequenceMgr::~CSequenceMgr()
{
    
}

IResource* CSequenceMgr::Load(std::string _sName, IResource::E_PARSER _eParser, IResource::E_THREAD _eThread)
{
    CSequence* pSequence = NULL;
    
    if(_eThread == IResource::E_MAIN_THREAD)
    {
        if( m_lContainer.find(_sName) != m_lContainer.end())
        {
            pSequence = static_cast<CSequence*>(m_lContainer[_sName]);
            pSequence->IncRefCount();
        }
        else
        {
            pSequence = new CSequence();
            pSequence->Set_Source(m_pStub);
            CParser_SEQ* pParser = new CParser_SEQ(); 
            pParser->Load(_sName.c_str());
            if(pParser->Get_Status() != IParser::E_ERROR_STATUS)
            {
                pSequence->Set_Source(pParser->Get_Source());
            }
            delete pParser;
        }
    }
    else if(_eThread == IResource::E_BACKGROUND_THREAD)
    {
        if( m_lContainer.find(_sName) != m_lContainer.end())
        {
            pSequence = static_cast<CSequence*>(m_lContainer[_sName]);
            pSequence->IncRefCount();
        }
        else
        {
            if(m_lTaskPool.find(_sName) == m_lTaskPool.end())
            {
                m_lTaskPool[_sName] = new CParser_SEQ();
            }
            pSequence = new CSequence();
            pSequence->Set_Source(m_pStub);
            m_lContainer[_sName] = pSequence;
        }
    }
    
    return pSequence;
}

void CSequenceMgr::Unload(std::string _sName)
{
    CSequence* pSequence = NULL;
    if( m_lContainer.find(_sName) != m_lContainer.end())
    {
        pSequence = static_cast<CSequence*>(m_lContainer[_sName]);
        pSequence->DecRefCount();
        if(pSequence->Get_RefCount() == 0)
        {
            delete pSequence;
            std::map<std::string, IResource*>::iterator pIterator = m_lContainer.find(_sName);
            m_lContainer.erase(pIterator);
        }
    }
}












