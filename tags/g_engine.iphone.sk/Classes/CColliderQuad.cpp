//
//  CColliderQuad.cpp
//  gEngine
//
//  Created by sergey.sergeev on 1/17/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CColliderQuad.h"
#include "CShaderComposite.h"
#include "CSceneMgr.h"
#include "CBatchMgr.h"

CColliderQuad::CColliderQuad(const glm::vec3 &_vPoint_01, const glm::vec3 &_vPoint_02, const glm::vec3 &_vPoint_03, const glm::vec3 &_vPoint_04)
{
    /*m_mWorld = CMatrix4x4(CMatrix4x4::E_MATRIX_ONE);
    
    m_pShader = CShaderComposite::Instance()->Get_Shader(IResource::E_SHADER_COLOR);
    
    CMesh::SSource* pSource = new CMesh::SSource();
    pSource->m_iNumVertexes = 4;
    pSource->m_iNumIndexes  = 6; 
    
    pSource->m_pIB = new CIndexBuffer(pSource->m_iNumIndexes);
    unsigned short* pIBData = pSource->m_pIB->Get_Data();
    pIBData[0] = 0;
    pIBData[1] = 1;
    pIBData[2] = 2;
    pIBData[3] = 2;
    pIBData[4] = 3;
    pIBData[5] = 0;
    
    pSource->m_pVB = new CVertexBuffer(pSource->m_iNumVertexes, sizeof(CVertexBuffer::SVertexVC), CVertexBuffer::E_VERTEX_BUFFER_MODE_VC);
    CVertexBuffer::SVertexVC* pData = static_cast<CVertexBuffer::SVertexVC*>(pSource->m_pVB->Get_Data());
    
    pData[0].m_vPosition = _vPoint_01;
    pData[1].m_vPosition = _vPoint_02;
    pData[2].m_vPosition = _vPoint_03;
    pData[3].m_vPosition = _vPoint_04;
    
    m_pMesh = new CMesh();
    m_pMesh->Set_Source(pSource);
    m_pMesh->Get_VB()->Set_ShaderRef(m_pShader->Get_ProgramHandle());*/
}

CColliderQuad::~CColliderQuad()
{
    
}

void CColliderQuad::Render()
{
    /*if(m_bIsBatching)
    {
        CSceneMgr::Instance()->Get_BatchMgr()->PushToColliderBatch(this);
    }
    else
    {
        m_pShader->Enable();
        m_pShader->SetMatrix(m_mWorld, CShader::k_MATRIX_WORLD);
        ICamera* pCamera = CSceneMgr::Instance()->Get_Camera();
        m_pShader->SetMatrix(pCamera->Get_Projection(), CShader::k_MATRIX_PROJECTION);
        m_pShader->SetMatrix(pCamera->Get_View(), CShader::k_MATRIX_VIEW);
        m_pMesh->Get_VB()->Enable();
        glDrawElements(GL_TRIANGLES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IB()->Get_Data());
        m_pMesh->Get_VB()->Disable();
        m_pShader->Disable();
    }*/
}
