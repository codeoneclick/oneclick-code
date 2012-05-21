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

#include "IResourceLoaderDelegate.h"
#include "ITouchDelegate.h"

#define TEXTURES_MAX_COUNT 8

class INode : public ITouchDelegate, public IResourceLoaderDelegate
{
public:
    enum E_RENDER_MODE { E_RENDER_MODE_SIMPLE = 0, E_RENDER_MODE_REFLECTION, E_RENDER_MODE_REFRACTION, E_RENDER_MODE_SCREEN_NORMAL_MAP, E_RENDER_MODE_MAX };
protected:
    glm::mat4x4 m_mScale;
    glm::mat4x4 m_mRotation;
    glm::mat4x4 m_mTranslation;
    glm::mat4x4 m_mWorld;
    
    glm::vec3 m_vPosition;
    glm::vec3 m_vRotation;
    glm::vec3 m_vScale;
    glm::vec2 m_vTexCoordOffset;
    
    CShader** m_pShaders;
    CTexture** m_pTextures;
    CMesh* m_pMesh;
    
    CBoundingBox* m_pBoundingBox;
    
    bool m_bIsRenderModeReflectionEnable;
    bool m_bIsRenderModeRefractionEnable;
    bool m_bIsRenderModeScreenNormalEnable;
    bool m_bIsRenderModeShadowMapEnable;
    
    std::vector<IDelegate*> m_lDelegateOwners;
public:
    INode(void);
    virtual ~INode(void);
    virtual void Load(const std::string& _sName, IResource::E_THREAD _eThread) = 0;
    virtual void Update(void);
    virtual void Render(E_RENDER_MODE _eMode) = 0;
    
    CShader*  Get_Shader(E_RENDER_MODE _eRenderMode);
    CTexture* Get_Texture(unsigned int index);
    CMesh*    Get_Mesh(void) { return m_pMesh; }
    
    void Set_Texture(CTexture* _pTexture, int index, CTexture::E_WRAP_MODE _eWrap);
    void Set_Texture(const std::string &_sName, int _index, CTexture::E_WRAP_MODE _eWrap, IResource::E_THREAD _eThread = IResource::E_THREAD_MAIN);
    void Set_Shader(E_RENDER_MODE _eRenderMode, IResource::E_SHADER _eShader);
    
    void Set_Position(const glm::vec3& _vPosition) { m_vPosition = _vPosition; }
    glm::vec3 Get_Position(void) { return m_vPosition; }
    
    void Set_Rotation(const glm::vec3& _vRotation) { m_vRotation = _vRotation; }
    glm::vec3 Get_Rotation(void) { return m_vRotation; }
    
    void Set_Scale(const glm::vec3& _vScale) { m_vScale = _vScale; }
    glm::vec3 Get_Scale(void) { return m_vScale; }
    
    glm::mat4x4 Get_WorldMatrix(void) { return m_mWorld; }
    
    void Set_TexCoordOffset(glm::vec2 _vOffset) { m_vTexCoordOffset = _vOffset; }
    glm::vec2 Get_TexCoordOffset(void) { return m_vTexCoordOffset; }
    
    void Add_DelegateOwner(IDelegate* _pDelegateOwner);
    void Remove_DelegateOwner(IDelegate* _pDelegateOwner);
    
    virtual void Create_BoundingBox(void);
    void Remove_BoundingBox(void);
    
    void Set_RenderModeReflectionEnable(bool _value) { m_bIsRenderModeReflectionEnable = _value; }
    bool Get_RenderModeReflectionEnable(void) { return m_bIsRenderModeReflectionEnable; }
    void Set_RenderModeRefractionEnable(bool _value) { m_bIsRenderModeRefractionEnable = _value; }
    bool Get_RenderModeRefractionEnable(void) { return m_bIsRenderModeRefractionEnable; }
    void Set_RenderModeScreenNormalEnable(bool _value) { m_bIsRenderModeScreenNormalEnable = _value; }
    bool Get_RenderModeScreenNormalEnable(void) { return m_bIsRenderModeScreenNormalEnable; }
    void Set_RenderModeShadowMapEnable(bool _value) { m_bIsRenderModeShadowMapEnable = _value; }
    bool Get_RenderModeShadowMapEnable(void) { return m_bIsRenderModeShadowMapEnable; }
    
    virtual void OnTouchEvent(ITouchDelegate* _pDelegateOwner) = 0;
    virtual void OnResourceLoadDoneEvent(IResource::E_RESOURCE_TYPE _eType, IResource* _pResource) = 0;
};

#endif










