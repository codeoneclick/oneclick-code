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

CLandscape::CLandscape()
{
    m_iWidth = 32;
    m_iHeight = 32;
    
    m_pHeightMapSetter = NULL;
    m_pNavigationMesh = NULL;
    m_pVisualNavigationMeshRef = NULL;
    m_pVisualNavigationMeshShader = NULL;
    
    m_bIsNavigationMeshDebug = false;
}

CLandscape::~CLandscape()
{
    
}

void CLandscape::Load(IResource::SResource _tResource)
{
    m_pHeightMapSetter = new CHeightMapSetter();
    m_pMesh = m_pHeightMapSetter->Load_SourceData(_tResource.m_sName, m_iWidth, m_iHeight);
    
    m_pNavigationMesh = new CNavigationMesh();
    m_pNavigationMesh->Set_NavigationModel(this);
    m_pVisualNavigationMeshRef = m_pNavigationMesh->Get_VisualMesh();
    m_pVisualNavigationMeshShader = CShaderComposite::Instance()->Get_Shader(IResource::E_SHADER_COLOR);
    m_pVisualNavigationMeshRef->Get_VB()->Set_ShaderRef(m_pVisualNavigationMeshShader->Get_ProgramHandle());
    CSceneMgr::Instance()->Set_NavigationMeshRef(m_pNavigationMesh);
    CSceneMgr::Instance()->Set_HeightMapSetterRef(m_pHeightMapSetter);
    
    m_pMesh->Get_VB()->CommitFromRAMToVRAM();
    m_pMesh->Get_IB()->CommitFromRAMToVRAM();
}

void CLandscape::OnTouchEvent(void)
{
    CCollisionMgr::SRay3d tTouchRay = CSceneMgr::Instance()->Get_CollisionMgr()->Get_TouchRay();
    glm::vec3 vCollisionPoint;
     
    if(!CSceneMgr::Instance()->Get_CollisionMgr()->Get_CollisionPoint(m_pMesh->Get_VB(), m_pMesh->Get_IB(), tTouchRay, &vCollisionPoint))
    {
        return;
    }
    else
    {
        std::cout<<"[CLandscape::OnTouchEvent] Colission Point = "<<vCollisionPoint.x<<","<<vCollisionPoint.y<<","<<vCollisionPoint.z<<"\n";
    }
    
    CSceneMgr::Instance()->Get_CollisionMgr()->Set_Touch3DPoint(vCollisionPoint);
    for(size_t index = 0; index< m_lDelegates.size(); index++)
    {
        m_lDelegates[index]->OnTouchEvent(m_pDelegateTarget);
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
    
    switch (_eMode)
    {
        case INode::E_RENDER_MODE_SIMPLE:
        {
            m_pMesh->Get_VB()->Set_ShaderRef(m_pShader->Get_ProgramHandle());
            m_pShader->Enable();
            m_pShader->SetMatrix(m_mWorld, CShader::k_MATRIX_WORLD); 
            m_pShader->SetMatrix(pCamera->Get_Projection(), CShader::k_MATRIX_PROJECTION);
            m_pShader->SetMatrix(pCamera->Get_View(), CShader::k_MATRIX_VIEW);
            m_pShader->SetVector(pCamera->Get_Position(), CShader::k_VECTOR_VIEW);
            char pStrTextureId[256];
            for(unsigned int i = 0; i < TEXTURES_MAX_COUNT; ++i)
            {
                if( m_pTextures[i] == NULL )
                {
                    continue;
                }
                sprintf(pStrTextureId, "EXT_TEXTURE_0%i",i + 1);
                std::string k_TEXTURE_ID = pStrTextureId;
                m_pShader->SetTexture(m_pTextures[i]->Get_Handle(), k_TEXTURE_ID);
            }
            if(m_pLight != NULL)
            {
                m_pShader->SetVector(m_pLight->Get_Position(), CShader::k_VECTOR_LIGHT);
            }
            
            m_pShader->SetTexture(m_pHeightMapSetter->Get_SplattingTexture(), CShader::k_TEXTURE_07);
        }
            break;
        case INode::E_RENDER_MODE_EDGE_DETECTED:
        {
            
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

        default:
            break;
    }
    
    m_pMesh->Get_VB()->Enable();
    m_pMesh->Get_IB()->Enable();
    glDrawElements(GL_TRIANGLES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IB()->Get_DataFromVRAM());
    m_pMesh->Get_IB()->Disable();
    m_pMesh->Get_VB()->Disable();
    m_pShader->Disable();
    glCullFace(GL_FRONT);

    
    if(m_pVisualNavigationMeshRef != NULL && m_bIsNavigationMeshDebug == true)
    {
        m_pVisualNavigationMeshShader->Enable();
        m_pVisualNavigationMeshShader->SetMatrix(m_mWorld, CShader::k_MATRIX_WORLD);
        ICamera* pCamera = CSceneMgr::Instance()->Get_Camera();
        m_pVisualNavigationMeshShader->SetMatrix(pCamera->Get_Projection(), CShader::k_MATRIX_PROJECTION);
        m_pVisualNavigationMeshShader->SetMatrix(pCamera->Get_View(), CShader::k_MATRIX_VIEW);
        m_pVisualNavigationMeshShader->SetVector(pCamera->Get_Position(), CShader::k_VECTOR_VIEW);
        
        m_pVisualNavigationMeshRef->Get_VB()->Enable();
        glDrawElements(GL_TRIANGLES, m_pVisualNavigationMeshRef->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*)m_pVisualNavigationMeshRef->Get_IB()->Get_Data());
        m_pVisualNavigationMeshRef->Get_VB()->Disable();
        m_pVisualNavigationMeshShader->Disable();
    }
    
    if(m_pBoundingBox != NULL)
    {
        m_pBoundingBox->Render();
    }
}




