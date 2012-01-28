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
#include "CTileSetterMgr.h"
#include "CEditMgr.h"

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
    
    m_pHeihtmapSource = NULL;
    m_pTilesetData = NULL;
    
    CTileSetterMgr::Instance();
}

CLandscape::~CLandscape()
{
    
}

void CLandscape::Load(IResource::SResource _tResource)
{
    m_pMesh = new CMesh();
    CMesh::SSource* pSource = new CMesh::SSource();
    pSource->m_iNumVertexes = m_iHeight * m_iWidth * k_TILE_NUM_VERTEXES;
    pSource->m_iNumIndexes = m_iHeight * m_iWidth * k_TILE_NUM_INDEXES;
    
    pSource->m_pIB = new CIndexBuffer(pSource->m_iNumIndexes);
    unsigned short* pIBData =  pSource->m_pIB->Get_Data();
   
    pSource->m_pVB = new CVertexBuffer(pSource->m_iNumVertexes, sizeof(CVertexBuffer::SVertexVTN), CVertexBuffer::E_VERTEX_BUFFER_MODE_VTN);   
    CVertexBuffer::SVertexVTN* pVBData = static_cast<CVertexBuffer::SVertexVTN*>(pSource->m_pVB->Get_Data());
    
    unsigned int iIBIndex = 0;
    unsigned int iVBIndex = 0; 
    int iOffset = 0;
    
    m_pHeihtmapSource = CEditMgr::Instance()->LoadHeightmapData("", m_iWidth, m_iHeight);
    m_pTilesetSource = CEditMgr::Instance()->LoadTilesetData("", m_iWidth, m_iWidth);
    m_pTilesetData = CEditMgr::Instance()->Get_TilesetData("", m_iWidth, m_iHeight, m_pTilesetSource);
    
    for(int i = 0; i < m_iWidth; ++i)
    {
        for(int j = 0; j < m_iHeight; ++j)
        {
            float fHeight = -0.5f;
            if((i - 1) >= 0 && (j - 1) >= 0)
            {
                fHeight = m_pHeihtmapSource[i - 1][j - 1];
            }
            pVBData[iVBIndex].m_vPosition = CVector3d(-k_TILE_SIZE / 2.0f + i, fHeight, -k_TILE_SIZE / 2.0f + j);
            
            fHeight = -0.5f;
            if((i - 1) >= 0)
            {
                fHeight = m_pHeihtmapSource[i - 1][j];
            }
            pVBData[iVBIndex + 1].m_vPosition = CVector3d(-k_TILE_SIZE / 2.0f + i, fHeight,  k_TILE_SIZE / 2.0f + j);
            
            fHeight = m_pHeihtmapSource[i][j];
            pVBData[iVBIndex + 2].m_vPosition = CVector3d( k_TILE_SIZE / 2.0f + i, fHeight, k_TILE_SIZE / 2.0f + j);
            
            fHeight = -0.5f;
            if((j - 1) >= 0)
            {
                fHeight = m_pHeihtmapSource[i][j - 1];
            }
            pVBData[iVBIndex + 3].m_vPosition = CVector3d( k_TILE_SIZE / 2.0f + i, fHeight, -k_TILE_SIZE / 2.0f + j);
            
            pVBData[iVBIndex    ].m_vTexCoord = m_pTilesetData[i + j * m_iHeight].m_vTexCoord[2];
            pVBData[iVBIndex + 1].m_vTexCoord = m_pTilesetData[i + j * m_iHeight].m_vTexCoord[3];
            pVBData[iVBIndex + 2].m_vTexCoord = m_pTilesetData[i + j * m_iHeight].m_vTexCoord[0];
            pVBData[iVBIndex + 3].m_vTexCoord = m_pTilesetData[i + j * m_iHeight].m_vTexCoord[1];
            
            CLandscape::STile* pTile = new CLandscape::STile();
            pTile->m_vPosition = CVector3d(i, m_pHeihtmapSource[i][j], j);
            
            CVector3d vMaxBound = CVector3d( CBoundingBox::k_MAX_VALUE, CBoundingBox::k_MAX_VALUE, CBoundingBox::k_MAX_VALUE );
            CVector3d vMinBound = CVector3d( CBoundingBox::k_MIN_VALUE, CBoundingBox::k_MIN_VALUE, CBoundingBox::k_MIN_VALUE );
            
            for( unsigned int k = 0; k < k_TILE_NUM_VERTEXES; ++k )
            {
                if(pVBData[iVBIndex + k].m_vPosition.x > vMaxBound.x)
                {
                    vMaxBound.x = pVBData[iVBIndex + k].m_vPosition.x;
                }
                
                if(pVBData[iVBIndex + k].m_vPosition.y > vMaxBound.y)
                {
                    vMaxBound.y = pVBData[iVBIndex + k].m_vPosition.y;
                }
                
                if(pVBData[iVBIndex + k].m_vPosition.z > vMaxBound.z)
                {
                    vMaxBound.z = pVBData[iVBIndex + k].m_vPosition.z;
                }
                
                if(pVBData[iVBIndex + k].m_vPosition.x < vMinBound.x)
                {
                   vMinBound.x = pVBData[iVBIndex + k].m_vPosition.x;
                }
                
                if(pVBData[iVBIndex + k].m_vPosition.y < vMinBound.y)
                {
                    vMinBound.y = pVBData[iVBIndex + k].m_vPosition.y;
                }
                
                if(pVBData[iVBIndex + k].m_vPosition.z < vMinBound.z)
                {
                    vMinBound.z = pVBData[iVBIndex + k].m_vPosition.z;
                }
            }
            
            pTile->m_pBoundingBox = new CBoundingBox(vMaxBound,vMinBound);  
            pTile->m_pBoundingBox->Set_Batching(true);
            
            pTile->m_pCollider = new CColliderQuad(pVBData[iVBIndex].m_vPosition, pVBData[iVBIndex + 1].m_vPosition, pVBData[iVBIndex + 2].m_vPosition, pVBData[iVBIndex + 3].m_vPosition);
            pTile->m_pCollider->Set_Batching(true);
            
            CCollisionMgr::Instance()->Create_Collider(pTile->m_pCollider); 
            
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
    
    CEditMgr::Instance()->CalculateNormals(pSource->m_pVB, pSource->m_pIB, CVertexBuffer::E_VERTEX_BUFFER_MODE_VTN);
       
    m_pMesh->Set_Source(pSource);
    m_bIsBatching = _tResource.m_bIsBatching;
}

void CLandscape::EditTilesetData(int _iX, int _iY, CTileSetterMgr::E_TILE_LEVEL _eLevel)
{
    CEditMgr::Instance()->EditTilesetData("", _iX, _iY, m_iWidth, m_iHeight, _eLevel, m_pMesh->Get_VB(), m_pTilesetData, m_pTilesetSource);
}

void CLandscape::EditHeightmapData(int _iX, int _iY, CLandscape::E_HEIGHT_LEVEL _eLevel)
{
    
}

void CLandscape::OnMouseTouchEvent(void)
{
}

void CLandscape::Update()
{
    INode::Update();
    unsigned int iHexColliderID = CCollisionMgr::Instance()->Get_HexColliderID();
    if(iHexColliderID != 0)
    {
        std::map<unsigned int, CLandscape::STile*>::iterator pIterator = m_lContainer.find(iHexColliderID);
        if(pIterator != m_lContainer.end())
        {
            CVector3d vTouch3DPoint = (*pIterator).second->m_vPosition;
            CCollisionMgr::Instance()->Set_Touch3DPoint(vTouch3DPoint);
        }
    }

}

void CLandscape::Render()
{      
    if(m_bIsBatching)
    {
        
    }
    else
    {
        glCullFace(GL_FRONT);
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
        
        m_pMesh->Get_VB()->Enable(m_pShader->Get_ProgramHandle());
        glDrawElements(GL_TRIANGLES, m_pMesh->Get_NumIndexes(), GL_UNSIGNED_SHORT, (void*) m_pMesh->Get_IB()->Get_Data());
        m_pMesh->Get_VB()->Disable(m_pShader->Get_ProgramHandle());
        m_pShader->Disable();
    }
    
    if(m_pBoundingBox != NULL)
    {
        m_pBoundingBox->Render();
    }
    
    std::map<unsigned int,CLandscape::STile*>::iterator pBIterator = m_lContainer.begin();
    std::map<unsigned int,CLandscape::STile*>::iterator pEIterator = m_lContainer.end();
    
    while (pBIterator != pEIterator)
    {
        CBoundingBox* pBoundingBox = (*pBIterator).second->m_pBoundingBox;
        //pBoundingBox->Render(); 
        ++pBIterator;
    }
}




