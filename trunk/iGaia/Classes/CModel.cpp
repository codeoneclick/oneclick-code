
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
    
    m_pMesh->Get_VertexBufferRef()->Commit();
    m_pMesh->Get_IndexBufferRef()->Commit();
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
            m_pMesh->Get_VertexBufferRef()->Commit();
            m_pMesh->Get_IndexBufferRef()->Commit();
            
            for(unsigned int i = 0; i < CShader::E_RENDER_MODE_MAX; ++i)
            {
                if(m_pShaders[i] != NULL)
                {
                    m_pMesh->Get_VertexBufferRef()->Add_ShaderRef(static_cast<CShader::E_RENDER_MODE>(i), m_pShaders[i]);
                }
            }
            
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

void CModel::Render(CShader::E_RENDER_MODE _eMode)
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
        case CShader::E_RENDER_MODE_SIMPLE:
        {
            if(m_pShaders[_eMode] == NULL)
            {
                std::cout<<"[CModel::Render] Shader MODE_SIMPLE is NULL"<<std::endl;
                return;
            }

            m_pShaders[_eMode]->Enable();
            m_pShaders[_eMode]->Set_Matrix(m_mWorld, CShader::E_ATTRIBUTE_MATRIX_WORLD);
            m_pShaders[_eMode]->Set_Matrix(pCamera->Get_Projection(), CShader::E_ATTRIBUTE_MATRIX_PROJECTION);
            m_pShaders[_eMode]->Set_Matrix(pCamera->Get_View(), CShader::E_ATTRIBUTE_MATRIX_VIEW);
            m_pShaders[_eMode]->Set_Vector3(pCamera->Get_Position(), CShader::E_ATTRIBUTE_VECTOR_CAMERA_POSITION);
            m_pShaders[_eMode]->Set_Vector2(m_vTexCoordOffset, CShader::E_ATTRIBUTE_VECTOR_TEXCOORD_OFFSET);
            m_pShaders[_eMode]->Set_Vector3(pLight->Get_Position(), CShader::E_ATTRIBUTE_VECTOR_LIGHT_POSITION);
            
            for(unsigned int i = 0; i < TEXTURES_MAX_COUNT; ++i)
            {
                if( m_pTextures[i] == NULL )
                {
                    continue;
                }
                m_pShaders[_eMode]->Set_Texture(m_pTextures[i]->Get_Handle(), static_cast<CShader::E_TEXTURE_SLOT>(i));
            }
        }
            break;
        case CShader::E_RENDER_MODE_REFLECTION:
        {
            
        }
            break;
        case CShader::E_RENDER_MODE_REFRACTION:
        {
            
        }
            break;
        case CShader::E_RENDER_MODE_SCREEN_NORMAL_MAP:
        {
            if(m_pShaders[_eMode] == NULL)
            {
                std::cout<<"[CModel::Render] Shader MODE_SCREEN_NORMAL_MAP is NULL"<<std::endl;
                return;
            }
            
            m_pShaders[_eMode]->Enable();
            m_pShaders[_eMode]->Set_Matrix(m_mWorld, CShader::E_ATTRIBUTE_MATRIX_WORLD);
            m_pShaders[_eMode]->Set_Matrix(pCamera->Get_Projection(), CShader::E_ATTRIBUTE_MATRIX_PROJECTION);
            m_pShaders[_eMode]->Set_Matrix(pCamera->Get_View(), CShader::E_ATTRIBUTE_MATRIX_VIEW);
            
            for(unsigned int i = 0; i < TEXTURES_MAX_COUNT; ++i)
            {
                if( m_pTextures[i] == NULL )
                {
                    continue;
                }
                m_pShaders[_eMode]->Set_Texture(m_pTextures[i]->Get_Handle(), static_cast<CShader::E_TEXTURE_SLOT>(i));
            }
        }
            break;
        default:
            break;
    }
    
    m_pMesh->Get_VertexBufferRef()->Enable(_eMode);
    m_pMesh->Get_IndexBufferRef()->Enable();
    glDrawElements(GL_TRIANGLES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IndexBufferRef()->Get_SourceDataFromVRAM());
    m_pMesh->Get_IndexBufferRef()->Disable();
    m_pMesh->Get_VertexBufferRef()->Disable(_eMode);
    m_pShaders[_eMode]->Disable();
    glCullFace(GL_FRONT);
    
    if(m_pBoundingBox != NULL && CShader::E_RENDER_MODE_SIMPLE == _eMode)
    {
        m_pBoundingBox->Render();
    }

}

