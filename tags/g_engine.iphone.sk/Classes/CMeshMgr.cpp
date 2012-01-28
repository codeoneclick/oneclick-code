//
//  CMeshMgr.cpp
//  gEngine
//
//  Created by sergey.sergeev on 11/28/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CMeshMgr.h"

CMeshMgr::CMeshMgr()
{
    CParser_GMESH* pParser = new CParser_GMESH();
    pParser->Load("footman.gmesh");
    pParser->Commit();
    m_pStub = static_cast<CMesh::SSource*>(pParser->Get_Source());
}

CMeshMgr::~CMeshMgr()
{
    
}

IResource* CMeshMgr::Load(std::string _sName, IResource::E_THREAD _eThread)
{
    CMesh* pMesh = NULL;
    
    if(_eThread == IResource::E_THREAD_MAIN)
    {
        if( m_lContainer.find(_sName) != m_lContainer.end())
        {
            pMesh = static_cast<CMesh*>(m_lContainer[_sName]);
            pMesh->IncRefCount();
        }
        else
        {
            pMesh = new CMesh();
            pMesh->Set_Source(m_pStub);
            
            IParser* pParser = new CParser_GMESH();
            
            pParser->Load(_sName.c_str());
            if(pParser->Get_Status() != IParser::E_ERROR_STATUS)
            {
                pMesh->Set_Source(pParser->Get_Source());
            }
            delete pParser;
        }
    }
    else if(_eThread == IResource::E_THREAD_BACKGROUND)
    {
        if( m_lContainer.find(_sName) != m_lContainer.end())
        {
            pMesh = static_cast<CMesh*>(m_lContainer[_sName]);
            pMesh->IncRefCount();
        }
        else
        {
            if(m_lTaskPool.find(_sName) == m_lTaskPool.end())
            {
                m_lTaskPool[_sName] = new CParser_GMESH();
            }
            pMesh = new CMesh();
            pMesh->Set_Source(m_pStub);
            m_lContainer[_sName] = pMesh;
        }
    }
    
    return pMesh;
}

void CMeshMgr::Unload(std::string _sName)
{
    CMesh* pMesh = NULL;
    if( m_lContainer.find(_sName) != m_lContainer.end())
    {
        pMesh = static_cast<CMesh*>(m_lContainer[_sName]);
        pMesh->DecRefCount();
        if(pMesh->Get_RefCount() == 0)
        {
            delete pMesh;
            std::map<std::string, IResource*>::iterator pIterator = m_lContainer.find(_sName);
            m_lContainer.erase(pIterator);
        }
    }
}
