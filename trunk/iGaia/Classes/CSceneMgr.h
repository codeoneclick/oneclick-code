//
//  CSceneMgr.h
//  iGaia
//
//  Created by sergey.sergeev on 12/1/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CSceneMgr_h
#define iGaia_CSceneMgr_h

#include "INode.h"
#include "ILight.h"
#include "ICamera.h"
#include "CRenderMgr.h"
#include "CPhysicMgr.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h"
#include "CHeightMapSetter.h"
#include "CNavigationMeshMgr.h"
#include "CParticleMgr.h"
#include "CDecalMgr.h"
#include "CFrustum.h"

class CSceneMgr
{
private:
    static CSceneMgr* m_pInsatnce;
    static const unsigned int k_MAX_LIGHTS; 
    
    std::vector<INode*> m_lContainer;
    std::map<unsigned int, ILight*> m_lLights;
    ILight* m_pGlobalLight;
    INode* m_pSkyBox;
    INode* m_pLandscape;
    INode* m_pWater;
    ICamera* m_pCamera;
    CFrustum* m_pFrustum;
    
    CRenderMgr* m_pRenderMgr;
    CCollisionMgr* m_pCollisionMgr;
    CPhysicMgr* m_pPhysicMgr;
    CParticleMgr* m_pParticleMgr;
    CDecalMgr* m_pDecalMgr;
    
    CNavigationMeshMgr* m_pNavigationMeshMgrRef;
    CHeightMapSetter* m_pHeightMapSetterRef;
    
    void _DrawSimpleStep(void);
    void _DrawReflectionStep(void);
    void _DrawRefractionStep(void);
    void _DrawScreenNormalMapStep(void);
    void _DrawShadowMapStep(void);
public:
    CSceneMgr(void);
    ~CSceneMgr(void);
    
    static CSceneMgr* Instance(void);
    
    ILight* Get_Light(ILight::E_LIGHT_MODE _eMode, unsigned int _iIndex = 0);
    ICamera* Get_Camera(void) { return m_pCamera; }
    void Set_Camera(ICamera* _pCamera);
    CFrustum* Get_Frustum(void) { return m_pFrustum; }
    
    void Set_GlobalLight(ILight* _pLight) { m_pGlobalLight = _pLight; }
    ILight* Get_GlobalLight(void) { return m_pGlobalLight; }
    
    INode* AddCustomModel(const std::string& _sName, IResource::E_THREAD _eThread = IResource::E_THREAD_MAIN);
    INode* AddLandscapeModel(const std::string& _sName, IResource::E_THREAD _eThread = IResource::E_THREAD_MAIN);
    INode* AddLandscapeGrassModel(const std::string& _sName, IResource::E_THREAD _eThread = IResource::E_THREAD_MAIN);
    INode* AddWaterModel(const std::string& _sName, IResource::E_THREAD _eThread = IResource::E_THREAD_MAIN);
    INode* AddSkyBoxModel(const std::string& _sName, IResource::E_THREAD _eThread = IResource::E_THREAD_MAIN);
    
    void AddEventListener(INode* _pNode, CEventMgr::E_EVENT _eEvent);
    void RemoveEventListener(INode* _pNode, CEventMgr::E_EVENT _eEvent);
    
    ICamera* CreateFreeCamera(float _fFov, float _fNearPlane, float _fFarPlane);
    ICamera* CreateTargetCamera(float _fFov, float _fNearPlane, float _fFarPlane, INode* _pTarget);
    
    CRenderMgr* Get_RenderMgr(void) { return m_pRenderMgr; }
    CCollisionMgr* Get_CollisionMgr(void) { return m_pCollisionMgr; }
    CPhysicMgr* Get_PhysicMgr(void) { return m_pPhysicMgr; }
    CParticleMgr* Get_ParticleMgr(void) { return m_pParticleMgr; }
    CDecalMgr* Get_DecalMgr(void) { return m_pDecalMgr; }
    
    CNavigationMeshMgr* Get_NavigationMeshRef(void) { return m_pNavigationMeshMgrRef; }
    void Set_NavigationMeshRef(CNavigationMeshMgr* _pNavigationMeshMgrRef) { m_pNavigationMeshMgrRef = _pNavigationMeshMgrRef; }
    CHeightMapSetter* Get_HeightMapSetterRef(void) { return m_pHeightMapSetterRef; }
    void Set_HeightMapSetterRef(CHeightMapSetter* _pHeightMapSetterRef) { m_pHeightMapSetterRef = _pHeightMapSetterRef; }                                                         
    
    unsigned char Get_UniqueColorId(INode* _pNode);
    
    void RemoveModel(INode *_pNode);
    void Update(void);
    void Render(void);
};

#endif
