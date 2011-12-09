//
//  CMovieModel.cpp
//  gEngine
//
//  Created by sergey.sergeev on 12/1/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CMovieModel.h"
#include "CSceneMgr.h"
#include "CRenderMgr.h"

CMovieModel::CMovieModel()
{
    m_fLastUpdateFrameTime = 0.0f;
    m_fFrameTimeInterval = 0.33f;
    m_iCurrentFrame = 0;
}

CMovieModel::~CMovieModel()
{
    
}

void CMovieModel::Load(IResource::SResource _pReosurce)
{
    switch (_pReosurce.m_eMesh)
    {
        case IResource::E_MESH_MOVIE:
            m_pMesh = static_cast<CMesh*>(CResourceMgr::Instance()->Load(_pReosurce.m_sMesh, IResource::E_MESH_MGR, IResource::E_GMESH_PARSER, IResource::E_BACKGROUND_THREAD));
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

void CMovieModel::Intersect(bool _bItersected)
{
    m_bIntersected = _bItersected;
}

void CMovieModel::UpdateFrames(float _fTime)
{
    unsigned int iTotalFrames = m_pMesh->Get_FramesCount();
    if(m_iCurrentFrame >= iTotalFrames)
    {
        m_iCurrentFrame = 0;
    }
    
    if(m_pMesh->Get_Sequence().size() > 0)
    {
        CMesh::SVertex* pSequenceNode = m_pMesh->Get_Sequence()[m_iCurrentFrame];
        CVertexBuffer::SVertex* pData = static_cast<CVertexBuffer::SVertex*>(m_pMesh->Get_VB()->Get_Data());  
        unsigned int i = 0;
        for(unsigned int index = 0; index < m_pMesh->Get_NumIndexes() / 3; index++)
        {
            pData[i].m_vPosition = pSequenceNode[i].m_vPosition;
            pData[i].m_vNormal = pSequenceNode[i].m_vNormal;
            i++;
            
            pData[i].m_vPosition = pSequenceNode[i].m_vPosition;
            pData[i].m_vNormal = pSequenceNode[i].m_vNormal;
            i++;
            
            pData[i].m_vPosition = pSequenceNode[i].m_vPosition;
            pData[i].m_vNormal = pSequenceNode[i].m_vNormal;
            i++;
        }
        
        m_fLastUpdateFrameTime += m_fFrameTimeInterval;
        if(m_fLastUpdateFrameTime > 1.0f)
        {
            m_iCurrentFrame++;
            m_fLastUpdateFrameTime = 0.0f;
        }
    }
}

void CMovieModel::UpdateBones(float _fTime)
{
    
}

void CMovieModel::Update(float _fTime)
{
    INode::Update(_fTime);
}

void CMovieModel::Render()
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
                CSceneMgr::Instance()->PushToBatch(CSceneMgr::E_BATCH_02, this);
            }
            else
            {
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
            }
            
            m_pMesh->Get_VB()->Enable(m_pShader->Get_ProgramHandle());
            glDrawElements(GL_TRIANGLES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IB());
            m_pMesh->Get_VB()->Disable(m_pShader->Get_ProgramHandle());
            m_pShader->Disable();
        }
            break;
            
        case CSceneMgr::E_RENDER_STATE_PICKER:
        {
            if(m_eIntersector == IResource::E_INTERSECTOR_NONE)
            {
                return;
            }
            m_pIntersectorShader->Enable();
            m_pIntersectorShader->SetMatrix(m_mWorld, CShader::k_MATRIX_WORLD);
            m_pIntersectorShader->SetMatrix(CCamera::Instance()->Get_Projection(), CShader::k_MATRIX_PROJECTION);
            m_pIntersectorShader->SetMatrix(CCamera::Instance()->Get_View(), CShader::k_MATRIX_VIEW);
            m_pMesh->Get_VB()->Enable(m_pIntersectorShader->Get_ProgramHandle());
            glDrawElements(GL_TRIANGLES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IB());
            m_pMesh->Get_VB()->Disable(m_pIntersectorShader->Get_ProgramHandle());
            m_pIntersectorShader->Disable();
        }
            break;
            
        default:
            break;
    }
}

