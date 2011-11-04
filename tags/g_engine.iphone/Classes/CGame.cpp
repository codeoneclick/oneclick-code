//
//  CGame.cpp
//  gEngine
//
//  Created by Snow Leopard User on 26/10/2011.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CGame.h"
#include "CSceneController.h"
#include "CWindow.h"
#include "CInput.h"

CGame* CGame::m_game = NULL;

CGame::CGame()
{

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

void CGame::Load(float _fWidth, float _fHeight)
{
    m_pRenderController = new CRenderController(_fWidth, _fHeight);
    CWindow::Instance()->Init(_fWidth, _fHeight);
    /*CResource::SResource resource;
    resource.s_sName = "node_01";
    resource.s_vSize = Vector2d(32.0f, 32.0f);
    resource.s_vColor = Vector4d(1.0f,0.0f,0.0f,1.0f);
    resource.s_tNode = CResource::SResource::SPRITE;
    resource.s_vPosition = Vector3d(-160.0f,100.0f,0.0f);
    INode* node_01 = CSceneController::Instance()->AddNode(resource);*/
    
    /*resource.s_sName = "node_02";
    resource.s_vColor = Vector4d(0.0f,1.0f,0.0f,1.0f);
    resource.s_tNode = CResource::SResource::DSPRITE;
    INode* node_02 = CSceneController::Instance()->AddNode(resource);
    
    resource.s_sName = "node_03";
    resource.s_vColor = Vector4d(0.0f,0.0f,1.0f,1.0f);
    resource.s_tNode = CResource::SResource::DSPRITE;
    resource.s_vPosition = Vector3d(-32.0f,128.0f,0.0f);
    INode* node_03 = CSceneController::Instance()->AddNode(resource);
    
    CSceneController::Instance()->RemoveNode(node_03);
    CSceneController::Instance()->RemoveNode(node_02);
    CSceneController::Instance()->RemoveNode(node_01);
    
    resource.s_sName = "node_02";
    resource.s_vColor = Vector4d(0.0f,1.0f,0.0f,1.0f);
    resource.s_tNode = CResource::SResource::DSPRITE;
    resource.s_vPosition = Vector3d(0.0f,0.0f,0.0f);
    node_02 = CSceneController::Instance()->AddNode(resource);
    
    resource.s_sName = "node_03";
    resource.s_vColor = Vector4d(0.0f,0.0f,1.0f,1.0f);
    resource.s_tNode = CResource::SResource::DSPRITE;
    resource.s_vPosition = Vector3d(-64.0f,128.0f,0.0f);
    node_03 = CSceneController::Instance()->AddNode(resource);*/
    
}

void CGame::Update(float _fTime)
{
    static int index = 0;
    if(CInput::Instance()->Get_State() == CInput::E_TOUCH)
    {
        CResource::SResource resource;
        char pBuffer[16];
        sprintf (pBuffer, "node_%d",index);
        resource.s_sName = pBuffer;
        resource.s_vSize = Vector2d(32.0f, 32.0f);
        resource.s_vColor = Vector4d(1.0f,0.0f,0.0f,1.0f);
        resource.s_tNode = CResource::SResource::DSPRITE;
        resource.s_vPosition = Vector3d(CInput::Instance()->Get_Coord().x,CInput::Instance()->Get_Coord().y,0.0f);
        CSceneController::Instance()->AddNode(resource);
        index++;
    }
    
    static float angle = 0.0f;
    angle += 0.05f;
    Vector3d vCameraPosition = Vector3d(sinf(angle) * 64.0f, cosf(angle) * 64.0f, 0.0f); 
    CCamera::Instance()->Set_Position(vCameraPosition);
    
    CResource::Instance()->Update();
    CSceneController::Instance()->Update(_fTime);
}

void CGame::Render()
{
    m_pRenderController->BeginScene();
    CSceneController::Instance()->Render();
    m_pRenderController->EndScene();
}

