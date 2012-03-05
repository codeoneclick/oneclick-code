//
//  CScreenSpacePostMgr.cpp
//  gEngine
//
//  Created by sergey.sergeev on 3/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CScreenSpacePostMgr.h"
#include "CWindow.h"
#include "CSceneMgr.h"
#include "CResourceMgr.h"

CScreenSpacePostMgr::CScreenSpacePostMgr(void)
{
    glGenTextures(1, &m_hTexturePostSimple);
    glBindTexture(GL_TEXTURE_2D, m_hTexturePostSimple);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, CWindow::Get_Width(), CWindow::Get_Height(), 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, 0);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glGenTextures(1, &m_hTexturePostBloomExtract);
    glBindTexture(GL_TEXTURE_2D, m_hTexturePostBloomExtract);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, CWindow::Get_Width(), CWindow::Get_Height(), 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, 0);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glGenTextures(1, &m_hTexturePostBloomCombine);
    glBindTexture(GL_TEXTURE_2D, m_hTexturePostBloomCombine);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, CWindow::Get_Width(), CWindow::Get_Height(), 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, 0);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glGenTextures(1, &m_hTexturePostBlur);
    glBindTexture(GL_TEXTURE_2D, m_hTexturePostBlur);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, CWindow::Get_Width(), CWindow::Get_Height(), 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, 0);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    glGenFramebuffers(1, &m_hOffScreenFrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_hOffScreenFrameBuffer);
    
    glGenRenderbuffers(1, &m_hDepthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_hDepthBuffer);
    
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, CWindow::Get_Width(), CWindow::Get_Height());
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_hDepthBuffer);
    
    GLuint uStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if(uStatus != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout<<"[CScreenSpacePostMgr::CScreenSpacePostMgr] Offscreen Framebuffer FAILURE \n";
    }
    
    glGenRenderbuffers(1, &m_hRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_hRenderBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_RGB, CWindow::Get_Width(), CWindow::Get_Height());
    
    glGenFramebuffers(1, &m_hScreenFrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_hScreenFrameBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_hRenderBuffer);
    
    uStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if(uStatus != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout<<"[CScreenSpacePostMgr::CScreenSpacePostMgr] Screen Framebuffer FAILURE \n";
    }
    
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_BLEND);
    glViewport(0, 0, CWindow::Get_Width(), CWindow::Get_Height());
    CWindow::Set_Viewport(0, 0, CWindow::Get_Width(), CWindow::Get_Height());
    
    CMesh::SSource* pSource = new CMesh::SSource();
    pSource->m_iNumVertexes = 4;
    pSource->m_iNumIndexes  = 6;
    
    pSource->m_pVB = new CVertexBuffer(pSource->m_iNumVertexes, sizeof(CVertexBuffer::SVertexVTN), CVertexBuffer::E_VERTEX_BUFFER_MODE_VTN);
    CVertexBuffer::SVertexVTN* pData = static_cast<CVertexBuffer::SVertexVTN*>(pSource->m_pVB->Get_Data());
    
    unsigned i = 0;
    pData[i].m_vPosition = CVector3d(-1.0f,-1.0f,0.0f);
    pData[i].m_vTexCoord = CVector2d(0.0f,0.0f);
    i++;
    pData[i].m_vPosition = CVector3d(-1.0f,1.0f,0.0f);
    pData[i].m_vTexCoord = CVector2d(0.0f,1.0f);
    i++;
    pData[i].m_vPosition = CVector3d(1.0f,-1.0f,0.0f);
    pData[i].m_vTexCoord = CVector2d(1.0f,0.0f);
    i++;
    pData[i].m_vPosition = CVector3d(1.0f,1.0f,0.0f);
    pData[i].m_vTexCoord = CVector2d(1.0f,1.0f);
    i++;

    pSource->m_pIB = new CIndexBuffer(pSource->m_iNumIndexes);
    unsigned short* pIBData = pSource->m_pIB->Get_Data();
    
    i = 0;
    unsigned short iValue = 0;
    pIBData[i++] = iValue; iValue++;
    pIBData[i++] = iValue; iValue++;
    pIBData[i++] = iValue; iValue--;
    
    pIBData[i++] = iValue; iValue++;
    pIBData[i++] = iValue; iValue++;
    pIBData[i++] = iValue; iValue++;
    
    m_pMesh = new CMesh();
    m_pMesh->Set_Source(pSource);
    
    m_pShaderPostSimple = CShaderComposite::Instance()->Get_Shader(IResource::E_SHADER_TEXTURE);
    m_pShaderPostBloomExtract = CShaderComposite::Instance()->Get_Shader(IResource::E_SHADER_BLOOM_EXTRACT);
    m_pShaderPostBloomCombine = CShaderComposite::Instance()->Get_Shader(IResource::E_SHADER_BLOOM_COMBINE);
    m_pShaderPostBlur = CShaderComposite::Instance()->Get_Shader(IResource::E_SHADER_BLUR);
}

CScreenSpacePostMgr::~CScreenSpacePostMgr(void)
{                               
    
}

void CScreenSpacePostMgr::BindRenderBufferAsBuffer(void)
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_hScreenFrameBuffer);
    glViewport(0, 0, CWindow::Get_Width(), CWindow::Get_Height());
}

void CScreenSpacePostMgr::BindRenderBufferAsTexture(CScreenSpacePostMgr::E_POST_TEXTURE _ePostTexture)
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_hOffScreenFrameBuffer);
    glViewport(0, 0, CWindow::Get_Width(), CWindow::Get_Height());
    
    switch (_ePostTexture)
    {
        case E_POST_TEXTURE_SIMPLE:
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_hTexturePostSimple, 0);
            break;
        case E_POST_TEXTURE_BLOOM_EXTRACT:
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_hTexturePostBloomExtract, 0);
            break;
        case E_POST_TEXTURE_BLOOM_COMBINE:
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_hTexturePostBloomCombine, 0);
            break;
        case E_POST_TEXTURE_BLUR:
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_hTexturePostBlur, 0);
            break;
        default:
            break;
    }
}

void CScreenSpacePostMgr::Render_PostSimple(void)
{
    if(m_pMesh->Get_VB() != NULL)
    {
        m_pMesh->Get_VB()->Set_ShaderRef(m_pShaderPostSimple->Get_ProgramHandle());
    }
    m_pShaderPostSimple->Enable();
    m_pShaderPostSimple->SetTexture(m_hTexturePostBloomCombine, CShader::k_TEXTURE_01);
    m_pMesh->Get_VB()->Enable();
    glDrawElements(GL_TRIANGLES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IB()->Get_Data());
    m_pMesh->Get_VB()->Disable();
    m_pShaderPostSimple->Disable();
}

void CScreenSpacePostMgr::Render_PostBloomExtract(void)
{
    if(m_pMesh->Get_VB() != NULL)
    {
        m_pMesh->Get_VB()->Set_ShaderRef(m_pShaderPostBloomExtract->Get_ProgramHandle());
    }
    m_pShaderPostBloomExtract->Enable();
    m_pShaderPostBloomExtract->SetTexture(m_hTexturePostSimple, CShader::k_TEXTURE_01);
    m_pMesh->Get_VB()->Enable();
    glDrawElements(GL_TRIANGLES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IB()->Get_Data());
    m_pMesh->Get_VB()->Disable();
    m_pShaderPostBloomExtract->Disable();
}

void CScreenSpacePostMgr::Render_PostBloomCombine(void)
{
    if(m_pMesh->Get_VB() != NULL)
    {
        m_pMesh->Get_VB()->Set_ShaderRef(m_pShaderPostBloomCombine->Get_ProgramHandle());
    }
    m_pShaderPostBloomCombine->Enable();
    m_pShaderPostBloomCombine->SetTexture(m_hTexturePostBlur, CShader::k_TEXTURE_01);
    m_pShaderPostBloomCombine->SetTexture(m_hTexturePostSimple, CShader::k_TEXTURE_02);
    m_pMesh->Get_VB()->Enable();
    glDrawElements(GL_TRIANGLES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IB()->Get_Data());
    m_pMesh->Get_VB()->Disable();
    m_pShaderPostBloomCombine->Disable();
}

void CScreenSpacePostMgr::Render_PostBlur(void)
{
    if(m_pMesh->Get_VB() != NULL)
    {
        m_pMesh->Get_VB()->Set_ShaderRef(m_pShaderPostBlur->Get_ProgramHandle());
    }
    m_pShaderPostBlur->Enable();
    m_pShaderPostBlur->SetTexture(m_hTexturePostBloomExtract, CShader::k_TEXTURE_01);
    m_pMesh->Get_VB()->Enable();
    glDrawElements(GL_TRIANGLES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IB()->Get_Data());
    m_pMesh->Get_VB()->Disable();
    m_pShaderPostBlur->Disable();
}




