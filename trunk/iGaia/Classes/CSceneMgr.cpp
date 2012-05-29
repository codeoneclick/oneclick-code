//
//  CSceneMgr.cpp
//  iGaia
//
//  Created by sergey.sergeev on 12/1/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <mach/mach.h>
#include <mach/mach_time.h>
#include "CSceneMgr.h"
#include "CModel.h"
#include "CLandscape.h"
#include "CGrass.h"
#include "CWater.h"
#include "CSkyBox.h"
#include "CShadowPlane.h"
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
    m_pLandscape = NULL;
    m_pWater = NULL;
    m_pFrustum = NULL;
    
    m_pRenderMgr = new CRenderMgr();
    m_pCollisionMgr = new CCollisionMgr();
    m_pPhysicMgr = new CPhysicMgr();
    m_pParticleMgr = new CParticleMgr();
    m_pDecalMgr = new CDecalMgr();
    
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


INode* CSceneMgr::AddCustomModel(const std::string& _sName, IResource::E_THREAD _eThread)
{
    INode* pNode = new CModel();
    m_lContainer.push_back(pNode);
    pNode->Load(_sName, _eThread);
    return pNode;
}

INode* CSceneMgr::AddLandscapeModel(const std::string& _sName, IResource::E_THREAD _eThread)
{
    INode* pNode = new CLandscape();
    m_lContainer.push_back(pNode);
    pNode->Load(_sName, _eThread);
    m_pLandscape = pNode;
    return pNode;
}

INode* CSceneMgr::AddLandscapeGrassModel(const std::string& _sName, IResource::E_THREAD _eThread)
{
    INode* pNode = new CGrass();
    m_lContainer.push_back(pNode);
    pNode->Load(_sName, _eThread);
    return pNode;
}

INode* CSceneMgr::AddWaterModel(const std::string& _sName, IResource::E_THREAD _eThread)
{
    INode* pNode = new CWater();
    m_lContainer.push_back(pNode);
    pNode->Load(_sName, _eThread);
    m_pWater = pNode;
    return pNode;
}

INode* CSceneMgr::AddSkyBoxModel(const std::string& _sName, IResource::E_THREAD _eThread)
{
    INode* pNode = new CSkyBox();
    pNode->Load(_sName, _eThread);
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

void CSceneMgr::Set_Camera(ICamera* _pCamera)
{
    m_pCamera = _pCamera;
    m_pFrustum = new CFrustum();
    m_pFrustum->Set_InternalParams(m_pCamera->Get_FovY(), m_pCamera->Get_AspectRatio(), m_pCamera->Get_NearPlane(), m_pCamera->Get_FarPlane());
    m_pFrustum->Set_CameraRef(m_pCamera);
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
    
    if(m_pFrustum != NULL)
    {
        m_pFrustum->Update();
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
    
    if(m_pDecalMgr != NULL)
    {
        m_pDecalMgr->Update();
    }
    
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
        m_pSkyBox->Render(CShader::E_RENDER_MODE_SIMPLE);
    }
    
    while (pBeginNodeIterator != pEndNodeIterator)
    {
        (*pBeginNodeIterator)->Render(CShader::E_RENDER_MODE_SIMPLE);
        ++pBeginNodeIterator;
    }
    
    /*std::map<unsigned int, ILight*>::iterator pMapBIterator = m_lLights.begin();
    std::map<unsigned int, ILight*>::iterator pMapEIterator = m_lLights.end();
    
    while (pMapBIterator != pMapEIterator)
    {
        (*pMapBIterator).second->Render();
        ++pMapBIterator;
    }*/
    
    if(m_pDecalMgr != NULL)
    {
        m_pDecalMgr->Render(CShader::E_RENDER_MODE_SIMPLE);
    }
    
    if(m_pParticleMgr != NULL)
    {
        m_pParticleMgr->Render(CShader::E_RENDER_MODE_SIMPLE);
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
    
    if(m_pSkyBox != NULL)
    {
        m_pSkyBox->Update();
        m_pSkyBox->Render(CShader::E_RENDER_MODE_SIMPLE);
    }
    
    while (pBeginNodeIterator != pEndNodeIterator)
    {
        if((*pBeginNodeIterator)->Get_RenderModeReflectionEnable())
        {
            (*pBeginNodeIterator)->Update();
            (*pBeginNodeIterator)->Render(CShader::E_RENDER_MODE_REFLECTION);
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
            (*pBeginNodeIterator)->Render(CShader::E_RENDER_MODE_REFRACTION);
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
            (*pBeginNodeIterator)->Render(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP);
        }
        ++pBeginNodeIterator;
    }
    
    if(m_pParticleMgr != NULL)
    {
        m_pParticleMgr->Render(CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP);
    }
    
    m_pRenderMgr->EndDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_SCREEN_NORMAL_MAP);
}

void CSceneMgr::_DrawShadowMapStep(void)
{
    /*std::vector<INode*>::iterator pBeginNodeIterator = m_lContainer.begin();
    std::vector<INode*>::iterator pEndNodeIterator = m_lContainer.end();
    m_pRenderMgr->BeginDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_SHADOW_MAP);
    
    glm::vec3 vCameraPosition = m_pCamera->Get_Position();
    vCameraPosition = glm::vec3(8.0f, 8.0f, 8.0f); //m_pGlobalLight->Get_Position();
    
    glm::vec3 vCameraLookAt = m_pCamera->Get_LookAt();
    vCameraLookAt = glm::vec3(0.0f, 0.0f, 0.0f);
    m_pCamera->Set_View(glm::lookAt(vCameraPosition, vCameraLookAt, glm::vec3(0.0f,-1.0f,0.0f)));
    
    if(m_pLandscape != NULL && m_pLandscape->Get_RenderModeShadowMapEnable())
    {
        m_pLandscape->Render(INode::E_RENDER_MODE_SHADOW_MAP);
    }
    
    if(m_pWater != NULL && m_pWater->Get_RenderModeShadowMapEnable())
    {
        m_pWater->Render(INode::E_RENDER_MODE_SHADOW_MAP);
    }
    
    if(m_pGrass != NULL && m_pGrass->Get_RenderModeShadowMapEnable())
    {
        m_pGrass->Render(INode::E_RENDER_MODE_SHADOW_MAP);
    }
    
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
    m_pRenderMgr->EndDrawMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE_SHADOW_MAP);*/
}

uint64_t getTickCount(void)
{
    static mach_timebase_info_data_t sTimebaseInfo;
    uint64_t machTime = mach_absolute_time();
    
    if (sTimebaseInfo.denom == 0 )
    {
        (void)mach_timebase_info(&sTimebaseInfo);
    }
    
    uint64_t millis = ((machTime / 1000000) * sTimebaseInfo.numer) / sTimebaseInfo.denom;
    return millis;
}


void CSceneMgr::Render(void)
{
    CWindow::g_iTrianglesPerFrame = 0;
    
    _DrawReflectionStep();
    _DrawRefractionStep();
    _DrawShadowMapStep();
    _DrawSimpleStep();
    _DrawScreenNormalMapStep();
    m_pRenderMgr->DrawResult();
    
    std::cout<<"[CSceneMgr::Render] Triangles Per Frame : "<<CWindow::g_iTrianglesPerFrame<<std::endl;
    
    static int iLastTime = 0;
    int iCurrentTime = getTickCount();
    ++CWindow::g_iFramesPerSecond;
    
    if(iCurrentTime - iLastTime > 1000 )
    {
        iLastTime = iCurrentTime;
        
        std::cout<<"[CSceneMgr::Render] Frames Per Second : "<<CWindow::g_iFramesPerSecond<<std::endl;
        CWindow::g_iFramesPerSecond = 0;
    }

}



