//
//  CBoundingBox.cpp
//  gEngine
//
//  Created by sergey.sergeev on 1/4/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CBoundingBox.h"
#include "CShaderComposite.h"
#include "CSceneMgr.h"
#include "CBatchMgr.h"

const float CBoundingBox::k_MAX_VALUE = -4096.0f;
const float CBoundingBox::k_MIN_VALUE = 4096.0f;

CBoundingBox::CBoundingBox(const CVector3d &_vMax, const CVector3d &_vMin)
{
    m_vMax = _vMax;
    m_vMin = _vMin;
    
    m_mWorld = CMatrix4x4(CMatrix4x4::E_MATRIX_ONE);
    
    m_pShader = CShaderComposite::Instance()->Get_Shader(IResource::E_SHADER_COLOR);
    
    CMesh::SSource* pSource = new CMesh::SSource();
    pSource->m_iNumVertexes = 8;
    pSource->m_iNumIndexes  = 24;
    
    pSource->m_pVB = new CVertexBuffer(pSource->m_iNumVertexes, sizeof(CVertexBuffer::SVertexVC), CVertexBuffer::E_VERTEX_BUFFER_MODE_VC);
    CVertexBuffer::SVertexVC* pData = static_cast<CVertexBuffer::SVertexVC*>(pSource->m_pVB->Get_Data());

    pData[0].m_vPosition = CVector3d( m_vMin.x,  m_vMin.y, m_vMax.z);
    pData[1].m_vPosition = CVector3d( m_vMax.x,  m_vMin.y, m_vMax.z);
    pData[2].m_vPosition = CVector3d( m_vMax.x,  m_vMax.y, m_vMax.z);
    pData[3].m_vPosition = CVector3d( m_vMin.x,  m_vMax.y, m_vMax.z);

    pData[4].m_vPosition = CVector3d( m_vMin.x,  m_vMin.y,  m_vMin.z);
    pData[5].m_vPosition = CVector3d( m_vMin.x,  m_vMax.y,  m_vMin.z);
    pData[6].m_vPosition = CVector3d( m_vMax.x,  m_vMax.y,  m_vMin.z);
    pData[7].m_vPosition = CVector3d( m_vMax.x,  m_vMin.y,  m_vMin.z);
    
    for(unsigned int i = 0; i < pSource->m_iNumVertexes; i++)
    {
        pData[i].m_cColor = CColor4(0, 255, 0, 255);
    }

    pSource->m_pIB = new CIndexBuffer(pSource->m_iNumIndexes);
    unsigned short* pIBData = pSource->m_pIB->Get_Data();
    
    pIBData[0] = 0;
    pIBData[1] = 1;
    pIBData[2] = 0;
    pIBData[3] = 3;
    pIBData[4] = 3;
    pIBData[5] = 2;
    pIBData[6] = 1;
    pIBData[7] = 2;
    
    pIBData[8] = 4;
    pIBData[9] = 5;
    pIBData[10] = 4;
    pIBData[11] = 7;
    pIBData[12] = 7;
    pIBData[13] = 6;
    pIBData[14] = 5;
    pIBData[15] = 6;
    
    pIBData[16] = 0;
    pIBData[17] = 4;
    pIBData[18] = 1;
    pIBData[19] = 7;
    pIBData[20] = 2;
    pIBData[21] = 6;
    pIBData[22] = 3;
    pIBData[23] = 5;

    m_pMesh = new CMesh();
    m_pMesh->Set_Source(pSource);
}

CBoundingBox::~CBoundingBox()
{
    
}

void CBoundingBox::Render()
{
    if(m_bIsBatching)
    {
        CBatchMgr::Instance()->PushToBoundingBatch(this);
    }
    else
    {
        glCullFace(GL_BACK);
        m_pShader->Enable();
        m_pShader->SetMatrix(m_mWorld, CShader::k_MATRIX_WORLD);
        ICamera* pCamera = CSceneMgr::Instance()->Get_Camera();
        m_pShader->SetMatrix(pCamera->Get_Projection(), CShader::k_MATRIX_PROJECTION);
        m_pShader->SetMatrix(pCamera->Get_View(), CShader::k_MATRIX_VIEW);
        m_pMesh->Get_VB()->Enable(m_pShader->Get_ProgramHandle());
        glDrawElements(GL_LINES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IB()->Get_Data());
        m_pMesh->Get_VB()->Disable(m_pShader->Get_ProgramHandle());
        m_pShader->Disable();
    }

}