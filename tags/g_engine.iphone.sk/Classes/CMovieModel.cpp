//
//  CMovieModel.cpp
//  gEngine
//
//  Created by sergey.sergeev on 12/1/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CMovieModel.h"
#include "CSceneMgr.h"
#include "CRenderMgr.h"

CMovieModel::CMovieModel()
{

}

CMovieModel::~CMovieModel()
{
    
}

void CMovieModel::Load(IResource::SResource _tResource)
{
    m_pMesh = static_cast<CMesh*>(CResourceMgr::Instance()->Load(_tResource.m_sName, IResource::E_MGR_MESH, _tResource.m_eThread));
    m_bIsBatching = _tResource.m_bIsBatching;
}

void CMovieModel::Update()
{
    INode::Update();
}

void CMovieModel::Render()
{
    CModel::Render();
}

