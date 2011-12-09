//
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

void CModel::Load(IResource::SResource _pReosurce)
{
    switch (_pReosurce.m_eMesh)
    {
        case IResource::E_MESH_PRIMITIVE:
            m_pMesh = CMeshComposite::Instance()->Get_Mesh(_pReosurce.m_ePrimitive);
            break;
        case IResource::E_MESH_STATIC:
            m_pMesh = static_cast<CMesh*>(CResourceMgr::Instance()->Load(_pReosurce.m_sMesh, IResource::E_MESH_MGR, IResource::E_MD2_PARSER, IResource::E_BACKGROUND_THREAD));
        default:
            break;
    }
    
    m_pShader = CShaderComposite::Instance()->Get_Shader(_pReosurce.m_eShader);
    
    m_eIntersector = _pReosurce.m_eIntersector;
    
    m_bBatch = _pReosurce.m_bBatch;
    
    for( unsigned int i = 0; i < _pReosurce.m_lTextures.size() && i < 4; i++)
    {
        m_pTextures[i] = static_cast<CTexture*>(CResourceMgr::Instance()->Load(_pReosurce.m_lTextures[i], IResource::E_TEXTURE_MGR, IResource::E_PVR_PARSER, IResource::E_BACKGROUND_THREAD));
    }
}

void CModel::Intersect(bool _bItersected)
{
    m_bIntersected = _bItersected;
    if(_bItersected == true)
    {
        m_vColor = Vector4d(0.0f,1.0f,0.0f,1.0f);
    }
    else
    {
        m_vColor = Vector4d(0.0f,0.0f,0.0f,0.0f);
    }
}

void CModel::Update(float _fTime)
{
    INode::Update(_fTime);
}

void CModel::Render()
{
    CSceneMgr::E_RENDER_STATE eState = CRenderMgr::Instance()->Get_State();
    
    switch (eState)
    {
        case CSceneMgr::E_RENDER_STATE_SCREEN:
        {
            if(m_eIntersector == IResource::E_INTERSECTOR_ONLY)
            {
                return;
            }
            
            if(m_bBatch)
            {
                CSceneMgr::Instance()->PushToBatch(CSceneMgr::E_BATCH_01, this);
            }
            else
            {
                glCullFace(GL_FRONT);
                m_pShader->Enable();
                m_pShader->SetMatrix(m_mWorld, CShader::k_MATRIX_WORLD);
                m_pShader->SetMatrix(CCamera::Instance()->Get_Projection(), CShader::k_MATRIX_PROJECTION);
                m_pShader->SetMatrix(CCamera::Instance()->Get_View(), CShader::k_MATRIX_VIEW);
                m_pShader->SetVector(CCamera::Instance()->Get_Position(), CShader::k_VECTOR_VIEW);
                m_pShader->SetVector(CSceneMgr::Instance()->Get_Light()->Get_Position(), CShader::k_VECTOR_LIGHT);
            
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
                m_pShader->SetColor(m_vColor);
            
                m_pMesh->Get_VB()->Enable(m_pShader->Get_ProgramHandle());
                glDrawElements(GL_TRIANGLES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IB());
                m_pMesh->Get_VB()->Disable(m_pShader->Get_ProgramHandle());
                m_pShader->Disable();
            }
        }
            break;
        case CSceneMgr::E_RENDER_STATE_PICKER:
        {
            if(m_eIntersector == IResource::E_INTERSECTOR_NONE)
            {
                return;
            }
            
            if(m_bBatch)
            {
                CSceneMgr::Instance()->PushToBatch(CSceneMgr::E_BATCH_01, this);
            }
            else
            {
                m_pIntersectorShader->Enable();
                m_pIntersectorShader->SetMatrix(m_mWorld, CShader::k_MATRIX_WORLD);
                m_pIntersectorShader->SetMatrix(CCamera::Instance()->Get_Projection(), CShader::k_MATRIX_PROJECTION);
                m_pIntersectorShader->SetMatrix(CCamera::Instance()->Get_View(), CShader::k_MATRIX_VIEW);
                m_pMesh->Get_VB()->Enable(m_pIntersectorShader->Get_ProgramHandle());
                glDrawElements(GL_TRIANGLES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IB());
                m_pMesh->Get_VB()->Disable(m_pIntersectorShader->Get_ProgramHandle());
                m_pIntersectorShader->Disable();
            }
        }   
            break;

        default:
            break;
    }
}

