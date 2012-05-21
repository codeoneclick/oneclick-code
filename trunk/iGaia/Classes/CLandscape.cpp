//
//  CLandscape.cpp
//  iGaia
//
//  Created by sergey.sergeev on 1/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CLandscape.h"
#include "CSceneMgr.h"
#include "CRenderMgr.h"
#include "CCollisionMgr.h"

CLandscape::CLandscape(void)
{
    m_iWidth = 32;
    m_iHeight = 32;
    m_pHeightMapSetter = NULL;
}

CLandscape::~CLandscape(void)
{
    
}

void CLandscape::Load(const std::string& _sName, IResource::E_THREAD _eThread)
{
    m_pHeightMapSetter = new CHeightMapSetter();
    m_pMesh = m_pHeightMapSetter->Load_DataSource(_sName, m_iWidth, m_iHeight);
    
    CSceneMgr::Instance()->Set_HeightMapSetterRef(m_pHeightMapSetter);
    
    glm::u8vec4* pColorData = m_pMesh->Get_VertexBufferRef()->CreateOrReUse_ColorData();
    unsigned char iUniqueColorId = CSceneMgr::Instance()->Get_UniqueColorId(this);
    for(unsigned int i = 0; i < m_pMesh->Get_NumVertexes(); ++i)
    {
        pColorData[i] = glm::u8vec4(iUniqueColorId, iUniqueColorId, iUniqueColorId, 255);
    }
    
    m_pMesh->Get_VertexBufferRef()->CommitToRAM();
    m_pMesh->Get_VertexBufferRef()->CommitFromRAMToVRAM();
    m_pMesh->Get_IndexBufferRef()->CommitFromRAMToVRAM();
}

void CLandscape::OnResourceLoadDoneEvent(IResource::E_RESOURCE_TYPE _eType, IResource *_pResource)
{
    switch (_eType)
    {
        case IResource::E_RESOURCE_TYPE_MESH:
            std::cout<<"[CModel::OnLoadDone] Resource Mesh loaded : "<<_pResource->Get_Name()<<"\n";
            break;
        case IResource::E_RESOURCE_TYPE_TEXTURE:
            std::cout<<"[CModel::OnLoadDone] Resource Texture loaded : "<<_pResource->Get_Name()<<"\n";
            break;
        default:
            break;
    }
}

void CLandscape::OnTouchEvent(ITouchDelegate *_pDelegateOwner)
{
    CCollisionMgr::SRay3d tTouchRay = CSceneMgr::Instance()->Get_CollisionMgr()->Get_TouchRay();
    glm::vec3 vCollisionPoint;
    
    if(!CSceneMgr::Instance()->Get_CollisionMgr()->Get_CollisionPoint(m_pMesh->Get_VertexBufferRef(), m_pMesh->Get_IndexBufferRef(), tTouchRay, &vCollisionPoint))
    {
        return;
    }
    else
    {
        std::cout<<"[CLandscape::OnTouchEvent] Colission Point = "<<vCollisionPoint.x<<","<<vCollisionPoint.y<<","<<vCollisionPoint.z<<"\n";
    }
    
    CSceneMgr::Instance()->Get_CollisionMgr()->Set_Touch3DPoint(vCollisionPoint);
    
    for(size_t index = 0; index< m_lDelegateOwners.size(); index++)
    {
        if(m_lDelegateOwners[index]->Get_DelegateType() == IDelegate::E_DELEGATE_TYPE_TOUCH)
        {
            dynamic_cast<ITouchDelegate*>(m_lDelegateOwners[index])->OnTouchEvent(this);
        }
    }
}

void CLandscape::Update()
{
    INode::Update();
}

void CLandscape::Render(INode::E_RENDER_MODE _eMode)
{      
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

            m_pShaders[_eMode]->SetTexture(m_pHeightMapSetter->Get_TextureSplatting(), CShader::k_TEXTURE_07);
            m_pShaders[_eMode]->SetVector4(glm::vec4(0.0f, 1.0, 0.0, 0.1), CShader::k_VECTOR_CLIP_PLANE);
        }
            break;
        case INode::E_RENDER_MODE_REFLECTION:
        {
            if(m_pShaders[_eMode] == NULL)
            {
                std::cout<<"[CModel::Render] Shader MODE_REFLECTION is NULL"<<std::endl;
                return;
            }
            m_pMesh->Get_VertexBufferRef()->Set_ShaderRef(m_pShaders[_eMode]->Get_ProgramHandle());
            m_pShaders[_eMode]->Enable();
            m_pShaders[_eMode]->SetMatrix(m_mWorld, CShader::k_MATRIX_WORLD); 
            m_pShaders[_eMode]->SetMatrix(pCamera->Get_Projection(), CShader::k_MATRIX_PROJECTION);
            m_pShaders[_eMode]->SetMatrix(pCamera->Get_View(), CShader::k_MATRIX_VIEW);
            m_pShaders[_eMode]->SetVector3(pCamera->Get_Position(), CShader::k_VECTOR_VIEW);
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
            
            m_pShaders[_eMode]->SetTexture(m_pHeightMapSetter->Get_TextureSplatting(), CShader::k_TEXTURE_07);
            m_pShaders[_eMode]->SetVector4(glm::vec4(0.0f, 1.0, 0.0, 0.1), CShader::k_VECTOR_CLIP_PLANE);
        }
            break;
        case INode::E_RENDER_MODE_REFRACTION:
        {
            if(m_pShaders[_eMode] == NULL)
            {
                std::cout<<"[CModel::Render] Shader MODE_REFRACTION is NULL"<<std::endl;
                return;
            }
            m_pMesh->Get_VertexBufferRef()->Set_ShaderRef(m_pShaders[_eMode]->Get_ProgramHandle());
            m_pShaders[_eMode]->Enable();
            m_pShaders[_eMode]->SetMatrix(m_mWorld, CShader::k_MATRIX_WORLD); 
            m_pShaders[_eMode]->SetMatrix(pCamera->Get_Projection(), CShader::k_MATRIX_PROJECTION);
            m_pShaders[_eMode]->SetMatrix(pCamera->Get_View(), CShader::k_MATRIX_VIEW);
            m_pShaders[_eMode]->SetVector3(pCamera->Get_Position(), CShader::k_VECTOR_VIEW);
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
            
            m_pShaders[_eMode]->SetTexture(m_pHeightMapSetter->Get_TextureSplatting(), CShader::k_TEXTURE_07);
            m_pShaders[_eMode]->SetVector4(glm::vec4(0.0f, -1.0, 0.0, 0.1), CShader::k_VECTOR_CLIP_PLANE);
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
            m_pShaders[_eMode]->SetVector4(glm::vec4(0.0f, 1.0, 0.0, 0.1), CShader::k_VECTOR_CLIP_PLANE);
        }
            break;
        default:
            break;
    }
    
    m_pMesh->Get_VertexBufferRef()->Enable();
    m_pMesh->Get_IndexBufferRef()->Enable();
    glDrawElements(GL_TRIANGLES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IndexBufferRef()->Get_DataFromVRAM());
    m_pMesh->Get_IndexBufferRef()->Disable();
    m_pMesh->Get_VertexBufferRef()->Disable();
    m_pShaders[_eMode]->Disable();
    glCullFace(GL_FRONT);
    
    if(m_pBoundingBox != NULL)
    {
        m_pBoundingBox->Render();
    }
}




