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
    m_pOffScreenSize[E_OFFSCREEN_MODE_REFRACTION] = glm::vec2(k_REFRACTION_TEXTURE_SIZE, k_REFRACTION_TEXTURE_SIZE);
    m_pOffScreenSize[E_OFFSCREEN_MODE_EDGE_DETECT] = glm::vec2(CWindow::Get_OffScreenWidth(), CWindow::Get_OffScreenHeight());
    m_pOffScreenSize[E_OFFSCREEN_MODE_SCREEN_NORMAL_MAP] = glm::vec2(CWindow::Get_OffScreenWidth(), CWindow::Get_OffScreenHeight());
    m_pOffScreenSize[E_OFFSCREEN_MODE_SHADOW_MAP] = glm::vec2(CWindow::Get_OffScreenWidth(), CWindow::Get_OffScreenHeight());
    
    glGenTextures(E_OFFSCREEN_MODE_MAX, m_hOffScreenTextures);
    glGenFramebuffers(E_OFFSCREEN_MODE_MAX, m_hOffScreenFBOs);
    glGenRenderbuffers(E_OFFSCREEN_MODE_MAX, m_hOffScreenDepthBuffers);
    
    for(unsigned int i = 0; i < E_OFFSCREEN_MODE_MAX; ++i)
    {
        glBindTexture(GL_TEXTURE_2D, m_hOffScreenTextures[i]);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        if(i == E_OFFSCREEN_MODE_REFLECTION || i == E_OFFSCREEN_MODE_REFRACTION)
        {
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        }
        else 
        {
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        }
        
        if(i == E_OFFSCREEN_MODE_REFLECTION || i == E_OFFSCREEN_MODE_SIMPLE)
        {
            m_pOffScreenClearColor[i] = glm::vec4(1.0,1.0,1.0,1.0);
            
        }
        else
        {
            m_pOffScreenClearColor[i] = glm::vec4(0.0,0.0,0.0,0.0);;
        }
      
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_pOffScreenSize[i].x, m_pOffScreenSize[i].y, 0, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, 0);
        
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
    
    glGenFramebuffers(1, &m_hScreenFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, m_hScreenFBO);
    
    glGenRenderbuffers(1, &m_hScreenRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_hScreenRenderBuffer);
    
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, m_hScreenRenderBuffer);
    
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
    
    pSource->m_pVertexBuffer = new CVertexBuffer(pSource->m_iNumVertexes);
    
    glm::vec3* pPositionData = pSource->m_pVertexBuffer->CreateOrReUse_PositionData();
    glm::vec2* pTexCoordData = pSource->m_pVertexBuffer->CreateOrReUse_TexCoordData();
    
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

    pSource->m_pIndexBuffer = new CIndexBuffer(pSource->m_iNumIndexes);
    unsigned short* pIBData = pSource->m_pIndexBuffer->Get_Data();
    
    i = 0;
    pIBData[i++] = 0;
    pIBData[i++] = 1;
    pIBData[i++] = 2;
    
    pIBData[i++] = 3; 
    pIBData[i++] = 2; 
    pIBData[i++] = 1;
    
    m_pMesh = new CMesh();
    m_pMesh->Set_Source(pSource);
    
    m_pMesh->Get_VertexBufferRef()->CommitToRAM();
    m_pMesh->Get_VertexBufferRef()->CommitFromRAMToVRAM();
    m_pMesh->Get_IndexBufferRef()->CommitFromRAMToVRAM();
    
    m_pShaderPostSimple = CShaderComposite::Instance()->Get_Shader(IResource::E_SHADER_TEXTURE);
    m_pShaderPostBloomExtract = CShaderComposite::Instance()->Get_Shader(IResource::E_SHADER_BLOOM_EXTRACT);
    m_pShaderPostBloomCombine = CShaderComposite::Instance()->Get_Shader(IResource::E_SHADER_BLOOM_COMBINE);
    m_pShaderPostBlur = CShaderComposite::Instance()->Get_Shader(IResource::E_SHADER_BLUR);
    m_pShaderPostEdgeDetect = CShaderComposite::Instance()->Get_Shader(IResource::E_SHADER_EDGE_DETECT);
}

CScreenSpacePostMgr::~CScreenSpacePostMgr(void)
{                               
    
}

void CScreenSpacePostMgr::EnableOffScreenMode(CScreenSpacePostMgr::E_OFFSCREEN_MODE _eMode)
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_hOffScreenFBOs[_eMode]);
    glViewport(0, 0, m_pOffScreenSize[_eMode].x, m_pOffScreenSize[_eMode].y);
    glClearColor( m_pOffScreenClearColor[_eMode].r, m_pOffScreenClearColor[_eMode].g, m_pOffScreenClearColor[_eMode].b, m_pOffScreenClearColor[_eMode].a );
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
    if(m_pMesh->Get_VertexBufferRef() != NULL)
    {
        m_pMesh->Get_VertexBufferRef()->Set_ShaderRef(m_pShaderPostSimple->Get_ProgramHandle());
    }
    m_pShaderPostSimple->Enable();
    m_pShaderPostSimple->SetTexture(m_hOffScreenTextures[E_OFFSCREEN_MODE_EDGE_DETECT], CShader::k_TEXTURE_01);
    m_pMesh->Get_VertexBufferRef()->Enable();
    m_pMesh->Get_IndexBufferRef()->Enable();
    glDrawElements(GL_TRIANGLES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IndexBufferRef()->Get_DataFromVRAM());
    m_pMesh->Get_IndexBufferRef()->Disable();
    m_pMesh->Get_VertexBufferRef()->Disable();
    m_pShaderPostSimple->Disable();
}

void CScreenSpacePostMgr::Render_PostBloomExtract(void)
{
    if(m_pMesh->Get_VertexBufferRef() != NULL)
    {
        m_pMesh->Get_VertexBufferRef()->Set_ShaderRef(m_pShaderPostBloomExtract->Get_ProgramHandle());
    }

    m_pShaderPostBloomExtract->Enable();
    m_pShaderPostBloomExtract->SetTexture(m_hOffScreenTextures[E_OFFSCREEN_MODE_EDGE_DETECT], CShader::k_TEXTURE_01);
    m_pMesh->Get_VertexBufferRef()->Enable();
    m_pMesh->Get_IndexBufferRef()->Enable();
    glDrawElements(GL_TRIANGLES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IndexBufferRef()->Get_DataFromVRAM());
    m_pMesh->Get_IndexBufferRef()->Disable();
    m_pMesh->Get_VertexBufferRef()->Disable();
    m_pShaderPostBloomExtract->Disable();
}

void CScreenSpacePostMgr::Render_PostBloomCombine(void)
{
    if(m_pMesh->Get_VertexBufferRef() != NULL)
    {
        m_pMesh->Get_VertexBufferRef()->Set_ShaderRef(m_pShaderPostBloomCombine->Get_ProgramHandle());
    }
    m_pShaderPostBloomCombine->Enable();
    m_pShaderPostBloomCombine->SetTexture(m_hOffScreenTextures[E_OFFSCREEN_MODE_BLUR], CShader::k_TEXTURE_01);
    m_pShaderPostBloomCombine->SetTexture(m_hOffScreenTextures[E_OFFSCREEN_MODE_EDGE_DETECT], CShader::k_TEXTURE_02);
    m_pMesh->Get_VertexBufferRef()->Enable();
    m_pMesh->Get_IndexBufferRef()->Enable();
    glDrawElements(GL_TRIANGLES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IndexBufferRef()->Get_DataFromVRAM());
    m_pMesh->Get_IndexBufferRef()->Disable();
    m_pMesh->Get_VertexBufferRef()->Disable();
    m_pShaderPostBloomCombine->Disable();
}

void CScreenSpacePostMgr::Render_PostBlur(void)
{
    if(m_pMesh->Get_VertexBufferRef() != NULL)
    {
        m_pMesh->Get_VertexBufferRef()->Set_ShaderRef(m_pShaderPostBlur->Get_ProgramHandle());
    }
    m_pShaderPostBlur->Enable();
    m_pShaderPostBlur->SetTexture(m_hOffScreenTextures[E_OFFSCREEN_MODE_BLOOM_EXTRACT], CShader::k_TEXTURE_01);
    m_pMesh->Get_VertexBufferRef()->Enable();
    m_pMesh->Get_IndexBufferRef()->Enable();
    glDrawElements(GL_TRIANGLES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IndexBufferRef()->Get_DataFromVRAM());
    m_pMesh->Get_IndexBufferRef()->Disable();
    m_pMesh->Get_VertexBufferRef()->Disable();
    m_pShaderPostBlur->Disable();
}


void CScreenSpacePostMgr::Render_PostEdgeDetect(void)
{
    if(m_pMesh->Get_VertexBufferRef() != NULL)
    {
        m_pMesh->Get_VertexBufferRef()->Set_ShaderRef(m_pShaderPostEdgeDetect->Get_ProgramHandle());
    }
    m_pShaderPostEdgeDetect->Enable();
    m_pShaderPostEdgeDetect->SetTexture(m_hOffScreenTextures[E_OFFSCREEN_MODE_SIMPLE], CShader::k_TEXTURE_01);
    m_pShaderPostEdgeDetect->SetTexture(m_hOffScreenTextures[E_OFFSCREEN_MODE_SCREEN_NORMAL_MAP], CShader::k_TEXTURE_02);
    m_pMesh->Get_VertexBufferRef()->Enable();
    m_pMesh->Get_IndexBufferRef()->Enable();
    glDrawElements(GL_TRIANGLES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IndexBufferRef()->Get_DataFromVRAM());
    m_pMesh->Get_IndexBufferRef()->Disable();
    m_pMesh->Get_VertexBufferRef()->Disable();
    m_pShaderPostEdgeDetect->Disable();
}



