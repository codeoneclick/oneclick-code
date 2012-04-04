//
//  CSceneMgr.cpp
//  iGaia
//
//  Created by sergey.sergeev on 12/1/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CSceneMgr.h"
#include "CModel.h"
#include "CLandscape.h"
#include "CGrass.h"
#include "CWater.h"
#include "CRenderMgr.h"
#include "CCollisionMgr.h"
#include "CCameraFree.h"
#include "CCameraTarget.h"
#include "CWindow.h"
#include "CRenderMgr.h"
#include "CBatchMgr.h"
#include "CLightPoint.h"
#include "CAnimatorMove.h"
#include "CAnimatorMoveHeightMap.h"


CSceneMgr* CSceneMgr::m_pInsatnce = NULL;
const unsigned int CSceneMgr::k_MAX_LIGHTS = 8;

CSceneMgr::CSceneMgr()
{
    m_pCamera = NULL;
    m_pNavigationMeshRef = NULL;
    m_pHeightMapSetterRef = NULL;
    
    m_pRenderMgr = new CRenderMgr();
    m_pBatchMgr = new CBatchMgr();
    m_pCollisionMgr = new CCollisionMgr();
    
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

INode* CSceneMgr::AddModel(IResource::E_STANDART_MODEL _eModel, bool _isBatching)
{
    IResource::SResource tResource;
    tResource.m_sName = STANDART_MODEL;
    tResource.m_eThread = IResource::E_THREAD_MAIN;
    tResource.m_bIsBatching = _isBatching;
    tResource.m_eModel = _eModel;
    INode* pNode = new CModel();
    m_lContainer.push_back(pNode);
    pNode->Load(tResource);
    return pNode;
}

INode* CSceneMgr::AddCustomModel(const std::string &_sName, bool _isBatching, IResource::E_THREAD _eThread)
{
    IResource::SResource tResource;
    tResource.m_sName = _sName;
    tResource.m_eThread = _eThread;
    tResource.m_bIsBatching = _isBatching;
    tResource.m_eModel = IResource::E_STANDART_MODEL_NONE;
    INode* pNode = new CModel();
    m_lContainer.push_back(pNode);
    pNode->Load(tResource);
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
    m_lContainer.push_back(pNode);
    pNode->Load(tResource);
    return pNode;
}

INode* CSceneMgr::AddLandscapeGrassModel(const std::string &_sName, bool _isBatching)
{
    IResource::SResource tResource;
    tResource.m_sName = _sName;
    tResource.m_eThread = IResource::E_THREAD_MAIN;
    tResource.m_eModel = IResource::E_STANDART_MODEL_NONE;
    tResource.m_bIsBatching = _isBatching;
    INode* pNode = new CGrass();
    m_lContainer.push_back(pNode);
    pNode->Load(tResource);
    return pNode;
}

INode* CSceneMgr::AddWaterModel(const std::string &_sName, bool _isBatching)
{
    IResource::SResource tResource;
    tResource.m_sName = _sName;
    tResource.m_eThread = IResource::E_THREAD_MAIN;
    tResource.m_eModel = IResource::E_STANDART_MODEL_NONE;
    tResource.m_bIsBatching = _isBatching;
    INode* pNode = new CWater();
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
    pCamera->Init(CWindow::Get_OffScreenWidth(), CWindow::Get_OffScreenHeight(), _fFov, _fFarPlane, _fNearPlane);
    return pCamera;
}

ICamera* CSceneMgr::CreateTargetCamera(float _fFov, float _fNearPlane, float _fFarPlane, INode *_pTarget)
{
    CCameraTarget* pCamera = new CCameraTarget();
    pCamera->Init(CWindow::Get_OffScreenWidth(), CWindow::Get_OffScreenHeight(), _fFov, _fFarPlane, _fNearPlane);
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
            delete pNode;
            _pNode = NULL;
            break;
        }
        ++pBIterator;
    }
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

unsigned char CSceneMgr::Get_UniqueColorId(INode *_pNode)
{
    std::vector<INode*>::iterator pNodeIteratorBegin = m_lContainer.begin();
    std::vector<INode*>::iterator pNodeIteratorEnd   = m_lContainer.end();
    
    unsigned int iUniqueIndex = 0;
    while (pNodeIteratorBegin != pNodeIteratorEnd)
    {
        iUniqueIndex++;
        if((*pNodeIteratorBegin) == _pNode)
        {
            if(iUniqueIndex <= 255)
            {
                return static_cast<unsigned char>(iUniqueIndex);
            }
            else
            {
                std::cout<<"[CSceneMgr::Get_UniqueColorId] Unique index out of range \n";
                return 0;
            }
        }
        ++pNodeIteratorBegin;
    }
    
    std::cout<<"[CSceneMgr::Get_UniqueColorId] Unique index is not found \n";
    return 0;
}

IAnimator* CSceneMgr::AddMoveAnimator(INode *_pNode, IAnimatorDelegate *_pAnimatorDelegateOwner, const glm::vec3 &_vStartPosition, const glm::vec3 &_vEndPosition, float _fStep)
{
    //IAnimator* pAnimator = new CAnimatorMove();
    //((CAnimatorMove*)pAnimator)->Init(_pNode, _pAnimatorDelegateOwner, _vStartPosition, _vEndPosition, _fStep);
    //m_lAnimators.push_back(pAnimator);
    return NULL;
}

IAnimator* CSceneMgr::AddHeightMapMoveAnimator(INode *_pNode, IAnimatorDelegate *_pAnimatorDelegateOwner, glm::vec2 _vStartPosition, glm::vec2 _vEndPosition, float _fStep)
{
    IAnimator* pAnimator = new CAnimatorMoveHeightMap();
    ((CAnimatorMoveHeightMap*)pAnimator)->Init(_pNode, _pAnimatorDelegateOwner, _vStartPosition,_vEndPosition,_fStep);
    m_lAnimators.push_back(pAnimator);
    return pAnimator;
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
    
    std::vector<IAnimator*>::iterator pBeginAnimatorIterator = m_lAnimators.begin();
    std::vector<IAnimator*>::iterator pEndAnimatorIterator = m_lAnimators.end();
    
    while (pBeginAnimatorIterator != pEndAnimatorIterator)
    {
        (*pBeginAnimatorIterator)->Update();
        ++pBeginAnimatorIterator;
    }
    
    pBeginAnimatorIterator = m_lAnimators.begin();
    pEndAnimatorIterator = m_lAnimators.end();
    
    while (pBeginAnimatorIterator != pEndAnimatorIterator)
    {
        if((*pBeginAnimatorIterator)->Get_IsDone())
        {
            (*pBeginAnimatorIterator)->Remove();
            IAnimator* pAnimator = (*pBeginAnimatorIterator);
            m_lAnimators.erase(pBeginAnimatorIterator);
            delete pAnimator;
            break;
        }
        else
        {
            ++pBeginAnimatorIterator;
        }
    }

    m_pCollisionMgr->Update();
}

void CSceneMgr::_DrawSimpleStep(void)
{
    std::vector<INode*>::iterator pBeginNodeIterator = m_lContainer.begin();
    std::vector<INode*>::iterator pEndNodeIterator = m_lContainer.end();
    m_pRenderMgr->BeginDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_SIMPLE);
    
    while (pBeginNodeIterator != pEndNodeIterator)
    {
        (*pBeginNodeIterator)->Render(INode::E_RENDER_MODE_SIMPLE);
        ++pBeginNodeIterator;
    }
    
    std::map<unsigned int, ILight*>::iterator pMapBIterator = m_lLights.begin();
    std::map<unsigned int, ILight*>::iterator pMapEIterator = m_lLights.end();
    
    while (pMapBIterator != pMapEIterator)
    {
        (*pMapBIterator).second->Render();
        ++pMapBIterator;
    }
    
    m_pRenderMgr->EndDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_SIMPLE);
}

void CSceneMgr::_DrawReflectionStep(void)
{
    std::vector<INode*>::iterator pBeginNodeIterator = m_lContainer.begin();
    std::vector<INode*>::iterator pEndNodeIterator = m_lContainer.end();
    float fWaterLevel = -0.1f;
    m_pRenderMgr->BeginDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_REFLECTION);
    
    glm::vec3 vCameraPosition = m_pCamera->Get_Position();
    vCameraPosition.y = -vCameraPosition.y + fWaterLevel * 2.0;
    
    glm::vec3 vCameraLookAt = m_pCamera->Get_LookAt();
    vCameraLookAt.y = -vCameraLookAt.y + fWaterLevel * 2.0f;
    m_pCamera->Set_View(glm::lookAt(vCameraPosition, vCameraLookAt, glm::vec3(0.0f,-1.0f,0.0f)));    
    
    while (pBeginNodeIterator != pEndNodeIterator)
    {
        if((*pBeginNodeIterator)->Get_ForReflection())
        {
            (*pBeginNodeIterator)->Update();
            (*pBeginNodeIterator)->Render(INode::E_RENDER_MODE_REFLECTION);
        }
        ++pBeginNodeIterator;
    }
    m_pCamera->Set_View(glm::lookAt(m_pCamera->Get_Position(), m_pCamera->Get_LookAt(), glm::vec3(0.0f,1.0f,0.0f))); 
    m_pRenderMgr->EndDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_REFLECTION);
}

void CSceneMgr::_DrawRefractionStep(void)
{
    std::vector<INode*>::iterator pBeginNodeIterator = m_lContainer.begin();
    std::vector<INode*>::iterator pEndNodeIterator = m_lContainer.end();
    m_pRenderMgr->BeginDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_REFRACTION);
    
    while (pBeginNodeIterator != pEndNodeIterator)
    {
        if((*pBeginNodeIterator)->Get_ForRefraction())
        {
            (*pBeginNodeIterator)->Update();
            (*pBeginNodeIterator)->Render(INode::E_RENDER_MODE_REFRACTION);
        }
        ++pBeginNodeIterator;
    }
    m_pRenderMgr->EndDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_REFRACTION);
}

void CSceneMgr::_DrawNormalDepthStep(void)
{
    std::vector<INode*>::iterator pBeginNodeIterator = m_lContainer.begin();
    std::vector<INode*>::iterator pEndNodeIterator = m_lContainer.end();
    pBeginNodeIterator = m_lContainer.begin();
    pEndNodeIterator = m_lContainer.end();
    m_pRenderMgr->BeginDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_NORMAL_DEPTH);
    while (pBeginNodeIterator != pEndNodeIterator)
    {
        if((*pBeginNodeIterator)->Get_NormalDepth())
        {
            (*pBeginNodeIterator)->Update();
            (*pBeginNodeIterator)->Render(INode::E_RENDER_MODE_NORMAL_DEPTH);
        }
        ++pBeginNodeIterator;
    }
    m_pRenderMgr->EndDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_NORMAL_DEPTH);
}

void CSceneMgr::Render(void)
{   _DrawReflectionStep();
    _DrawRefractionStep();
    _DrawSimpleStep();
    _DrawNormalDepthStep();
    m_pRenderMgr->DrawResult();
}













