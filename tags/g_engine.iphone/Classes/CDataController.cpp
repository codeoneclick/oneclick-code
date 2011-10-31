//
//  CDataController.cpp
//  gEngine
//
//  Created by sergey.sergeev on 10/28/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CDataController.h"

CDataController::CDataController()
{
    
}

CDataController::~CDataController()
{
    
}

void CDataController::Get_Sequence(std::string _sName, CSequence* _pSequence)
{
    if( m_container.find(_sName) != m_container.end())
    {
        _pSequence->Set_Sequence(m_container[_sName]);
        return;
    }
    else
    {
        CFXMLLoader* pLoader = new CFXMLLoader();
        m_container[_sName] = pLoader->Load(_sName.c_str()); 
        _pSequence->Set_Sequence(m_container[_sName]);
        delete pLoader;
        return;
    }
}











