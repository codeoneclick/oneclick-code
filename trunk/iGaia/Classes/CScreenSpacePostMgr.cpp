//
//  CScreenSpacePostMgr.cpp
//  iGaia
//
//  Created by sergey.sergeev on 3/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CScreenSpacePostMgr.h"
#include "CWindow.h"
#include "CSceneMgr.h"
#include "CResourceMgr.h"

int CScreenSpacePostMgr::k_REFLECTION_TEXTURE_SIZE = 256;
int CScreenSpacePostMgr::k_REFRACTION_TEXTURE_SIZE = 256;

CScreenSpacePostMgr::CScreenSpacePostMgr(void)
{
    
    m_pOffScreenSize[E_OFFSCREEN_MODE_SIMPLE] = glm::vec2(CWindow::Get_OffScreenWidth(), CWindow::Get_OffScreenHeight());
    m_pOffScreenSize[E_OFFSCREEN_MODE_BLOOM_EXTRACT] = glm::vec2(CWindow::Get_OffScreenWidth(), CWindow::Get_OffScreenHeight());
    m_pOffScreenSize[E_OFFSCREEN_MODE_BLUR] = glm::vec2(CWindow::Get_OffScreenWidth(), CWindow::Get_OffScreenHeight());
    m_pOffScreenSize[E_OFFSCREEN_MODE_BLOOM_COMBINE] = glm::vec2(CWindow::Get_OffScreenWidth(), CWindow::Get_OffScreenHeight());
    m_pOffScreenSize[E_OFFSCREEN_MODE_REFLECTION] = glm::vec2(k_REFLECTION_TEXTURE_SIZE, k_REFLECTION_TEXTURE_SIZE);
    
    glGenTextures(k_OFFSCREEN_FBO_COUNT, m_hOffScreenTextures);
    glGenFramebuffers(k_OFFSCREEN_FBO_COUNT, m_hOffScreenFBOs);
    glGenRenderbuffers(k_OFFSCREEN_FBO_COUNT, m_hOffScreenDepthBuffers);
    
    for(unsigned int i = 0; i < k_OFFSCREEN_FBO_COUNT; ++i)
    {
        glBindTexture(GL_TEXTURE_2D, m_hOffScreenTextures[i]);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_pOffScreenSize[i].x, m_pOffScreenSize[i].y, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, 0);
        
        glBindFramebuffer(GL_FRAMEBUFFER, m_hOffScreenFBOs[i]);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_hOffScreenTextures[i],0);
		glClear(GL_COLOR_BUFFER_BIT);
		glBindRenderbuffer(GL_RENDERBUFFER, m_hOffScreenDepthBuffers[i]);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, m_pOffScreenSize[i].x, m_pOffScreenSize[i].y);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_hOffScreenDepthBuffers[i]);
        
		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			std::cout<<"[CScreenSpacePostMgr::CScreenSpacePostMgr] Offscreen Framebuffer FAILURE with INDEX: " <<i<<"\n";
		}
    }
    
    /*glGenTextures(k_OFFSCREEN_FBO_COUNT, m_hOffScreenTextures);
    glBindTexture(GL_TEXTURE_2D, m_hOffScreenTextures[E_OFFSCREEN_MODE_SIMPLE]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, CWindow::Get_OffScreenWidth(), CWindow::Get_OffScreenHeight(), 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, 0);
    
    glBindTexture(GL_TEXTURE_2D, m_hOffScreenTextures[E_OFFSCREEN_MODE_BLOOM_EXTRACT]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, CWindow::Get_OffScreenWidth(), CWindow::Get_OffScreenHeight(), 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, 0);
    
    glBindTexture(GL_TEXTURE_2D, m_hOffScreenTextures[E_OFFSCREEN_MODE_BLUR]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, CWindow::Get_OffScreenWidth(), CWindow::Get_OffScreenHeight(), 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, 0);
    
    glBindTexture(GL_TEXTURE_2D, m_hOffScreenTextures[E_OFFSCREEN_MODE_BLOOM_COMBINE]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, CWindow::Get_OffScreenWidth(), CWindow::Get_OffScreenHeight(), 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, 0);
    
    glBindTexture(GL_TEXTURE_2D, m_hOffScreenTextures[E_OFFSCREEN_MODE_REFLECTION]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, k_REFLECTION_TEXTURE_SIZE, k_REFLECTION_TEXTURE_SIZE, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, 0);
    
    */
    
    /*glGenTextures(1, &m_hTexturePostBloomExtract);
    glBindTexture(GL_TEXTURE_2D, m_hTexturePostBloomExtract);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, CWindow::Get_OffScreenWidth(), CWindow::Get_OffScreenHeight(), 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, 0);
    
    glGenTextures(1, &m_hTexturePostBloomCombine);
    glBindTexture(GL_TEXTURE_2D, m_hTexturePostBloomCombine);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, CWindow::Get_OffScreenWidth(), CWindow::Get_OffScreenHeight(), 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, 0);
    
    glGenTextures(1, &m_hTexturePostBlur);
    glBindTexture(GL_TEXTURE_2D, m_hTexturePostBlur);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, CWindow::Get_OffScreenWidth(), CWindow::Get_OffScreenHeight(), 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, 0);
    
    glGenTextures(1, &m_hTextureReflection);
    glBindTexture(GL_TEXTURE_2D, m_hTextureReflection);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, CWindow::Get_OffScreenWidth(), CWindow::Get_OffScreenHeight(), 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, 0);
    
    glGenTextures(1, &m_hTextureRefraction);
    glBindTexture(GL_TEXTURE_2D, m_hTextureReflection);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, k_REFRACTION_TEXTURE_SIZE, k_REFRACTION_TEXTURE_SIZE, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, 0);
    */
    /*glGenFramebuffers(1, &m_hReflectionFrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_hReflectionFrameBuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_hTextureReflection, 0);
    
    GLuint uStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if(uStatus != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout<<"[CScreenSpacePostMgr::CScreenSpacePostMgr] Reflection Framebuffer FAILURE \n";
    }*/
    
    /*glGenFramebuffers(1, &m_hOffScreenFrameBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_hOffScreenFrameBuffer);
    
    glGenRenderbuffers(1, &m_hDepthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_hDepthBuffer);
    
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, CWindow::Get_OffScreenWidth(), CWindow::Get_OffScreenHeight());
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_hDepthBuffer);
    
    GLuint uStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if(uStatus != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout<<"[CScreenSpacePostMgr::CScreenSpacePostMgr] Offscreen Framebuffer FAILURE \n";
    }*/
    
    glGenFramebuffers(1, &m_hScreenFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, m_hScreenFBO);
    
    glGenRenderbuffers(1, &m_hScreenRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_hScreenRenderBuffer);
    
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_hScreenRenderBuffer);
    
    //uStatus = glCheckFramebufferStatus(GL_FRAMEBUFFER);
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout<<"[CScreenSpacePostMgr::CScreenSpacePostMgr] Screen Framebuffer FAILURE \n";
    }
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    
    CMesh::SSource* pSource = new CMesh::SSource();
    pSource->m_iNumVertexes = 4;
    pSource->m_iNumIndexes  = 6;
    
    pSource->m_pVB = new CVertexBuffer(pSource->m_iNumVertexes);
    
    glm::vec3* pPositionData = pSource->m_pVB->CreateOrReUse_PositionData();
    glm::vec2* pTexCoordData = pSource->m_pVB->CreateOrReUse_TexCoordData();
    
    unsigned i = 0;
    pPositionData[i] = glm::vec3(-1.0f,-1.0f,0.0f);
    pTexCoordData[i] = glm::vec2(0.0f,0.0f);
    i++;
    pPositionData[i] = glm::vec3(-1.0f,1.0f,0.0f);
    pTexCoordData[i] = glm::vec2(0.0f,1.0f);
    i++;
    pPositionData[i] = glm::vec3(1.0f,-1.0f,0.0f);
    pTexCoordData[i] = glm::vec2(1.0f,0.0f);
    i++;
    pPositionData[i] = glm::vec3(1.0f,1.0f,0.0f);
    pTexCoordData[i] = glm::vec2(1.0f,1.0f);
    i++;

    pSource->m_pIB = new CIndexBuffer(pSource->m_iNumIndexes);
    unsigned short* pIBData = pSource->m_pIB->Get_Data();
    
    i = 0;
    pIBData[i++] = 0;
    pIBData[i++] = 1;
    pIBData[i++] = 2;
    
    pIBData[i++] = 3; 
    pIBData[i++] = 2; 
    pIBData[i++] = 1;
    
    m_pMesh = new CMesh();
    m_pMesh->Set_Source(pSource);
    
    m_pMesh->Get_VB()->CommitToRAM();
    m_pMesh->Get_VB()->CommitFromRAMToVRAM();
    m_pMesh->Get_IB()->CommitFromRAMToVRAM();
    
    m_pShaderPostSimple = CShaderComposite::Instance()->Get_Shader(IResource::E_SHADER_TEXTURE);
    m_pShaderPostBloomExtract = CShaderComposite::Instance()->Get_Shader(IResource::E_SHADER_BLOOM_EXTRACT);
    m_pShaderPostBloomCombine = CShaderComposite::Instance()->Get_Shader(IResource::E_SHADER_BLOOM_COMBINE);
    m_pShaderPostBlur = CShaderComposite::Instance()->Get_Shader(IResource::E_SHADER_BLUR);
}

CScreenSpacePostMgr::~CScreenSpacePostMgr(void)
{                               
    
}

/*void CScreenSpacePostMgr::BindRenderBufferAsBuffer(void)
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_hScreenFrameBuffer);
    glViewport(0, 0, CWindow::Get_ScreenWidth(), CWindow::Get_ScreenHeight());
}

void CScreenSpacePostMgr::DiscardRenderBufferAsTexture(void)
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_hOffScreenFrameBuffer);
    const GLenum tDiscards[]  = { GL_COLOR_ATTACHMENT0, GL_DEPTH_ATTACHMENT };
    glDiscardFramebufferEXT(GL_FRAMEBUFFER, 2, tDiscards);
}

void CScreenSpacePostMgr::BindRenderBufferAsTexture(CScreenSpacePostMgr::E_POST_TEXTURE _ePostTexture)
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_hOffScreenFrameBuffer);
    glViewport(0, 0, CWindow::Get_OffScreenWidth(), CWindow::Get_OffScreenHeight());
    
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
        case E_POST_TEXTURE_REFLECTION:
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_hTextureReflection, 0);
            break;
        default:
            break;
    }
}*/

/*void CScreenSpacePostMgr::Render_Reflection(void)
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_hOffScreenFrameBuffer);
    glViewport(0, 0, k_REFLECTION_TEXTURE_SIZE, k_REFLECTION_TEXTURE_SIZE);
}

void CScreenSpacePostMgr::Discard_Reflection(void)
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_hReflectionFrameBuffer);
    const GLenum tDiscards[]  = { GL_COLOR_ATTACHMENT0 };
    glDiscardFramebufferEXT(GL_FRAMEBUFFER, 1, tDiscards);
}*/

void CScreenSpacePostMgr::EnableOffScreenMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE _eMode)
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_hOffScreenFBOs[_eMode]);
    glViewport(0, 0, m_pOffScreenSize[_eMode].x, m_pOffScreenSize[_eMode].y);
}

void CScreenSpacePostMgr::DisableOffScreenMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE _eMode)
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_hOffScreenFBOs[_eMode]);
    const GLenum tDiscards[]  = { GL_COLOR_ATTACHMENT0, GL_DEPTH_ATTACHMENT };
    glDiscardFramebufferEXT(GL_FRAMEBUFFER, 2, tDiscards);
}

void CScreenSpacePostMgr::EnableScreenMode(void)
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_hScreenFBO);
    glViewport(0, 0, CWindow::Get_ScreenWidth(), CWindow::Get_ScreenHeight());
}

void CScreenSpacePostMgr::DisableScreenMode(void)
{
    
}


void CScreenSpacePostMgr::Render_PostSimple(void)
{
    if(m_pMesh->Get_VB() != NULL)
    {
        m_pMesh->Get_VB()->Set_ShaderRef(m_pShaderPostSimple->Get_ProgramHandle());
    }
    m_pShaderPostSimple->Enable();
    m_pShaderPostSimple->SetTexture(m_hOffScreenTextures[E_OFFSCREEN_MODE_BLOOM_COMBINE], CShader::k_TEXTURE_01);
    m_pMesh->Get_VB()->Enable();
    m_pMesh->Get_IB()->Enable();
    glDrawElements(GL_TRIANGLES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IB()->Get_DataFromVRAM());
    m_pMesh->Get_IB()->Disable();
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
    m_pShaderPostBloomExtract->SetTexture(m_hOffScreenTextures[E_OFFSCREEN_MODE_SIMPLE], CShader::k_TEXTURE_01);
    m_pMesh->Get_VB()->Enable();
    m_pMesh->Get_IB()->Enable();
    glDrawElements(GL_TRIANGLES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IB()->Get_DataFromVRAM());
    m_pMesh->Get_IB()->Disable();
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
    m_pShaderPostBloomCombine->SetTexture(m_hOffScreenTextures[E_OFFSCREEN_MODE_BLUR], CShader::k_TEXTURE_01);
    m_pShaderPostBloomCombine->SetTexture(m_hOffScreenTextures[E_OFFSCREEN_MODE_SIMPLE], CShader::k_TEXTURE_02);
    m_pMesh->Get_VB()->Enable();
    m_pMesh->Get_IB()->Enable();
    glDrawElements(GL_TRIANGLES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IB()->Get_DataFromVRAM());
    m_pMesh->Get_IB()->Disable();
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
    m_pShaderPostBlur->SetTexture(m_hOffScreenTextures[E_OFFSCREEN_MODE_BLOOM_EXTRACT], CShader::k_TEXTURE_01);
    m_pMesh->Get_VB()->Enable();
    m_pMesh->Get_IB()->Enable();
    glDrawElements(GL_TRIANGLES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IB()->Get_DataFromVRAM());
    m_pMesh->Get_IB()->Disable();
    m_pMesh->Get_VB()->Disable();
    m_pShaderPostBlur->Disable();
}




