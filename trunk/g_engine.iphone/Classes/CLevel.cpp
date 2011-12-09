//
//  CLevel.cpp
//  gEngine
//
//  Created by sergey.sergeev on 12/1/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CLevel.h"
#include "CSceneMgr.h"
#include "CPathFinder.h"

CLevel::CLevel()
{
    m_iWidth = 16;
    m_iHeight = 16;
}

CLevel::~CLevel()
{
    
}

void CLevel::Load(std::string _sName)
{
    std::vector<IResource::SResource> lResource;
    
    IResource::SResource tResource;
    tResource.m_sMesh = "footman.gmesh";
    tResource.m_eMesh = IResource::E_MESH_MOVIE;
    tResource.m_eShader = IResource::E_TEXTURE_VERTEX_DIFFUSE;
    tResource.m_eIntersector = IResource::E_INTERSECTOR_WITH_MODEL;
    tResource.m_lTextures.clear();
    tResource.m_lTextures.push_back("footman.pvr");
    tResource.m_bBatch = true;
    lResource.push_back(tResource);
    
    m_pPlayer = new CPlayer();
    m_pPlayer->Load(lResource);
    m_pPlayer->Set_Rotation(Vector3d(0.0f, 3.14f, 0.0f));
    m_pPlayer->Set_Position(Vector3d(0.0f, -0.8f, 2.0f));
    m_pPlayer->Set_Scale(Vector3d(0.02f,0.02f,0.02f));
    
    m_pEnemy = new CPlayer();
    m_pEnemy->Load(lResource);
    m_pEnemy->Set_Rotation(Vector3d(0.0f, 3.14f, 0.0f));
    m_pEnemy->Set_Position(Vector3d(5.0f, -0.8f, 2.0f));
    m_pEnemy->Set_Scale(Vector3d(0.02f,0.02f,0.02f));
    
    lResource.clear();
    
    tResource.m_eMesh = IResource::E_MESH_PRIMITIVE;
    tResource.m_ePrimitive = IResource::E_PRIMITIVE_PLANE;
    tResource.m_eShader = IResource::E_TEXTURE_VERTEX_DIFFUSE;
    tResource.m_eIntersector = IResource::E_INTERSECTOR_WITH_MODEL;
    tResource.m_lTextures.clear();
    tResource.m_lTextures.push_back("sector_01.pvr");
    tResource.m_bBatch = true;
    lResource.push_back(tResource);
    
    m_pNavigationMap = new int*[m_iWidth];
    m_pGround = new CSector**[m_iWidth];
    for( unsigned char i = 0; i < m_iWidth; i++)
    {
        m_pNavigationMap[i] = new int[m_iHeight];
        m_pGround[i] = new CSector*[m_iHeight];
        for( unsigned char j = 0; j < m_iHeight; j++)
        {
            m_pGround[i][j] = new CSector();
            m_pGround[i][j]->Load(lResource);
            m_pGround[i][j]->Set_Position(Vector3d((i - m_iWidth / 2), -0.8f, (j - m_iHeight / 2)));
            m_pGround[i][j]->Set_Rotation(Vector3d(1.57f, 0.0f, 0.0f));
            IGameObject::SNavigationIndex tNavigationIndex;
            tNavigationIndex.m_pIndex[0] = i;
            tNavigationIndex.m_pIndex[1] = j;
            m_pGround[i][j]->Set_NavigationIndex(tNavigationIndex);
            m_pNavigationMap[i][j] = 0;
        }
    }
}

void CLevel::Update(float _fTime)
{
    m_pPlayer->Update(_fTime);
    m_pEnemy->Update(_fTime);
    
    for( unsigned char i = 0; i < m_iWidth; i++)
    {
        for( unsigned char j = 0; j < m_iHeight; j++)
        {
            m_pGround[i][j]->Update(_fTime);
        }
    }
    
    CPlayer::E_PLAYER_STATE eState = m_pPlayer->Get_State();
    switch (eState) 
    {
        case CPlayer::E_PLAYER_STATE_PICK:
        {
            for( unsigned char i = 0; i < m_iWidth; i++)
            {
                for( unsigned char j = 0; j < m_iHeight; j++)
                {
                    if(m_pGround[i][j]->IsPicker())
                    {
                        IGameObject::SNavigationIndex tNavigationIndex = m_pGround[i][j]->Get_NavigationIndex();
                        CPathFinder::Instance()->FindPath(m_pNavigationMap, m_iWidth, m_iHeight, Vector2d(8.0f, 8.0f), Vector2d(tNavigationIndex.m_pIndex[0], tNavigationIndex.m_pIndex[1]));
                        CSceneMgr::Instance()->Set_Picker(NULL);
                        
                        std::vector<Vector2d> lPath = CPathFinder::Instance()->Get_Path();
                        std::vector<Vector2d>::iterator itStart = lPath.begin();
                        std::vector<Vector2d>::iterator itEnd = lPath.end();
                        while (itStart != itEnd)
                        {
                            m_pGround[static_cast<unsigned char>((*itStart).x)][static_cast<unsigned char>((*itStart).y)]->Set_Path(true);
                            itStart++;
                        }
                    }
                }
            }
        }
            break;
            
        default:
            break;
    }
}

