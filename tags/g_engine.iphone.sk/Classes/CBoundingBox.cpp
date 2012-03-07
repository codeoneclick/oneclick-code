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

CMesh* CBoundingBox::m_pMesh = NULL;

CMesh* CBoundingBox::Get_BoundingBoxMesh(void)
{
    if(m_pMesh == NULL)
    {
        CVector3d m_vMin = CVector3d( -0.5f, -1.0f, -0.5f);
        CVector3d m_vMax = CVector3d(  0.5f,  0.0f,  0.5f);

        CMesh::SSource* pSource = new CMesh::SSource();
        pSource->m_iNumVertexes = 8;
        pSource->m_iNumIndexes  = 24;
    
        pSource->m_pVB = new CVertexBuffer(pSource->m_iNumVertexes);
        
        CVector3d* pPositionData = pSource->m_pVB->CreateOrReUse_PositionData();
        CColor4* pColorData = pSource->m_pVB->CreateOrReUse_ColorData();
    
        pPositionData[0] = CVector3d( m_vMin.x,  m_vMin.y, m_vMax.z);
        pPositionData[1] = CVector3d( m_vMax.x,  m_vMin.y, m_vMax.z);
        pPositionData[2] = CVector3d( m_vMax.x,  m_vMax.y, m_vMax.z);
        pPositionData[3] = CVector3d( m_vMin.x,  m_vMax.y, m_vMax.z);
    
        pPositionData[4] = CVector3d( m_vMin.x,  m_vMin.y,  m_vMin.z);
        pPositionData[5] = CVector3d( m_vMin.x,  m_vMax.y,  m_vMin.z);
        pPositionData[6] = CVector3d( m_vMax.x,  m_vMax.y,  m_vMin.z);
        pPositionData[7] = CVector3d( m_vMax.x,  m_vMin.y,  m_vMin.z);
    
        for(unsigned int i = 0; i < pSource->m_iNumVertexes; i++)
        {
            pColorData[i] = CColor4(0, 255, 0, 255);
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
        m_pMesh->Get_VB()->CommitToRAM();
    }
    return m_pMesh;
}

CBoundingBox::CBoundingBox(const CVector3d &_vMax, const CVector3d &_vMin)
{
    m_vMax = _vMax;
    m_vMin = _vMin;
    
    m_vScale = m_vMin - m_vMax;
    
    m_mWorld = CMatrix4x4(CMatrix4x4::E_MATRIX_ONE);
    m_pShader = CShaderComposite::Instance()->Get_Shader(IResource::E_SHADER_COLOR);
    Get_BoundingBoxMesh();
    
    m_pMesh->Get_VB()->Set_ShaderRef(m_pShader->Get_ProgramHandle());
}

void CBoundingBox::Set_WorldMatrix(const CMatrix4x4 &_mWorld)
{
    CMatrix4x4 mScale = Scale(m_vScale);
    m_mWorld = mScale * _mWorld;
}

CBoundingBox::~CBoundingBox()
{
    
}

void CBoundingBox::Render()
{
    if(m_bIsBatching)
    {
        CSceneMgr::Instance()->Get_BatchMgr()->PushToBoundingBatch(this);
    }
    else
    {
        glCullFace(GL_BACK);
        m_pShader->Enable();
        m_pShader->SetMatrix(m_mWorld, CShader::k_MATRIX_WORLD);
        ICamera* pCamera = CSceneMgr::Instance()->Get_Camera();
        m_pShader->SetMatrix(pCamera->Get_Projection(), CShader::k_MATRIX_PROJECTION);
        m_pShader->SetMatrix(pCamera->Get_View(), CShader::k_MATRIX_VIEW);
        m_pMesh->Get_VB()->Enable();
        glDrawElements(GL_LINES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IB()->Get_Data());
        m_pMesh->Get_VB()->Disable();
        m_pShader->Disable();
    }

}