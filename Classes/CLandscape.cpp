//
//  CLandscape.cpp
//  gEngine
//
//  Created by sergey.sergeev on 1/16/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CLandscape.h"
#include "CSceneMgr.h"
#include "CRenderMgr.h"
#include "CCollisionMgr.h"
#include "CColliderQuad.h"

const int CLandscape::k_TILE_NUM_INDEXES = 6;
const int CLandscape::k_TILE_NUM_VERTEXES = 4;
const float CLandscape::k_TILE_SIZE = 1.0f;

CLandscape::CLandscape()
{
    m_iWidth = 32;
    m_iHeight = 32;
    
    m_pSingleTileIB = new unsigned short[k_TILE_NUM_INDEXES];
    m_pSingleTileIB[0] = 0;
    m_pSingleTileIB[1] = 1;
    m_pSingleTileIB[2] = 2;
    m_pSingleTileIB[3] = 2;
    m_pSingleTileIB[4] = 3;
    m_pSingleTileIB[5] = 0;
    
    m_pTileSetter = NULL;
    m_pHeightMapSetter = NULL;
    m_pNavigationMesh = NULL;
    m_pVisualNavigationMeshRef = NULL;
    m_pVisualNavigationMeshShader = NULL;
}

CLandscape::~CLandscape()
{
    
}
/*
void CLandscape::LoadWithTileSet(void)
{
     m_pMesh = new CMesh();
     CMesh::SSource* pSource = new CMesh::SSource();
     pSource->m_iNumVertexes = m_iHeight * m_iWidth * k_TILE_NUM_VERTEXES;
     pSource->m_iNumIndexes = m_iHeight * m_iWidth * k_TILE_NUM_INDEXES;
     
     pSource->m_pIB = new CIndexBuffer(pSource->m_iNumIndexes);
     unsigned short* pIBData =  pSource->m_pIB->Get_Data();
     
     pSource->m_pVB = new CVertexBuffer(pSource->m_iNumVertexes);
     glm::vec3* pPositionData = pSource->m_pVB->CreateOrReUse_PositionData();
     glm::vec2* pTexCoordData = pSource->m_pVB->CreateOrReUse_TexCoordData();
    
     unsigned int iIBIndex = 0;
     unsigned int iVBIndex = 0; 
     int iOffset = 0;
     
     m_pHeightMapSetter = new CHeightMapSetter();
     m_pHeightMapSetter->Load_SourceData("", m_iWidth, m_iHeight);
     float* m_pHeihtmapData = m_pHeightMapSetter->Get_HeightMapData();
     
     m_pTileSetter = new CTileSetter();
     m_pTileSetter->Load_SourceData("",m_iWidth, m_iHeight);
     m_pTileSetter->Create_TexCoordData();
     
     CTileSetter::STileTexCoords* pTilesetData = m_pTileSetter->Get_TexCoordData();
     
     for(int i = 0; i < m_iWidth; ++i)
     {
         for(int j = 0; j < m_iHeight; ++j)
         {
             float fHeight = -0.5f;
             float fNormalHeight = 0.0f;
             if((i - 1) >= 0 && (j - 1) >= 0)
             {
                fHeight = m_pHeihtmapData[(i - 1)+ (j - 1) * m_iHeight];
             }
             fNormalHeight += fHeight;
             pPositionData[iVBIndex] = glm::vec3(-k_TILE_SIZE / 2.0f + i, fHeight, -k_TILE_SIZE / 2.0f + j);
     
             fHeight = -0.5f;
             if((i - 1) >= 0)
             {
                 fHeight = m_pHeihtmapData[(i - 1) + j * m_iHeight];
             }  
             fNormalHeight += fHeight;
             pPositionData[iVBIndex + 1] = glm::vec3(-k_TILE_SIZE / 2.0f + i, fHeight,  k_TILE_SIZE / 2.0f + j);
     
             fHeight = m_pHeihtmapData[i + j * m_iHeight];
             fNormalHeight += fHeight;
             pPositionData[iVBIndex + 2] = glm::vec3( k_TILE_SIZE / 2.0f + i, fHeight, k_TILE_SIZE / 2.0f + j);
     
             fHeight = -0.5f;
             if((j - 1) >= 0)
             {
                 fHeight = m_pHeihtmapData[i + (j - 1) * m_iHeight];
             }
             fNormalHeight += fHeight;
             pPositionData[iVBIndex + 3] = glm::vec3( k_TILE_SIZE / 2.0f + i, fHeight, -k_TILE_SIZE / 2.0f + j);
     
             pTexCoordData[iVBIndex    ] = pTilesetData[i + j * m_iHeight].m_vTexCoord[2];
             pTexCoordData[iVBIndex + 1] = pTilesetData[i + j * m_iHeight].m_vTexCoord[3];
             pTexCoordData[iVBIndex + 2] = pTilesetData[i + j * m_iHeight].m_vTexCoord[0];
             pTexCoordData[iVBIndex + 3] = pTilesetData[i + j * m_iHeight].m_vTexCoord[1];
     
             CLandscape::STile* pTile = new CLandscape::STile();
             fNormalHeight /= 4.0f;
             pTile->m_vPosition = CVector3d(i, fNormalHeight, j);
     
             CVector3d vMaxBound = CVector3d( CBoundingBox::k_MAX_VALUE, CBoundingBox::k_MAX_VALUE, CBoundingBox::k_MAX_VALUE );
             CVector3d vMinBound = CVector3d( CBoundingBox::k_MIN_VALUE, CBoundingBox::k_MIN_VALUE, CBoundingBox::k_MIN_VALUE );
     
             for( unsigned int k = 0; k < k_TILE_NUM_VERTEXES; ++k )
             {
                 if(pPositionData[iVBIndex + k].x > vMaxBound.x)
                 {
                     vMaxBound.x = pPositionData[iVBIndex + k].x;
                 }
     
                 if(pPositionData[iVBIndex + k].y > vMaxBound.y)
                 {
                     vMaxBound.y = pPositionData[iVBIndex + k].y;
                 }
     
                 if(pPositionData[iVBIndex + k].z > vMaxBound.z)
                 {
                     vMaxBound.z = pPositionData[iVBIndex + k].z;
                 }
     
                 if(pPositionData[iVBIndex + k].x < vMinBound.x)
                 {
                     vMinBound.x = pPositionData[iVBIndex + k].x;
                 }
     
                 if(pPositionData[iVBIndex + k].y < vMinBound.y)
                 {
                     vMinBound.y = pPositionData[iVBIndex + k].y;
                 }
     
                 if(pPositionData[iVBIndex + k].z < vMinBound.z)
                 {
                     vMinBound.z = pPositionData[iVBIndex + k].z;
                 }
             }
     
             pTile->m_pBoundingBox = new CBoundingBox(vMaxBound,vMinBound);  
             pTile->m_pBoundingBox->Set_Batching(true);
     
             pTile->m_pCollider = new CColliderQuad(pPositionData[iVBIndex], pPositionData[iVBIndex + 1], pPositionData[iVBIndex + 2], pPositionData[iVBIndex + 3]);
             pTile->m_pCollider->Set_Batching(true);
     
             CSceneMgr::Instance()->Get_CollisionMgr()->Create_Collider(pTile->m_pCollider); 
     
             for( unsigned int k = 0; k < k_TILE_NUM_INDEXES; ++k )
             {
                 pIBData[iIBIndex] = m_pSingleTileIB[k] + iOffset;
                 ++iIBIndex;
             }
             unsigned int iHexColliderID = pTile->m_pCollider->Get_ColliderID().m_iHex;
             m_lContainer[iHexColliderID] = pTile;
             iOffset += k_TILE_NUM_VERTEXES;
             iVBIndex += 4;
         }
     }
     
     m_pHeightMapSetter->Calculate_Normals(pSource->m_pVB, pSource->m_pIB);
     m_pMesh->Set_Source(pSource);
}*/

void CLandscape::Load(IResource::SResource _tResource)
{
    m_pHeightMapSetter = new CHeightMapSetter();
    m_pMesh = m_pHeightMapSetter->Load_SourceData(_tResource.m_sName, m_iWidth, m_iHeight);
    
    m_pNavigationMesh = new CNavigationMesh();
    m_pNavigationMesh->Set_NavigationModel(this);
    m_pVisualNavigationMeshRef = m_pNavigationMesh->Get_VisualMesh();
    m_pVisualNavigationMeshShader = CShaderComposite::Instance()->Get_Shader(IResource::E_SHADER_COLOR);
    m_pVisualNavigationMeshRef->Get_VB()->Set_ShaderRef(m_pVisualNavigationMeshShader->Get_ProgramHandle());
    CSceneMgr::Instance()->Set_NavigationMeshRef(m_pNavigationMesh);
    CSceneMgr::Instance()->Set_HeightMapSetterRef(m_pHeightMapSetter);
    
    m_bIsBatching = _tResource.m_bIsBatching;
    
    m_pMesh->Get_VB()->CommitFromRAMToVRAM();
    m_pMesh->Get_IB()->CommitFromRAMToVRAM();
}

void CLandscape::OnTouchEvent(void)
{
    CCollisionMgr::SRay3d tTouchRay = CSceneMgr::Instance()->Get_CollisionMgr()->Get_TouchRay();
    glm::vec3 vCollisionPoint;
     
    if(!CSceneMgr::Instance()->Get_CollisionMgr()->Get_CollisionPoint(m_pMesh->Get_VB(), m_pMesh->Get_IB(), tTouchRay, &vCollisionPoint))
    {
        return;
    }
    else
    {
        std::cout<<"[CLandscape::OnTouchEvent] Colission Point = "<<vCollisionPoint.x<<","<<vCollisionPoint.y<<","<<vCollisionPoint.z<<"\n";
    }
    
    CSceneMgr::Instance()->Get_CollisionMgr()->Set_Touch3DPoint(vCollisionPoint);
    for(size_t index = 0; index< m_lDelegates.size(); index++)
    {
        m_lDelegates[index]->OnTouchEvent(m_pDelegateTarget);
    }
}

void CLandscape::Update()
{
    INode::Update();
}

void CLandscape::Render()
{      
    if(m_bIsBatching)
    {
        
    }
    else
    {
        glCullFace(GL_BACK);
        m_pShader->Enable();
        m_pShader->SetMatrix(m_mWorld, CShader::k_MATRIX_WORLD);
        
        ICamera* pCamera = CSceneMgr::Instance()->Get_Camera();
        
        m_pShader->SetMatrix(pCamera->Get_Projection(), CShader::k_MATRIX_PROJECTION);
        m_pShader->SetMatrix(pCamera->Get_View(), CShader::k_MATRIX_VIEW);
        m_pShader->SetVector(pCamera->Get_Position(), CShader::k_VECTOR_VIEW);
        
        if(m_pLight != NULL)
        {
            m_pShader->SetVector(m_pLight->Get_Position(), CShader::k_VECTOR_LIGHT);
        }

        if( m_pTextures[0] != NULL )
        {
            m_pShader->SetTexture(m_pTextures[0]->Get_Handle(), CShader::k_TEXTURE_01);
        }
        if( m_pTextures[1] != NULL )
        {
            m_pShader->SetTexture(m_pTextures[1]->Get_Handle(), CShader::k_TEXTURE_02);
        }
        if( m_pTextures[2] != NULL )
        {
            m_pShader->SetTexture(m_pTextures[2]->Get_Handle(), CShader::k_TEXTURE_03);
        }
        if( m_pTextures[3] != NULL )
        {
            m_pShader->SetTexture(m_pTextures[3]->Get_Handle(), CShader::k_TEXTURE_04);
        }
        if( m_pTextures[4] != NULL )
        {
            m_pShader->SetTexture(m_pTextures[4]->Get_Handle(), CShader::k_TEXTURE_05);
        }
        if( m_pTextures[5] != NULL )
        {
            m_pShader->SetTexture(m_pTextures[5]->Get_Handle(), CShader::k_TEXTURE_06);
        }
        
        m_pShader->SetTexture(m_pHeightMapSetter->Get_SplattingTexture(), CShader::k_TEXTURE_07);
        
        m_pMesh->Get_VB()->Enable();
        m_pMesh->Get_IB()->Enable();
        glDrawElements(GL_TRIANGLES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IB()->Get_DataFromVRAM());
        m_pMesh->Get_IB()->Disable();
        m_pMesh->Get_VB()->Disable();
        m_pShader->Disable();
        
        glCullFace(GL_FRONT);
    }
    
    /*if(m_pVisualNavigationMeshRef != NULL)
    {
        m_pVisualNavigationMeshShader->Enable();
        m_pVisualNavigationMeshShader->SetMatrix(m_mWorld, CShader::k_MATRIX_WORLD);
        ICamera* pCamera = CSceneMgr::Instance()->Get_Camera();
        m_pVisualNavigationMeshShader->SetMatrix(pCamera->Get_Projection(), CShader::k_MATRIX_PROJECTION);
        m_pVisualNavigationMeshShader->SetMatrix(pCamera->Get_View(), CShader::k_MATRIX_VIEW);
        m_pVisualNavigationMeshShader->SetVector(pCamera->Get_Position(), CShader::k_VECTOR_VIEW);
        
        m_pVisualNavigationMeshRef->Get_VB()->Enable();
        glDrawElements(GL_TRIANGLES, m_pVisualNavigationMeshRef->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*)m_pVisualNavigationMeshRef->Get_IB()->Get_Data());
        m_pVisualNavigationMeshRef->Get_VB()->Disable();
        m_pVisualNavigationMeshShader->Disable();
    }*/
    
    if(m_pBoundingBox != NULL)
    {
        m_pBoundingBox->Render();
    }
    
    std::map<unsigned int,CLandscape::STile*>::iterator pBIterator = m_lContainer.begin();
    std::map<unsigned int,CLandscape::STile*>::iterator pEIterator = m_lContainer.end();
    
    while (pBIterator != pEIterator)
    {
        CBoundingBox* pBoundingBox = (*pBIterator).second->m_pBoundingBox;
        pBoundingBox->Render(); 
        ++pBIterator;
    }
}




