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
#include "CVertexBufferPositionTexcoord.h"
#include "CMaterial.h"

int CScreenSpacePostMgr::k_REFLECTION_TEXTURE_SIZE = 128;
int CScreenSpacePostMgr::k_REFRACTION_TEXTURE_SIZE = 128;

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
    glGenTextures(E_OFFSCREEN_MODE_MAX, m_hOffScreenDepthTextures);
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
        
        if(i == E_OFFSCREEN_MODE_REFLECTION || i == E_OFFSCREEN_MODE_SIMPLE )
        {
            m_pOffScreenClearColor[i] = glm::vec4(1.0,1.0,1.0,1.0);
            
        }
        else if(i == E_OFFSCREEN_MODE_SCREEN_NORMAL_MAP)
        {
            m_pOffScreenClearColor[i] = glm::vec4(1.0,0.0,0.0,1.0);
        }
        else
        {
            m_pOffScreenClearColor[i] = glm::vec4(0.0,0.0,0.0,0.0);;
        }
      
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_pOffScreenSize[i].x, m_pOffScreenSize[i].y, 0, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, NULL);
        
        glBindTexture(GL_TEXTURE_2D, m_hOffScreenDepthTextures[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE_EXT, GL_COMPARE_R_TO_TEXTURE_ARB );
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC_EXT, GL_LEQUAL );
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, m_pOffScreenSize[i].x, m_pOffScreenSize[i].y, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
        
        glBindFramebuffer(GL_FRAMEBUFFER, m_hOffScreenFBOs[i]);
		
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_hOffScreenTextures[i],0);
		//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,  GL_TEXTURE_2D, m_hOffScreenDepthTextures[i], 0);
        
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
    
    CMaterial::InitStates();
    
    CMesh::SSourceData* pSourceData = new CMesh::SSourceData();
    pSourceData->m_iNumVertexes = 4;
    pSourceData->m_iNumIndexes  = 6;
    
    pSourceData->m_pVertexBuffer = new CVertexBufferPositionTexcoord(pSourceData->m_iNumVertexes, GL_STATIC_DRAW);
    CVertexBufferPositionTexcoord::SVertex* pVertexBufferData = static_cast<CVertexBufferPositionTexcoord::SVertex*>(pSourceData->m_pVertexBuffer->Lock());
    //glm::vec3* pPositionData = pSourceData->m_pVertexBuffer->GetOrCreate_PositionSourceData();
    //glm::vec2* pTexCoordData = pSourceData->m_pVertexBuffer->GetOrCreate_TexcoordSourceData();
    
    unsigned i = 0;
    pVertexBufferData[i].m_vPosition = glm::vec3(-1.0f,-1.0f,0.0f);
    pVertexBufferData[i].m_vTexcoord = glm::vec2(0.0f,0.0f);
    i++;
    pVertexBufferData[i].m_vPosition = glm::vec3(-1.0f,1.0f,0.0f);
    pVertexBufferData[i].m_vTexcoord = glm::vec2(0.0f,1.0f);
    i++;
    pVertexBufferData[i].m_vPosition = glm::vec3(1.0f,-1.0f,0.0f);
    pVertexBufferData[i].m_vTexcoord = glm::vec2(1.0f,0.0f);
    i++;
    pVertexBufferData[i].m_vPosition = glm::vec3(1.0f,1.0f,0.0f);
    pVertexBufferData[i].m_vTexcoord = glm::vec2(1.0f,1.0f);
    i++;

    pSourceData->m_pIndexBuffer = new CIndexBuffer(pSourceData->m_iNumIndexes);
    unsigned short* pIndexBufferData = pSourceData->m_pIndexBuffer->Get_SourceData();
    
    i = 0;
    pIndexBufferData[i++] = 0;
    pIndexBufferData[i++] = 1;
    pIndexBufferData[i++] = 2;
    
    pIndexBufferData[i++] = 3; 
    pIndexBufferData[i++] = 2; 
    pIndexBufferData[i++] = 1;
    
    m_pMesh = new CMesh(IResource::E_CREATION_MODE_CUSTOM);
    m_pMesh->Set_SourceData(pSourceData);
    
    m_pMesh->Get_VertexBufferRef()->Commit();
    m_pMesh->Get_IndexBufferRef()->Commit();
    
    m_pShaderPostSimple = CShaderComposite::Instance()->Get_Shader(IResource::E_SHADER_TEXTURE);
    m_pShaderPostBloomExtract = CShaderComposite::Instance()->Get_Shader(IResource::E_SHADER_BLOOM_EXTRACT);
    m_pShaderPostBloomCombine = CShaderComposite::Instance()->Get_Shader(IResource::E_SHADER_BLOOM_COMBINE);
    m_pShaderPostBlur = CShaderComposite::Instance()->Get_Shader(IResource::E_SHADER_BLUR);
    m_pShaderPostEdgeDetect = CShaderComposite::Instance()->Get_Shader(IResource::E_SHADER_EDGE_DETECT);
    
    m_pMesh->Get_VertexBufferRef()->Add_ShaderRef(CShader::E_RENDER_MODE_SCREEN_SPACE_SIMPLE, m_pShaderPostSimple);
    m_pMesh->Get_VertexBufferRef()->Add_ShaderRef(CShader::E_RENDER_MODE_SCREEN_SPACE_BLOOM_EXTRACT, m_pShaderPostBloomExtract);
    m_pMesh->Get_VertexBufferRef()->Add_ShaderRef(CShader::E_RENDER_MODE_SCREEN_SPACE_BLOOM_COMBINE, m_pShaderPostBloomCombine);
    m_pMesh->Get_VertexBufferRef()->Add_ShaderRef(CShader::E_RENDER_MODE_SCREEN_SPACE_BLUR, m_pShaderPostBlur);
    m_pMesh->Get_VertexBufferRef()->Add_ShaderRef(CShader::E_RENDER_MODE_SCREEN_SPACE_EDGE_DETECT, m_pShaderPostEdgeDetect);
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
    //glBindFramebuffer(GL_FRAMEBUFFER, m_hOffScreenFBOs[_eMode]);
    //const GLenum tDiscards[]  = { GL_COLOR_ATTACHMENT0, GL_DEPTH_ATTACHMENT };
    //glDiscardFramebufferEXT(GL_FRAMEBUFFER, 2, tDiscards);
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
    glDisable(GL_DEPTH_TEST);
    m_pShaderPostSimple->Enable();
    m_pShaderPostSimple->Set_Texture(m_hOffScreenTextures[E_OFFSCREEN_MODE_EDGE_DETECT], CShader::E_TEXTURE_SLOT_01);
    m_pMesh->Get_VertexBufferRef()->Enable(CShader::E_RENDER_MODE_SCREEN_SPACE_SIMPLE);
    m_pMesh->Get_IndexBufferRef()->Enable();
    glDrawElements(GL_TRIANGLES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IndexBufferRef()->Get_SourceDataFromVRAM());
    m_pMesh->Get_IndexBufferRef()->Disable();
    m_pMesh->Get_VertexBufferRef()->Disable(CShader::E_RENDER_MODE_SCREEN_SPACE_SIMPLE);
    m_pShaderPostSimple->Disable();
    glEnable(GL_DEPTH_TEST);
}

void CScreenSpacePostMgr::Render_PostBloomExtract(void)
{
    m_pShaderPostBloomExtract->Enable();
    m_pShaderPostBloomExtract->Set_Texture(m_hOffScreenTextures[E_OFFSCREEN_MODE_EDGE_DETECT], CShader::E_TEXTURE_SLOT_01);
    m_pMesh->Get_VertexBufferRef()->Enable(CShader::E_RENDER_MODE_SCREEN_SPACE_BLOOM_EXTRACT);
    m_pMesh->Get_IndexBufferRef()->Enable();
    glDrawElements(GL_TRIANGLES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IndexBufferRef()->Get_SourceDataFromVRAM());
    m_pMesh->Get_IndexBufferRef()->Disable();
    m_pMesh->Get_VertexBufferRef()->Disable(CShader::E_RENDER_MODE_SCREEN_SPACE_BLOOM_EXTRACT);
    m_pShaderPostBloomExtract->Disable();
}

void CScreenSpacePostMgr::Render_PostBloomCombine(void)
{
    m_pShaderPostBloomCombine->Enable();
    m_pShaderPostBloomCombine->Set_Texture(m_hOffScreenTextures[E_OFFSCREEN_MODE_BLUR], CShader::E_TEXTURE_SLOT_01);
    m_pShaderPostBloomCombine->Set_Texture(m_hOffScreenTextures[E_OFFSCREEN_MODE_EDGE_DETECT], CShader::E_TEXTURE_SLOT_02);
    m_pMesh->Get_VertexBufferRef()->Enable(CShader::E_RENDER_MODE_SCREEN_SPACE_BLOOM_COMBINE);
    m_pMesh->Get_IndexBufferRef()->Enable();
    glDrawElements(GL_TRIANGLES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IndexBufferRef()->Get_SourceDataFromVRAM());
    m_pMesh->Get_IndexBufferRef()->Disable();
    m_pMesh->Get_VertexBufferRef()->Disable(CShader::E_RENDER_MODE_SCREEN_SPACE_BLOOM_COMBINE);
    m_pShaderPostBloomCombine->Disable();
}

void CScreenSpacePostMgr::Render_PostBlur(void)
{
    m_pShaderPostBlur->Enable();
    m_pShaderPostBlur->Set_Texture(m_hOffScreenTextures[E_OFFSCREEN_MODE_BLOOM_EXTRACT], CShader::E_TEXTURE_SLOT_01);
    m_pMesh->Get_VertexBufferRef()->Enable(CShader::E_RENDER_MODE_SCREEN_SPACE_BLUR);
    m_pMesh->Get_IndexBufferRef()->Enable();
    glDrawElements(GL_TRIANGLES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IndexBufferRef()->Get_SourceDataFromVRAM());
    m_pMesh->Get_IndexBufferRef()->Disable();
    m_pMesh->Get_VertexBufferRef()->Disable(CShader::E_RENDER_MODE_SCREEN_SPACE_BLUR);
    m_pShaderPostBlur->Disable();
}


void CScreenSpacePostMgr::Render_PostEdgeDetect(void)
{
    m_pShaderPostEdgeDetect->Enable();
    m_pShaderPostEdgeDetect->Set_Texture(m_hOffScreenTextures[E_OFFSCREEN_MODE_SIMPLE], CShader::E_TEXTURE_SLOT_01);
    m_pShaderPostEdgeDetect->Set_Texture(m_hOffScreenTextures[E_OFFSCREEN_MODE_SCREEN_NORMAL_MAP], CShader::E_TEXTURE_SLOT_02);
    m_pMesh->Get_VertexBufferRef()->Enable(CShader::E_RENDER_MODE_SCREEN_SPACE_EDGE_DETECT);
    m_pMesh->Get_IndexBufferRef()->Enable();
    glDrawElements(GL_TRIANGLES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IndexBufferRef()->Get_SourceDataFromVRAM());
    m_pMesh->Get_IndexBufferRef()->Disable();
    m_pMesh->Get_VertexBufferRef()->Disable(CShader::E_RENDER_MODE_SCREEN_SPACE_EDGE_DETECT);
    m_pShaderPostEdgeDetect->Disable();
}



