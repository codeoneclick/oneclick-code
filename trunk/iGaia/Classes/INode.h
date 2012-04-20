//
//  INode.h
//  iGaia
//
//  Created by sergey.sergeev on 11/28/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_INode_h
#define iGaia_INode_h

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 

#include "CTexture.h"
#include "CShader.h"
#include "CVertexBuffer.h"
#include "CMesh.h"

#include "CResourceMgr.h"
#include "CShaderComposite.h"
#include "CMeshComposite.h"

#include "CBoundingBox.h"
#include "ILight.h"

#include "IDelegate.h"
#include "IResourceLoaderDelegate.h"

#include "btRaycastVehicle.h"

#define TEXTURES_MAX_COUNT 8

class INode : public IResourceLoaderDelegate
{
public:
    enum E_RENDER_MODE { E_RENDER_MODE_SIMPLE = 0, E_RENDER_MODE_REFLECTION, E_RENDER_MODE_REFRACTION, E_RENDER_MODE_EDGE_DETECT, E_RENDER_MODE_NORMAL_DEPTH };
protected:
    glm::mat4x4 m_mScale;
    glm::mat4x4 m_mRotation;
    glm::mat4x4 m_mTranslation;
    glm::mat4x4 m_mWorld;
    
    glm::vec3 m_vPosition;
    glm::vec3 m_vRotation;
    glm::vec3 m_vScale;
    glm::vec2 m_vTexCoordOffset;
    
    CShader* m_pShader;
    CTexture** m_pTextures;
    CMesh* m_pMesh;
    
    CBoundingBox* m_pBoundingBox;
    ILight* m_pLight;
    
    bool m_bIsForReflection;
    bool m_bIsForRefraction;
    bool m_bIsEdgeDetect;
    bool m_bIsNormalDepth;
    
    std::vector<IDelegate*> m_lDelegates;
    IDelegate* m_pDelegateTarget;
    
    btRigidBody* m_pRigidBody;
    btRaycastVehicle*	m_pRaycastVehicle;
    btRaycastVehicle::btVehicleTuning m_pTuning;
    
public:
    INode(void);
    virtual ~INode(void);
    virtual void Load(IResource::SResource _tResource) = 0;
    virtual void Update(void);
    virtual void Render(E_RENDER_MODE _eMode) = 0;
    
    CShader* Get_Shader(void) const { return m_pShader; }
    CTexture** Get_Textures(void) const { return m_pTextures; }
    CMesh* Get_Mesh(void) const { return m_pMesh; }
    
    void Set_RigidBody(btRigidBody* _pRigidBody) { m_pRigidBody = _pRigidBody; }
    btRigidBody* Get_RigidBody(void) { return m_pRigidBody; }
    
    void Set_RaycastVehicle(btRaycastVehicle* _pRaycastVehicle) { m_pRaycastVehicle = _pRaycastVehicle; }
    btRaycastVehicle* Get_RaycastVehicle(void) { return m_pRaycastVehicle; }
    
    void Set_RigidBodyTuning(const btRaycastVehicle::btVehicleTuning& _pTuning) { m_pTuning = _pTuning; }
    btRaycastVehicle::btVehicleTuning Get_RigidBodyTuning(void) { return m_pTuning; }
    
    void Set_RigidOrigin(glm::vec3 _vOrigin)
    {
        if(m_pRigidBody != NULL)
        {
            btTransform mTransform;
            m_pRigidBody->getMotionState()->getWorldTransform(mTransform);
            mTransform.setOrigin(btVector3(_vOrigin.x,_vOrigin.y,_vOrigin.z));
            m_pRigidBody->getMotionState()->setWorldTransform(mTransform);
            m_pRigidBody->setCenterOfMassTransform(mTransform);
        }
    }
    
    void Set_Texture(CTexture* _pTexture, int index = 0);
    void Set_Texture(const std::string &_sName, int index = 0, IResource::E_THREAD _eThread = IResource::E_THREAD_MAIN);
    void Set_Shader(IResource::E_SHADER _eShader);
    
    void Set_Position(const glm::vec3& _vPosition) { m_vPosition = _vPosition; }
    glm::vec3 Get_Position(void) { return m_vPosition; }
    
    void Set_Rotation(const glm::vec3& _vRotation) { m_vRotation = _vRotation; }
    glm::vec3 Get_Rotation(void) { return m_vRotation; }
    
    void Set_Scale(const glm::vec3& _vScale) { m_vScale = _vScale; }
    glm::vec3 Get_Scale(void) { return m_vScale; }
    
    glm::mat4x4 Get_WorldMatrix(void) { return m_mWorld; }
    
    void Set_TexCoordOffset(glm::vec2 _vOffset) { m_vTexCoordOffset = _vOffset; }
    
    void Add_Delegate(IDelegate* _pDelegate);
    void Remove_Delegate(IDelegate* _pDelegate);
    
    void Set_DelegateTarget(IDelegate* _pDelegateTarget) { m_pDelegateTarget = _pDelegateTarget; }
    IDelegate* Get_DelegateTarget(void) { return m_pDelegateTarget; }
    
    void Create_BoundingBox(void);
    
    void Remove_BoundingBox(void);
    
    void Set_Light(ILight* _pLight)  { m_pLight = _pLight; }
    
    void Set_ForRefraction(bool _value) { m_bIsForRefraction = _value; }
    void Set_ForReflection(bool _value) { m_bIsForReflection = _value; }
    bool Get_ForReflection(void) { return m_bIsForReflection; }
    bool Get_ForRefraction(void) { return m_bIsForRefraction; }
    void Set_EdgeDetect(bool _value) { m_bIsEdgeDetect = _value; }
    bool Get_EdgeDetect(void) { return m_bIsEdgeDetect; }
    void Set_NormalDepth(bool _value) { m_bIsNormalDepth = _value; }
    bool Get_NormalDepth(void) { return m_bIsNormalDepth; }
    
    virtual void OnTouchEvent(void) = 0;
    virtual void OnPhysicEventUpdate(glm::vec3 _vPosition, glm::vec3 _vRotation, glm::vec3 _vScale) = 0;
};

#endif










