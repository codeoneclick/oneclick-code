//
//  CSector.cpp
//  gEngine
//
//  Created by sergey.sergeev on 12/1/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CSector.h"
#include "CSceneMgr.h"

CSector::CSector()
{
    
}

CSector::~CSector()
{
    
}

void CSector::Load(std::vector<IResource::SResource> _lResource)
{
    m_pModel = CSceneMgr::Instance()->AddNode(_lResource[0]);
}

void CSector::Update(float _fTime)
{
    m_pModel->Set_Scale(m_vScale);
    m_pModel->Set_Position(m_vPosition);
    m_pModel->Set_Rotation(m_vRotation);
}

bool CSector::IsPicker()
{
    INode* pPickerNode = CSceneMgr::Instance()->Get_Picker();
    if(pPickerNode == m_pModel)
    {
        return true;
    }
    return false;
}

void CSector::Set_Path(bool _bValue)
{
    if(_bValue)
    {
        m_pModel->Intersect(true);
    }
    else
    {
        m_pModel->Intersect(false);
    }
}
