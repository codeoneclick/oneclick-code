
//  CModel.cpp
//  iGaia
//
//  Created by sergey.sergeev on 11/17/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CModel.h"
#include "CSceneMgr.h"
#include "CRenderMgr.h"

CModel::CModel(void)
{
    
}

CModel::~CModel(void)
{
    
}

void CModel::Load(const std::string& _sName, IResource::E_THREAD _eThread)
{
    m_pMesh = static_cast<CMesh*>(CResourceMgr::Instance()->Load(_sName, IResource::E_MGR_MESH, _eThread, this));
    
    m_pMesh->Get_VertexBufferRef()->CommitToRAM();
    m_pMesh->Get_VertexBufferRef()->CommitFromRAMToVRAM();
    m_pMesh->Get_IndexBufferRef()->CommitFromRAMToVRAM();
}

void CModel::OnResourceLoadDoneEvent(IResource::E_RESOURCE_TYPE _eType, IResource *_pResource)
{
    switch (_eType)
    {
        case IResource::E_RESOURCE_TYPE_MESH:
            std::cout<<"[CModel::OnLoadDone] Resource Mesh loaded : "<<_pResource->Get_Name()<<"\n";
            m_pMesh = static_cast<CMesh*>(_pResource);
            if(m_pBoundingBox != NULL)
            {
                m_pBoundingBox->Set_MaxMinPoints(m_pMesh->Get_MaxBound(), m_pMesh->Get_MinBound());
            }
            m_pMesh->Get_VertexBufferRef()->CommitToRAM();
            m_pMesh->Get_VertexBufferRef()->CommitFromRAMToVRAM();
            m_pMesh->Get_IndexBufferRef()->CommitFromRAMToVRAM();
            break;
        case IResource::E_RESOURCE_TYPE_TEXTURE:
            std::cout<<"[CModel::OnLoadDone] Resource Texture loaded : "<<_pResource->Get_Name()<<"\n";
            break;
        default:
            break;
    }
}

void CModel::OnTouchEvent(ITouchDelegate* _pDelegateOwner)
{
    CCollisionMgr::SRay3d tTouchRay = CSceneMgr::Instance()->Get_CollisionMgr()->Get_TouchRay();
    glm::vec3 vCollisionPoint;
    
    if(!CSceneMgr::Instance()->Get_CollisionMgr()->Get_CollisionPoint(m_pBoundingBox->Get_Mesh()->Get_VertexBufferRef(), m_pBoundingBox->Get_Mesh()->Get_IndexBufferRef(), tTouchRay, &vCollisionPoint))
    {
        return;
    }
    else
    {
        std::cout<<"[CModel::OnTouchEven] Colission Point = "<<vCollisionPoint.x<<","<<vCollisionPoint.y<<","<<vCollisionPoint.z<<"\n";
    }
    
    for(size_t index = 0; index < m_lDelegateOwners.size(); index++)
    {
        if(m_lDelegateOwners[index]->Get_DelegateType() == IDelegate::E_DELEGATE_TYPE_TOUCH)
        {
            dynamic_cast<ITouchDelegate*>(m_lDelegateOwners[index])->OnTouchEvent(this);
        }
    }
}

void CModel::Update()
{
    INode::Update();
}

void CModel::Render(E_RENDER_MODE _eMode)
{
    
    if(CSceneMgr::Instance()->Get_Frustum()->IsPointInFrustum(m_vPosition) == CFrustum::E_FRUSTUM_RESULT_OUTSIDE)
    {
        return;
    }
    
    INode::Render(_eMode);
    
    glCullFace(GL_BACK);
    ICamera* pCamera = CSceneMgr::Instance()->Get_Camera();
    ILight* pLight = CSceneMgr::Instance()->Get_GlobalLight();
    
    switch (_eMode)
    {
        case INode::E_RENDER_MODE_SIMPLE:
        {
            if(m_pShaders[_eMode] == NULL)
            {
                std::cout<<"[CModel::Render] Shader MODE_SIMPLE is NULL"<<std::endl;
                return;
            }

            m_pMesh->Get_VertexBufferRef()->Set_ShaderRef(m_pShaders[_eMode]->Get_ProgramHandle());
            m_pShaders[_eMode]->Enable();
            m_pShaders[_eMode]->SetMatrix(m_mWorld, CShader::k_MATRIX_WORLD);
            m_pShaders[_eMode]->SetMatrix(pCamera->Get_Projection(), CShader::k_MATRIX_PROJECTION);
            m_pShaders[_eMode]->SetMatrix(pCamera->Get_View(), CShader::k_MATRIX_VIEW);
            m_pShaders[_eMode]->SetVector3(pCamera->Get_Position(), CShader::k_VECTOR_VIEW);
            m_pShaders[_eMode]->SetVector2(m_vTexCoordOffset, CShader::k_TEXCOORD_OFFSET);
            m_pShaders[_eMode]->SetVector3(pLight->Get_Position(), CShader::k_VECTOR_LIGHT);
            
            char pStrTextureId[256];
            for(unsigned int i = 0; i < TEXTURES_MAX_COUNT; ++i)
            {
                if( m_pTextures[i] == NULL )
                {
                    continue;
                }
                sprintf(pStrTextureId, "EXT_TEXTURE_0%i",i + 1);
                std::string k_TEXTURE_ID = pStrTextureId;
                m_pShaders[_eMode]->SetTexture(m_pTextures[i]->Get_Handle(), k_TEXTURE_ID);
            }
        }
            break;
        case INode::E_RENDER_MODE_REFLECTION:
        {
            
        }
            break;
        case INode::E_RENDER_MODE_REFRACTION:
        {
            
        }
            break;
        case INode::E_RENDER_MODE_SCREEN_NORMAL_MAP:
        {
            if(m_pShaders[_eMode] == NULL)
            {
                std::cout<<"[CModel::Render] Shader MODE_SCREEN_NORMAL_MAP is NULL"<<std::endl;
                return;
            }
            
            m_pMesh->Get_VertexBufferRef()->Set_ShaderRef(m_pShaders[_eMode]->Get_ProgramHandle());
            m_pShaders[_eMode]->Enable();
            m_pShaders[_eMode]->SetMatrix(m_mWorld, CShader::k_MATRIX_WORLD); 
            m_pShaders[_eMode]->SetMatrix(pCamera->Get_Projection(), CShader::k_MATRIX_PROJECTION);
            m_pShaders[_eMode]->SetMatrix(pCamera->Get_View(), CShader::k_MATRIX_VIEW);
            
            char pStrTextureId[256];
            for(unsigned int i = 0; i < TEXTURES_MAX_COUNT; ++i)
            {
                if( m_pTextures[i] == NULL )
                {
                    continue;
                }
                sprintf(pStrTextureId, "EXT_TEXTURE_0%i",i + 1);
                std::string k_TEXTURE_ID = pStrTextureId;
                m_pShaders[_eMode]->SetTexture(m_pTextures[i]->Get_Handle(), k_TEXTURE_ID);
            }
        }
            break;
        default:
            break;
    }
    
    m_pMesh->Get_VertexBufferRef()->Enable();
    m_pMesh->Get_IndexBufferRef()->Enable();
    glDrawElements(GL_TRIANGLES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IndexBufferRef()->Get_SourceDataFromVRAM());
    m_pMesh->Get_IndexBufferRef()->Disable();
    m_pMesh->Get_VertexBufferRef()->Disable();
    m_pShaders[_eMode]->Disable();
    glCullFace(GL_FRONT);
    
    if(m_pBoundingBox != NULL && INode::E_RENDER_MODE_SIMPLE == _eMode)
    {
        m_pBoundingBox->Render();
    }

}

