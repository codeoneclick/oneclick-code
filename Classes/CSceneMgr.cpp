//
//  CSceneMgr.cpp
//  gEngine
//
//  Created by sergey.sergeev on 12/1/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CSceneMgr.h"
#include "CModel.h"
#include "CLandscape.h"
#include "CMovieModel.h"
#include "CRenderMgr.h"
#include "CCollisionMgr.h"
#include "CCameraFree.h"
#include "CCameraTarget.h"
#include "CWindow.h"
#include "CRenderMgr.h"
#include "CBatchMgr.h"
#include "CLightPoint.h"


CSceneMgr* CSceneMgr::m_pInsatnce = NULL;
const unsigned int CSceneMgr::k_MAX_LIGHTS = 8;

CSceneMgr::CSceneMgr()
{
    m_pCamera = NULL;
    CBatchMgr::Instance();
    
    m_lLights[ILight::E_LIGHT_MODE_DIRECTION] = new CLightPoint();
    static_cast<CLightPoint*>(m_lLights[ILight::E_LIGHT_MODE_DIRECTION])->Set_Visible(false);
    
    for(unsigned int i = 0; i < k_MAX_LIGHTS; i++)
    {
        m_lLights[ILight::E_LIGHT_MODE_POINT + i] = new CLightPoint();
        static_cast<CLightPoint*>(m_lLights[ILight::E_LIGHT_MODE_POINT + i])->Set_Visible(false);
    }
}

CSceneMgr::~CSceneMgr()
{
    
}

CSceneMgr* CSceneMgr::Instance()
{
    if( m_pInsatnce == NULL)
    {
        m_pInsatnce = new CSceneMgr();
    }    
    return m_pInsatnce;
}

INode* CSceneMgr::AddStaticModel(const std::string &_sName, bool _isBatching, IResource::E_THREAD _eThread)
{
    IResource::SResource tResource;
    tResource.m_sName = _sName;
    tResource.m_eThread = _eThread;
    tResource.m_bIsBatching = _isBatching;
    tResource.m_eModel = IResource::E_STANDART_MODEL_NONE;
    INode* pNode = new CModel();
    pNode->Load(tResource);
    m_lContainer.push_back(pNode);
    return pNode;
}

INode* CSceneMgr::AddAnimatedModel(const std::string &_sName, bool _isBatching, IResource::E_THREAD _eThread)
{
    IResource::SResource tResource;
    tResource.m_sName = _sName;
    tResource.m_eThread = _eThread;
    tResource.m_bIsBatching = _isBatching;
    tResource.m_eModel = IResource::E_STANDART_MODEL_NONE;
    INode* pNode = new CMovieModel();
    pNode->Load(tResource);
    m_lContainer.push_back(pNode);
    return pNode;

}

INode* CSceneMgr::AddStandartModel(IResource::E_STANDART_MODEL _eModel, bool _isBatching, IResource::E_THREAD _eThread)
{
    IResource::SResource tResource;
    tResource.m_sName = STANDART_MODEL;
    tResource.m_eThread = _eThread;
    tResource.m_eModel = _eModel;
    tResource.m_bIsBatching = _isBatching;
    INode* pNode = new CModel();
    pNode->Load(tResource);
    m_lContainer.push_back(pNode);
    return pNode;
}

INode* CSceneMgr::AddLandscapeModel(const std::string &_sName, bool _isBatching)
{
    IResource::SResource tResource;
    tResource.m_sName = _sName;
    tResource.m_eThread = IResource::E_THREAD_MAIN;
    tResource.m_eModel = IResource::E_STANDART_MODEL_NONE;
    tResource.m_bIsBatching = _isBatching;
    INode* pNode = new CLandscape();
    pNode->Load(tResource);
    m_lContainer.push_back(pNode);
    return pNode;
}

void CSceneMgr::AddEventListener(INode *_pNode, CEventMgr::E_EVENT _eEvent)
{
    CEventMgr::Instance()->AddEventListener(_pNode, _eEvent);
}

void CSceneMgr::RemoveEventListener(INode *_pNode, CEventMgr::E_EVENT _eEvent)
{
    CEventMgr::Instance()->RemoveEventListener(_pNode, _eEvent);
}

ICamera* CSceneMgr::CreateFreeCamera(float _fFov, float _fNearPlane, float _fFarPlane)
{
    CCameraFree* pCamera = new CCameraFree();
    pCamera->Init(CWindow::Get_Width(), CWindow::Get_Height(), _fFov, _fFarPlane, _fNearPlane);
    return pCamera;
}

ICamera* CSceneMgr::CreateTargetCamera(float _fFov, float _fNearPlane, float _fFarPlane, INode *_pTarget)
{
    CCameraTarget* pCamera = new CCameraTarget();
    pCamera->Init(CWindow::Get_Width(), CWindow::Get_Height(), _fFov, _fFarPlane, _fNearPlane);
    pCamera->Set_Target(_pTarget);
    return pCamera;
}

void CSceneMgr::RemoveModel(INode *_pNode)
{
    std::vector<INode*>::iterator pBIterator = m_lContainer.begin();
    std::vector<INode*>::iterator pEIterator = m_lContainer.end();
    INode* pNode = NULL;
    
    while (pBIterator != pEIterator)
    {
        pNode = (*pBIterator);
        if(pNode == _pNode)
        {
            m_lContainer.erase(pBIterator);
            break;
        }
        ++pBIterator;
    }
    
    delete pNode;
    _pNode = NULL;
}

#define SMALL_NUM  0.00000001

void CSceneMgr::OnScreenTouch(CVector2d _vTouchPoint)
{

    CVector3d point_01 = CVector3d(1.0f, 0.0f, -1.0f);
    CVector3d point_02 = CVector3d(-1.0f, 0.0f, 1.0f);
    CVector3d point_03 = CVector3d(1.0f, 0.0f, 1.0f);
    
    CVector3d vOrigin = m_pCamera->Get_Position();
    
    CVector3d vStartRay = Unproject(CVector3d(_vTouchPoint.x,_vTouchPoint.y, 0.0f), m_pCamera->Get_View(), m_pCamera->Get_Projection(), CWindow::Get_Viewport().v);
    CVector3d vEndRay = Unproject(CVector3d(_vTouchPoint.x,_vTouchPoint.y, 1.0f), m_pCamera->Get_View(), m_pCamera->Get_Projection(), CWindow::Get_Viewport().v);
    
    CVector3d vRayDirection = vEndRay - vStartRay;
        
    CVector3d vEdge_01 = point_02 - point_01;
    CVector3d vEdge_02 = point_03 - point_01;
    
    CVector3d vNormal = Cross(vEdge_01, vEdge_02);
    vNormal.Normalize();
    
    CVector3d vTemp_01 = vStartRay - point_01;
    float fDistance = -Dot(vNormal, vTemp_01);
    float fDelta = Dot(vNormal, vRayDirection);
    CVector3d vIntersect;
    
    if (fabs(fDelta) < SMALL_NUM)
    {
        return;
    }
    else
    {
        vIntersect = vStartRay + vRayDirection * fDistance / fDelta;
    }
    
    if(m_lContainer.size() <= 1)
    {
        return;
    }
    INode* pNode = m_lContainer[1];
    pNode->Set_Position(vIntersect);
    
}


void CSceneMgr::CheckTouchCollision(const CVector2d &_vPosition)
{	
    
} 

ILight* CSceneMgr::Get_Light(ILight::E_LIGHT_MODE _eMode, unsigned int _iIndex)
{
    if(_eMode == ILight::E_LIGHT_MODE_DIRECTION)
    {
        return m_lLights[_eMode];
    }
    else if(_iIndex < k_MAX_LIGHTS)
    {
        return m_lLights[_eMode + _iIndex];
    }
    return NULL;
}


void CSceneMgr::Update()
{
    if(m_pCamera != NULL)
    {
        m_pCamera->Update();
    }
    
    std::map<unsigned int, ILight*>::iterator pMapBIterator = m_lLights.begin();
    std::map<unsigned int, ILight*>::iterator pMapEIterator = m_lLights.end();
    
    while (pMapBIterator != pMapEIterator)
    {
        (*pMapBIterator).second->Update();
        ++pMapBIterator;
    }
    
    std::vector<INode*>::iterator pBIterator = m_lContainer.begin();
    std::vector<INode*>::iterator pEIterator = m_lContainer.end();
    
    while (pBIterator != pEIterator)
    {
        (*pBIterator)->Update();
        ++pBIterator;
    }
    
    CCollisionMgr::Instance()->Update();
}

void CSceneMgr::Render()
{
    CRenderMgr::Instance()->Begin();
    std::vector<INode*>::iterator pBIterator = m_lContainer.begin();
    std::vector<INode*>::iterator pEIterator = m_lContainer.end();
    
    while (pBIterator != pEIterator)
    {
        (*pBIterator)->Render();
        ++pBIterator;
    }
    
    
    std::map<unsigned int, ILight*>::iterator pMapBIterator = m_lLights.begin();
    std::map<unsigned int, ILight*>::iterator pMapEIterator = m_lLights.end();
    
    while (pMapBIterator != pMapEIterator)
    {
        (*pMapBIterator).second->Render();
        ++pMapBIterator;
    }
    
    CBatchMgr::Instance()->RenderNodesBatch();
    CBatchMgr::Instance()->RenderBoundingBatch();
    
    CRenderMgr::Instance()->End();
}

