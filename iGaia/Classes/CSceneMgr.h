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
#include "CBatchMgr.h"
#include "CRenderMgr.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h"
#include "CHeightMapSetter.h"
#include "IAnimator.h"
#include "CNavigationMesh.h"

class CSceneMgr
{
private:
    static CSceneMgr* m_pInsatnce;
    static const unsigned int k_MAX_LIGHTS; 
    
    std::vector<INode*> m_lContainer;
    std::map<unsigned int, ILight*> m_lLights;
    ICamera* m_pCamera;
    
    std::vector<IAnimator*> m_lAnimators;
    
    CRenderMgr* m_pRenderMgr;
    CBatchMgr* m_pBatchMgr;
    CCollisionMgr* m_pCollisionMgr;
    
    CNavigationMesh* m_pNavigationMeshRef;
    CHeightMapSetter* m_pHeightMapSetterRef;
    
    void _DrawSimpleStep(void);
    void _DrawReflectionStep(void);
    void _DrawRefractionStep(void);
    void _DrawNormalDepthStep(void);
public:
    CSceneMgr(void);
    ~CSceneMgr(void);
    
    static CSceneMgr* Instance(void);
    
    ILight* Get_Light(ILight::E_LIGHT_MODE _eMode, unsigned int _iIndex = 0);
    ICamera* Get_Camera(void) { return m_pCamera; }
    void Set_Camera(ICamera* _pCamera) { m_pCamera = _pCamera; }
    
    INode* AddModel(IResource::E_STANDART_MODEL _eModel, bool _isBatching);
    INode* AddCustomModel(const std::string& _sName, bool _isBatching = false, IResource::E_THREAD _eThread = IResource::E_THREAD_MAIN);
    INode* AddLandscapeModel(const std::string& _sName, bool _isBatching = false);
    INode* AddLandscapeGrassModel(const std::string& _sName, bool _isBatching = false);
    INode* AddWaterModel(const std::string& _sName, bool _isBatching = false);
    
    void AddEventListener(INode* _pNode, CEventMgr::E_EVENT _eEvent);
    void RemoveEventListener(INode* _pNode, CEventMgr::E_EVENT _eEvent);
    
    ICamera* CreateFreeCamera(float _fFov, float _fNearPlane, float _fFarPlane);
    ICamera* CreateTargetCamera(float _fFov, float _fNearPlane, float _fFarPlane, INode* _pTarget);
    
    CRenderMgr* Get_RenderMgr(void) { return m_pRenderMgr; }
    CBatchMgr* Get_BatchMgr(void) { return m_pBatchMgr; }
    CCollisionMgr* Get_CollisionMgr(void) { return m_pCollisionMgr; }
    
    CNavigationMesh* Get_NavigationMeshRef(void) { return m_pNavigationMeshRef; }
    void Set_NavigationMeshRef(CNavigationMesh* _pNavigationMeshRef) { m_pNavigationMeshRef = _pNavigationMeshRef; }
    CHeightMapSetter* Get_HeightMapSetterRef(void) { return m_pHeightMapSetterRef; }
    void Set_HeightMapSetterRef(CHeightMapSetter* _pHeightMapSetterRef) { m_pHeightMapSetterRef = _pHeightMapSetterRef; }                                                         
    
    IAnimator* AddMoveAnimator(INode* _pNode, IAnimatorDelegate* _pAnimatorDelegateOwner, const glm::vec3& _vStartPosition, const glm::vec3&  _vEndPosition, float _fStep);
    IAnimator* AddHeightMapMoveAnimator(INode *_pNode, IAnimatorDelegate *_pAnimatorDelegateOwner, glm::vec2 _vStartPosition, glm::vec2 _vEndPosition, float _fStep);
    
    unsigned char Get_UniqueColorId(INode* _pNode);
    
    void RemoveModel(INode *_pNode);
    void Update(void);
    void Render(void);
};

#endif
