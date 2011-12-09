//
//  CPlayer.cpp
//  gEngine
//
//  Created by sergey.sergeev on 12/1/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CPlayer.h"
#include "CSceneMgr.h"

CPlayer::CPlayer()
{
    m_eState = E_PLAYER_STATE_IDLE;
}

CPlayer::~CPlayer()
{
    
}

void CPlayer::Load(std::vector<IResource::SResource> _lResource)
{
    m_pModel = CSceneMgr::Instance()->AddNode(_lResource[0]);
}

void CPlayer::Update(float _fTime)
{
    m_pModel->Set_Scale(m_vScale);
    m_pModel->Set_Position(m_vPosition);
    m_pModel->Set_Rotation(m_vRotation);
    
    if(CSceneMgr::Instance()->Get_Picker() != NULL)
    {
        m_eState = E_PLAYER_STATE_PICK;
    }
}

bool CPlayer::IsPicker()
{
    INode* pPickerNode = CSceneMgr::Instance()->Get_Picker();
    if(pPickerNode == m_pModel)
    {
        return true;
    }
    return false;
}

