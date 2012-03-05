//
//  INode.h
//  gEngine
//
//  Created by sergey.sergeev on 11/28/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_INode_h
#define gEngine_INode_h

#include "CQuaternion.h"
#include "CTexture.h"

#include "CShader.h"
#include "CVertexBuffer.h"
#include "CMesh.h"

#include "CResourceMgr.h"
#include "CShaderComposite.h"
#include "CMeshComposite.h"

#include "CBoundingBox.h"
#include "ICollider.h"
#include "ILight.h"

#include "IDelegate.h"

#define TEXTURES_MAX_COUNT 4

class INode
{
protected:
    CMatrix4x4 m_mScale;
    CMatrix4x4 m_mRotation;
    CMatrix4x4 m_mTranslation;
    CMatrix4x4 m_mWorld;
    
    CShader* m_pShader;
    CTexture** m_pTextures;
    CMesh* m_pMesh;
    
    CVector3d m_vScale;
    CVector3d m_vPosition;
    CVector3d m_vRotation;
    
    CBoundingBox* m_pBoundingBox;
    ICollider* m_pCollider;
    ILight* m_pLight;
    
    bool m_bIsBatching;
    
    std::vector<IDelegate*> m_lDelegates;
    IDelegate* m_pDelegateTarget;
    
public:
    INode(void);
    virtual ~INode();
    virtual void Load(IResource::SResource _tResource) = 0;
    virtual void Update(void);
    virtual void Render(void) = 0;
    
    CShader* Get_Shader(void) const { return m_pShader; }
    CTexture** Get_Textures(void) const { return m_pTextures; }
    CMesh* Get_Mesh(void) const { return m_pMesh; }
    
    void Set_Texture(CTexture* _pTexture, int index = 0);
    void Set_Texture(const std::string &_sName, int index = 0, IResource::E_THREAD _eThread = IResource::E_THREAD_MAIN);
    
    void Set_Shader(IResource::E_SHADER _eShader);
    
    void Set_Position(CVector3d _vPosition) { m_vPosition = _vPosition; }
    CVector3d Get_Position(void) { return m_vPosition; }
    
    void Set_Rotation(CVector3d _vRotation) { m_vRotation = _vRotation; }
    CVector3d Get_Rotation(void) { return m_vRotation; }
    
    void Set_Scale(CVector3d _vScale) { m_vScale = _vScale; }
    CVector3d Get_Scale(void) { return m_vScale; }
    
    CMatrix4x4 Get_WorldMatrix(void) { return m_mWorld; }
    
    void Add_Delegate(IDelegate* _pDelegate);
    void Remove_Delegate(IDelegate* _pDelegate);
    
    void Set_DelegateTarget(IDelegate* _pDelegateTarget) { m_pDelegateTarget = _pDelegateTarget; }
    IDelegate* Get_DelegateTarget(void) { return m_pDelegateTarget; }
    
    void Create_BoundingBox(void);
    void Create_ColliderBox(void);
    void Create_ColliderQuad(void);
    
    void Remove_BoundingBox(void);
    void Remove_Collider(void);
    
    void Set_Light(ILight* _pLight)  { m_pLight = _pLight; }
    
    virtual void OnTouchEvent(void) = 0; 
};

#endif










