//
//  CColliderBox.cpp
//  gEngine
//
//  Created by sergey.sergeev on 1/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CColliderBox.h"
#include "CShaderComposite.h"
#include "CSceneMgr.h"
#include "CBatchMgr.h"

CColliderBox::CColliderBox(const glm::vec3 &_vMax, const glm::vec3 &_vMin)
{
    /*m_vMax = _vMax;
    m_vMin = _vMin;
    
    m_mWorld = CMatrix4x4(CMatrix4x4::E_MATRIX_ONE);
    
    m_pShader = CShaderComposite::Instance()->Get_Shader(IResource::E_SHADER_COLOR);
    
    CMesh::SSource* pSource = new CMesh::SSource();
    pSource->m_iNumVertexes = 24;
    pSource->m_iNumIndexes  = 36;
    
    pSource->m_pVB = new CVertexBuffer(pSource->m_iNumVertexes, sizeof(CVertexBuffer::SVertexVC), CVertexBuffer::E_VERTEX_BUFFER_MODE_VC);
    CVertexBuffer::SVertexVC* pData = static_cast<CVertexBuffer::SVertexVC*>(pSource->m_pVB->Get_Data());
    
    pData[0].m_vPosition = CVector3d( m_vMin.x,  m_vMin.y, m_vMax.z);
    pData[1].m_vPosition = CVector3d( m_vMax.x,  m_vMin.y, m_vMax.z);
    pData[2].m_vPosition = CVector3d( m_vMax.x,  m_vMax.y, m_vMax.z);
    pData[3].m_vPosition = CVector3d( m_vMin.x,  m_vMax.y, m_vMax.z);
    // Back
    pData[4].m_vPosition = CVector3d( m_vMin.x,  m_vMin.y,  m_vMin.z);
    pData[5].m_vPosition = CVector3d( m_vMin.x,  m_vMax.y,  m_vMin.z);
    pData[6].m_vPosition = CVector3d( m_vMax.x,  m_vMax.y,  m_vMin.z);
    pData[7].m_vPosition = CVector3d( m_vMax.x,  m_vMin.y,  m_vMin.z);
    // Left
    pData[8].m_vPosition = CVector3d( m_vMin.x,  m_vMax.y,  m_vMin.z);
    pData[9].m_vPosition = CVector3d( m_vMin.x,  m_vMax.y,  m_vMax.z);
    pData[10].m_vPosition = CVector3d( m_vMax.x,  m_vMax.y,  m_vMax.z);
    pData[11].m_vPosition = CVector3d( m_vMax.x,  m_vMax.y,  m_vMin.z);
    // Right
    pData[12].m_vPosition = CVector3d( m_vMin.x,  m_vMin.y,  m_vMin.z);
    pData[13].m_vPosition = CVector3d( m_vMax.x,  m_vMin.y,  m_vMin.z);
    pData[14].m_vPosition = CVector3d( m_vMax.x,  m_vMin.y,  m_vMax.z);
    pData[15].m_vPosition = CVector3d( m_vMin.x,  m_vMin.y,  m_vMax.z);
    // Top
    pData[16].m_vPosition = CVector3d( m_vMax.x,  m_vMin.y,  m_vMin.z);
    pData[17].m_vPosition = CVector3d( m_vMax.x,  m_vMax.y,  m_vMin.z);
    pData[18].m_vPosition = CVector3d( m_vMax.x,  m_vMax.y,  m_vMax.z);
    pData[19].m_vPosition = CVector3d( m_vMax.x,  m_vMin.y,  m_vMax.z);
    // Bottom
    pData[20].m_vPosition = CVector3d( m_vMin.x,  m_vMin.y,  m_vMin.z);
    pData[21].m_vPosition = CVector3d( m_vMin.x,  m_vMin.y,  m_vMax.z);
    pData[22].m_vPosition = CVector3d( m_vMin.x,  m_vMax.y,  m_vMax.z);
    pData[23].m_vPosition = CVector3d( m_vMin.x,  m_vMax.y,  m_vMin.z);
    
    pSource->m_pIB = new CIndexBuffer(pSource->m_iNumIndexes);
    unsigned short* pIBData = pSource->m_pIB->Get_Data();
    
    // Front
    pIBData[0] = 0;
    pIBData[1] = 1;
    pIBData[2] = 2;
    pIBData[3] = 0;
    pIBData[4] = 2;
    pIBData[5] = 3;
    // Back
    pIBData[6] = 4;
    pIBData[7] = 5;
    pIBData[8] = 6;
    pIBData[9] = 4;
    pIBData[10] = 6;
    pIBData[11] = 7;
    // Left
    pIBData[12] = 8;
    pIBData[13] = 9;
    pIBData[14] = 10;
    pIBData[15] = 8;
    pIBData[16] = 10;
    pIBData[17] = 11;
    // Right
    pIBData[18] = 12;
    pIBData[19] = 13;
    pIBData[20] = 14;
    pIBData[21] = 12;
    pIBData[22] = 14;
    pIBData[23] = 15;
    // Top
    pIBData[24] = 16;
    pIBData[25] = 17;
    pIBData[26] = 18;
    pIBData[27] = 16;
    pIBData[28] = 18;
    pIBData[29] = 19;
    // Bottom
    pIBData[30] = 20;
    pIBData[31] = 21;
    pIBData[32] = 22;
    pIBData[33] = 20;
    pIBData[34] = 22;
    pIBData[35] = 23;
    
    m_pMesh = new CMesh();
    m_pMesh->Set_Source(pSource);
    m_pMesh->Get_VB()->Set_ShaderRef(m_pShader->Get_ProgramHandle());*/
}

CColliderBox::~CColliderBox()
{
    
}

void CColliderBox::Render()
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












