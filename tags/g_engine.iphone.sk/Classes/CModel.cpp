
//  CModel.cpp
//  gEngine
//
//  Created by sergey.sergeev on 11/17/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CModel.h"
#include "CSceneMgr.h"
#include "CRenderMgr.h"

CModel::CModel()
{
    
}

CModel::~CModel()
{
    
}

void CModel::Load(IResource::SResource _tResource)
{
    if(_tResource.m_eModel != IResource::E_STANDART_MODEL_NONE)
    {
        m_pMesh = CMeshComposite::Instance()->Get_Mesh(_tResource.m_eModel);
    }
    else
    {
        m_pMesh = static_cast<CMesh*>(CResourceMgr::Instance()->Load(_tResource.m_sName, IResource::E_MGR_MESH, _tResource.m_eThread));
    }
    
    m_bIsBatching = _tResource.m_bIsBatching;
}

void CModel::OnTouchEvent(void)
{
    CRay3d tTouchRay = CSceneMgr::Instance()->Get_CollisionMgr()->Get_TouchRay();
    CVector3d vCollisionPoint;
    
    if(!CSceneMgr::Instance()->Get_CollisionMgr()->Get_CollisionPoint(m_pBoundingBox->Get_Mesh()->Get_VB(), m_pBoundingBox->Get_Mesh()->Get_IB(), CVertexBuffer::E_VERTEX_BUFFER_MODE_VC, tTouchRay, &vCollisionPoint))
    {
        return;
    }
    else
    {
        std::cout<<"[CModel::OnTouchEven] Colission Point = "<<vCollisionPoint.x<<","<<vCollisionPoint.y<<","<<vCollisionPoint.z<<"\n";
    }
    
    for(size_t index = 0; index < m_lDelegates.size(); index++)
    {
        m_lDelegates[index]->OnTouchEvent(m_pDelegateTarget);
    }
}

void CModel::Update()
{
    INode::Update();
}

void CModel::Render()
{     
    if(m_bIsBatching)
    {
        
    }
    else
    {
        glCullFace(GL_FRONT);
        m_pShader->Enable();
        m_pShader->SetMatrix(m_mWorld, CShader::k_MATRIX_WORLD);
        ICamera* pCamera = CSceneMgr::Instance()->Get_Camera();
               
        m_pShader->SetMatrix(pCamera->Get_Projection(), CShader::k_MATRIX_PROJECTION);
        m_pShader->SetMatrix(pCamera->Get_View(), CShader::k_MATRIX_VIEW);
        
        m_pShader->SetVector(pCamera->Get_Position(), CShader::k_VECTOR_VIEW);
        
        if(m_pLight != NULL)
        {
            m_pShader->SetVector(m_pLight->Get_Position(), CShader::k_VECTOR_LIGHT);
        }
            
        if( m_pTextures[0] != NULL)
        {
            m_pShader->SetTexture(m_pTextures[0]->Get_Handle(), CShader::k_TEXTURE_01);
        }
        if( m_pTextures[1] != NULL)
        {
            m_pShader->SetTexture(m_pTextures[1]->Get_Handle(), CShader::k_TEXTURE_02);
        }
        if( m_pTextures[2] != NULL)
        {
            m_pShader->SetTexture(m_pTextures[2]->Get_Handle(), CShader::k_TEXTURE_03);
        }
        if( m_pTextures[3] != NULL)
        {
            m_pShader->SetTexture(m_pTextures[3]->Get_Handle(), CShader::k_TEXTURE_04);
        }
            
        m_pMesh->Get_VB()->Enable();
        glDrawElements(GL_TRIANGLES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IB()->Get_Data());
        m_pMesh->Get_VB()->Disable();
        m_pShader->Disable();
    }
    
    if(m_pBoundingBox != NULL)
    {
        m_pBoundingBox->Render();
    }

}

