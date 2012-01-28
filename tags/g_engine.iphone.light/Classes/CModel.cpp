//
//  CMesh.cpp
//  gEngine
//
//  Created by sergey.sergeev on 11/17/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CModel.h"
#include "CShaderComposite.h"
#include "CCamera.h"
#include "CResourceMgr.h"

CModel::CModel()
{
    m_vScale    = Vector3d(1.0f, 1.0f, 1.0f);
    m_vRotation = Vector3d(0.0f, 0.0f, 0.0f);
    m_vPosition = Vector3d(0.0f, 0.0f, 0.0f);
    
    m_pTextures = new CTexture*[4];
    m_pTextures[0] = NULL;
    m_pTextures[1] = NULL;
    m_pTextures[2] = NULL;
    m_pTextures[3] = NULL;
    
    m_iEffectIndex = 0;
    m_iModelIndex = 0;
    
    m_pCompositeVB = new CVertexBuffer*[3];
    m_pCompositeIB = new unsigned short*[3];
    m_pCompositeIBCount = new unsigned int[3];
}

CModel::~CModel()
{
    
}

void CModel::Load(std::string _sName)
{
    m_pShader = CShaderComposite::Instance()->Get_Shader(CShaderComposite::E_TEXTURE);
    m_pTextures[0] = static_cast<CTexture*>(CResourceMgr::Instance()->Load("mesh_02.pvr", IResource::E_TEXTURE_MGR, IResource::E_PVR_PARSER, IResource::E_BACKGROUND_THREAD));
    
    CParser_M3* pParser = new CParser_M3();
    CParser_M3::SMeshData* pMeshData = pParser->Parse("mesh_01.m3");
    m_pCompositeVB[0] = new CVertexBuffer(pMeshData->m_iVertexCount, sizeof(CVertexBuffer::SVertex));
    CVertexBuffer::SVertex* pData = static_cast<CVertexBuffer::SVertex*>(m_pCompositeVB[0]->Get_Data());  
    for(unsigned int index = 0; index < pMeshData->m_iVertexCount; index++)
    {
        pData[index].m_vPosition = pMeshData->m_vPosition[index];
        pData[index].m_vTexCoord = pMeshData->m_vTexCoord[index];
        pData[index].m_vNormal   = pMeshData->m_vNormal[index];
    }
    m_pCompositeIBCount[0] = pMeshData->m_iIndexCount;
    m_pCompositeVB[0]->Commit();
    m_pCompositeIB[0] = pMeshData->m_pIndeces;
    
    pMeshData = pParser->Parse("mesh_02.m3");
    m_pCompositeVB[1] = new CVertexBuffer(pMeshData->m_iVertexCount, sizeof(CVertexBuffer::SVertex));
    pData = static_cast<CVertexBuffer::SVertex*>(m_pCompositeVB[1]->Get_Data());  
    for(unsigned int index = 0; index < pMeshData->m_iVertexCount; index++)
    {
        pData[index].m_vPosition = pMeshData->m_vPosition[index];
        pData[index].m_vTexCoord = pMeshData->m_vTexCoord[index];
        pData[index].m_vNormal   = pMeshData->m_vNormal[index];
    }
    m_pCompositeIBCount[1] = pMeshData->m_iIndexCount;
    m_pCompositeVB[1]->Commit();
    m_pCompositeIB[1] = pMeshData->m_pIndeces;
    
    pMeshData = pParser->Parse("mesh_03.m3");
    m_pCompositeVB[2] = new CVertexBuffer(pMeshData->m_iVertexCount, sizeof(CVertexBuffer::SVertex));
    pData = static_cast<CVertexBuffer::SVertex*>(m_pCompositeVB[2]->Get_Data());  
    for(unsigned int index = 0; index < pMeshData->m_iVertexCount; index++)
    {
        pData[index].m_vPosition = pMeshData->m_vPosition[index];
        pData[index].m_vTexCoord = pMeshData->m_vTexCoord[index];
        pData[index].m_vNormal   = pMeshData->m_vNormal[index];
    }
    m_pCompositeIBCount[2] = pMeshData->m_iIndexCount;
    m_pCompositeVB[2]->Commit();
    m_pCompositeIB[2] = pMeshData->m_pIndeces;
    
    m_vRotation.x = -1.57f;
    m_vPosition.y = -0.8f;
}

void CModel::UpdateModel()
{
    m_pVb = m_pCompositeVB[m_iModelIndex];
    m_pIb = m_pCompositeIB[m_iModelIndex];
    m_indexCount = m_pCompositeIBCount[m_iModelIndex];
    
    
    switch (m_iModelIndex) 
    {
        case 0:
             m_pTextures[0] = static_cast<CTexture*>(CResourceMgr::Instance()->Load("mesh_01.pvr", IResource::E_TEXTURE_MGR, IResource::E_PVR_PARSER, IResource::E_BACKGROUND_THREAD));
            break;
        case 1:
             m_pTextures[0] = static_cast<CTexture*>(CResourceMgr::Instance()->Load("mesh_02.pvr", IResource::E_TEXTURE_MGR, IResource::E_PVR_PARSER, IResource::E_BACKGROUND_THREAD));
            break;
        case 2:
             m_pTextures[0] = static_cast<CTexture*>(CResourceMgr::Instance()->Load("mesh_03.pvr", IResource::E_TEXTURE_MGR, IResource::E_PVR_PARSER, IResource::E_BACKGROUND_THREAD));
            break;
    }
}

void CModel::UpdateEffect()
{
    switch (m_iEffectIndex) 
    {
        case 0:
            m_pShader = CShaderComposite::Instance()->Get_Shader(CShaderComposite::E_COLOR);
            break;
        case 1:
            m_pShader = CShaderComposite::Instance()->Get_Shader(CShaderComposite::E_TEXTURE);
            break;
        case 2:
            m_pShader = CShaderComposite::Instance()->Get_Shader(CShaderComposite::E_COLOR_VERTEX_DIFFUSE);
            break;
        case 3:
            m_pShader = CShaderComposite::Instance()->Get_Shader(CShaderComposite::E_TEXTURE_VERTEX_DIFFUSE);
            break;
        case 4:
            m_pShader = CShaderComposite::Instance()->Get_Shader(CShaderComposite::E_TEXTURE_PIXEL_DIFFUSE);
            break;
        case 5:
            m_pShader = CShaderComposite::Instance()->Get_Shader(CShaderComposite::E_TEXTURE_PIXEL_DIFFUSE_SPECULAR_COLOR);
            break;
        case 6:
            m_pShader = CShaderComposite::Instance()->Get_Shader(CShaderComposite::E_TEXTURE_PIXEL_DIFFUSE_SPECULAR_TEXTURE);
            break;
        default:
            break;
    }
}

void CModel::Set_Effect(unsigned int _iIndex)
{
    m_iEffectIndex = _iIndex;
}

void CModel::Set_Model(unsigned int _iIndex)
{
    m_iModelIndex = _iIndex;
}

void CModel::Update(float _fTime)
{
    static float fAngle = 0.0f;
    fAngle += 0.02f;
    m_vRotation.y = fAngle;
    Matrix4x4 mRotationX = RotationX(m_vRotation.x);
    Matrix4x4 mRotationY = RotationY(m_vRotation.y);
    Matrix4x4 mRotationZ = RotationZ(m_vRotation.z);
    m_mRotation = mRotationX * mRotationY * mRotationZ;
    m_mTranslation = Translation(m_vPosition);
    m_mScale = Scale(m_vScale);
    m_mWorld = m_mScale * m_mRotation * m_mTranslation;
    
    //m_mMVP = m_mWorld * CCamera::Instance()->Get_View() * CCamera::Instance()->Get_Projection();
    //m_mMVP_INV = Transpose(Inverse(m_mMVP));
}

void CModel::Render()
{
    UpdateEffect();
    UpdateModel();
    glCullFace(GL_FRONT);
    m_pShader->SetMatrix(m_mWorld, CShader::k_MATRIX_WORLD);
    m_pShader->SetMatrix(CCamera::Instance()->Get_Projection(), CShader::k_MATRIX_PROJECTION);
    m_pShader->SetMatrix(CCamera::Instance()->Get_View(), CShader::k_MATRIX_VIEW);
    //m_pShader->SetMatrix(m_mMVP, CShader::k_MATRIX_MVP);
    //m_pShader->SetMatrix(m_mMVP_INV, CShader::k_MATRIX_MVP_INV);
    Vector3d vLight = Vector3d(0.0f, 0.0f, -1.0f);
    m_pShader->SetVector(CCamera::Instance()->Get_Position(), CShader::k_VECTOR_VIEW);
    m_pShader->SetVector(vLight, CShader::k_VECTOR_LIGHT);
    
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
   
    m_pVb->Enable(m_pShader->Get_pHandle());
    glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_SHORT, (void*) m_pIb);
    m_pVb->Disable(m_pShader->Get_pHandle());
}

