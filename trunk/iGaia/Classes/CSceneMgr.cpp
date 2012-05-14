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
#include "CSkyBox.h"
#include "CRenderMgr.h"
#include "CCollisionMgr.h"
#include "CCameraFree.h"
#include "CCameraTarget.h"
#include "CWindow.h"
#include "CRenderMgr.h"
#include "CLightPoint.h"


CSceneMgr* CSceneMgr::m_pInsatnce = NULL;
const unsigned int CSceneMgr::k_MAX_LIGHTS = 8;

CSceneMgr::CSceneMgr(void)
{
    m_pCamera = NULL;
    m_pNavigationMeshMgrRef = NULL;
    m_pHeightMapSetterRef = NULL;
    m_pSkyBox = NULL;
    
    m_pRenderMgr = new CRenderMgr();
    m_pCollisionMgr = new CCollisionMgr();
    m_pPhysicMgr = new CPhysicMgr();
    m_pParticleMgr = new CParticleMgr();
    
    m_lLights[ILight::E_LIGHT_MODE_DIRECTION] = new CLightPoint();
    static_cast<CLightPoint*>(m_lLights[ILight::E_LIGHT_MODE_DIRECTION])->Set_Visible(false);
    
    for(unsigned int i = 0; i < k_MAX_LIGHTS; i++)
    {
        m_lLights[ILight::E_LIGHT_MODE_POINT + i] = new CLightPoint();
        static_cast<CLightPoint*>(m_lLights[ILight::E_LIGHT_MODE_POINT + i])->Set_Visible(false);
    }
}

CSceneMgr::~CSceneMgr(void)
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

INode* CSceneMgr::AddSkyBoxModel(const std::string &_sName, bool _isBatching)
{
    IResource::SResource tResource;
    tResource.m_sName = _sName;
    tResource.m_eThread = IResource::E_THREAD_MAIN;
    tResource.m_eModel = IResource::E_STANDART_MODEL_NONE;
    tResource.m_bIsBatching = _isBatching;
    INode* pNode = new CSkyBox();
    pNode->Load(tResource);
    m_pSkyBox = pNode;
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

    m_pCollisionMgr->Update();
    m_pPhysicMgr->Update();
    
    if(m_pParticleMgr != NULL)
    {
        m_pParticleMgr->Update();
    }
    
    if(m_pSkyBox != NULL)
    {
        m_pSkyBox->Set_Position(m_pCamera->Get_Position());
        m_pSkyBox->Update();
    }
}

void CSceneMgr::_DrawSimpleStep(void)
{
    std::vector<INode*>::iterator pBeginNodeIterator = m_lContainer.begin();
    std::vector<INode*>::iterator pEndNodeIterator = m_lContainer.end();
    m_pRenderMgr->BeginDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_SIMPLE);
    
    if(m_pSkyBox != NULL)
    {
        m_pSkyBox->Render(INode::E_RENDER_MODE_SIMPLE);
    }
    
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
    
    if(m_pParticleMgr != NULL)
    {
        m_pParticleMgr->Render(INode::E_RENDER_MODE_SIMPLE);
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
        if((*pBeginNodeIterator)->Get_RenderModeReflectionEnable())
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
        if((*pBeginNodeIterator)->Get_RenderModeRefractionEnable())
        {
            (*pBeginNodeIterator)->Update();
            (*pBeginNodeIterator)->Render(INode::E_RENDER_MODE_REFRACTION);
        }
        ++pBeginNodeIterator;
    }
    m_pRenderMgr->EndDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_REFRACTION);
}

void CSceneMgr::_DrawScreenNormalMapStep(void)
{
    std::vector<INode*>::iterator pBeginNodeIterator = m_lContainer.begin();
    std::vector<INode*>::iterator pEndNodeIterator = m_lContainer.end();
    pBeginNodeIterator = m_lContainer.begin();
    pEndNodeIterator = m_lContainer.end();
    m_pRenderMgr->BeginDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_SCREEN_NORMAL_MAP);
    while (pBeginNodeIterator != pEndNodeIterator)
    {
        if((*pBeginNodeIterator)->Get_RenderModeScreenNormalEnable())
        {
            (*pBeginNodeIterator)->Render(INode::E_RENDER_MODE_SCREEN_NORMAL_MAP);
        }
        ++pBeginNodeIterator;
    }
    
    if(m_pParticleMgr != NULL)
    {
        //m_pParticleMgr->Render(INode::E_RENDER_MODE_SCREEN_NORMAL_MAP);
    }
    
    m_pRenderMgr->EndDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_SCREEN_NORMAL_MAP);
}

void CSceneMgr::_DrawShadowMapStep(void)
{
    std::vector<INode*>::iterator pBeginNodeIterator = m_lContainer.begin();
    std::vector<INode*>::iterator pEndNodeIterator = m_lContainer.end();
    m_pRenderMgr->BeginDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_SHADOW_MAP);
    
    glm::vec3 vCameraPosition = m_pCamera->Get_Position();
    vCameraPosition = glm::vec3(8.0f, 8.0f, 8.0f);//m_pGlobalLight->Get_Position();
    
    glm::vec3 vCameraLookAt = m_pCamera->Get_LookAt();
    vCameraLookAt = glm::vec3(0.0f, 0.0f, 0.0f);
    m_pCamera->Set_View(glm::lookAt(vCameraPosition, vCameraLookAt, glm::vec3(0.0f,-1.0f,0.0f)));
    
    while (pBeginNodeIterator != pEndNodeIterator)
    {
        if((*pBeginNodeIterator)->Get_RenderModeShadowMapEnable())
        {
            (*pBeginNodeIterator)->Update();
            (*pBeginNodeIterator)->Render(INode::E_RENDER_MODE_SHADOW_MAP);
        }
        ++pBeginNodeIterator;
    }
    m_pCamera->Set_View(glm::lookAt(m_pCamera->Get_Position(), m_pCamera->Get_LookAt(), glm::vec3(0.0f,1.0f,0.0f))); 
    m_pRenderMgr->EndDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_SHADOW_MAP);
}

void CSceneMgr::Render(void)
{   _DrawReflectionStep();
    _DrawRefractionStep();
    _DrawShadowMapStep();
    _DrawSimpleStep();
    _DrawScreenNormalMapStep();
    m_pRenderMgr->DrawResult();
}



