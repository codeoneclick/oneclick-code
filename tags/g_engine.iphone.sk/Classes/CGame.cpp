//
//  CGame.cpp
//  gEngine
//
//  Created by Snow Leopard User on 26/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CGame.h"
#include "CInput.h"
#include "CResourceMgr.h"
#include "CCollisionMgr.h"
#include "CLightPoint.h"
#include "CLandscape.h"

CGame* CGame::m_game = NULL;

CGame::CGame()
{
    CRenderMgr::Instance();
}

CGame::~CGame()
{
    
}

CGame* CGame::Instance()
{
    if(m_game == NULL)
    {
        m_game = new CGame();
    }
    return m_game;
}

void CGame::Load()
{   
    m_pNode = CSceneMgr::Instance()->AddStaticModel("footman.gmesh", false, IResource::E_THREAD_BACKGROUND);
    m_pNode->Set_Texture("footman.pvr");
    m_pNode->Set_Scale(CVector3d(0.01f, 0.01f, 0.01f));
    m_pNode->Set_Shader(IResource::E_SHADER_PHONG);
    m_pNode->Create_BoundingBox();
    m_pNode->Create_ColliderBox();
    
    ICamera* pCamera = CSceneMgr::Instance()->CreateTargetCamera(45.0f, 0.1f, 1024.0f, m_pNode);
    CSceneMgr::Instance()->Set_Camera(pCamera);
    pCamera->Set_DistanceToLookAt(4.0f);
    pCamera->Set_HeightFromLookAt(4.0f);
    
    /*INode* pNode = CSceneMgr::Instance()->AddStandartModel(IResource::E_STANDART_MODEL_CUBE, false, IResource::E_THREAD_BACKGROUND);
    pNode->Set_Texture("footman.pvr");
    pNode->Set_Position(CVector3d(0.0f, 0.0f, 0.0f));
    pNode->Set_Scale(CVector3d(1.0f, 1.0f, 1.0f));
    pNode->Set_Shader(IResource::E_SHADER_COLOR);*/
    
    INode* pNode = CSceneMgr::Instance()->AddLandscapeModel("landscape.data");
    pNode->Set_Texture("TileSet.pvr");
    pNode->Set_Shader(IResource::E_SHADER_PHONG);
    CSceneMgr::Instance()->AddEventListener(pNode, CEventMgr::E_EVENT_TOUCH);
    pNode->Set_Position(CVector3d(0.0f, 0.0f, 0.0f));
    
    m_pLight = CSceneMgr::Instance()->Get_Light(ILight::E_LIGHT_MODE_POINT, 0);
    m_pLight->Set_Position(CVector3d(0.0f, 2.0f, 0.0f));
    m_pLight->Set_LightAt(CVector3d(4.0f, 0.0f, 4.0f));
    static_cast<CLightPoint*>(m_pLight)->Set_Visible(true);
    pNode->Set_Light(m_pLight);
}

void CGame::Update()
{
    //ICamera* pCamera = CSceneMgr::Instance()->Get_Camera();
    static float fAngle = 0.0f;
    fAngle += 0.1f;
    m_pNode->Set_Position(CCollisionMgr::Instance()->Get_Touch3DPoint());
    //static_cast<CLandscape*>(m_pNode)->EditTilesetData(CCollisionMgr::Instance()->Get_Touch3DPoint().x, CCollisionMgr::Instance()->Get_Touch3DPoint().z, CTileSetterMgr::LEVEL_03);
    m_pLight->Set_Rotation(CVector3d(0.0f, fAngle, 0.0f));
    CResourceMgr::Instance()->Update();
    CSceneMgr::Instance()->Update();
}

void CGame::Render()
{
    CSceneMgr::Instance()->Render();
    CRenderMgr::Instance()->End();

}










