//
//  CNavigationMeshMgr.cpp
//  iGaia
//
//  Created by sergey.sergeev on 2/22/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CNavigationMeshMgr.h"

CNavigationMeshMgr::CNavigationMeshMgr(void)
{
    memset(&m_cfg, 0x0, sizeof(m_cfg));
    m_cfg.cs = 0.1f;
    m_cfg.ch = 0.1f;
    m_cfg.walkableSlopeAngle = 45;
    m_cfg.walkableHeight = (int)ceilf(1.0f / m_cfg.ch);
    m_cfg.walkableClimb = (int)floorf(1.0f / m_cfg.ch);
    m_cfg.walkableRadius = (int)ceilf(0.5f / m_cfg.cs);
    m_cfg.maxEdgeLen = (int)(40 / m_cfg.cs);
    m_cfg.maxSimplificationError = 1.3;
    m_cfg.minRegionArea = (int)rcSqr(8.0f);      
    m_cfg.mergeRegionArea = (int)rcSqr(20.0f);
    m_cfg.maxVertsPerPoly = (int)6.0f;
    m_cfg.detailSampleDist = m_cfg.cs * 6;
    m_cfg.detailSampleMaxError = m_cfg.ch * 1.0f;
}

CNavigationMeshMgr::~CNavigationMeshMgr(void)
{
    
}

std::vector<glm::vec2> CNavigationMeshMgr::FindPath(glm::vec3 _vStartPoint, glm::vec3 _vEndPoint)
{
    std::vector<glm::vec2> lPath;
    lPath.clear();
    dtStatus tStatus;
    float pBound[3] = {2.0f, 4.0f, 2.0f};
    dtPolyRef pStartPolygon;
    float pStartPolygonNeighbors[3] ;
    dtPolyRef pEndPolygon;
    float pEndPolygonNeighbors[3] ;
    dtPolyRef pPolygonPath[MAX_PATHPOLY];
    int iPathPolygonsCount = 0 ;
    float pStraightPath[MAX_PATHVERT * 3];
    int iPathVertexesNum = 0 ;
    
    dtQueryFilter tFilter;
    tFilter.setIncludeFlags(SAMPLE_POLYFLAGS_ALL ^ SAMPLE_POLYFLAGS_DISABLED);
    tFilter.setExcludeFlags(0) ;
    tFilter.setAreaCost(SAMPLE_POLYAREA_GROUND, 1.0f) ;
    

    tStatus = m_pNavigationMeshQuery->findNearestPoly(&_vStartPoint[0], pBound, &tFilter, &pStartPolygon, pStartPolygonNeighbors) ;
    if((tStatus & DT_FAILURE) || (tStatus & DT_STATUS_DETAIL_MASK)) 
    {
        std::cout<<"[CNavigationMeshWrapper::FindPath] couldn't find a start polygon.\n";
        return lPath;
    }
    
    tStatus = m_pNavigationMeshQuery->findNearestPoly(&_vEndPoint[0], pBound, &tFilter, &pEndPolygon, pEndPolygonNeighbors) ;
    if((tStatus & DT_FAILURE) || (tStatus & DT_STATUS_DETAIL_MASK)) 
    {
        std::cout<<"[CNavigationMeshWrapper::FindPath] couldn't find a end polygon.\n";
        return lPath;
    }
    
    tStatus = m_pNavigationMeshQuery->initSlicedFindPath(pStartPolygon, pEndPolygon, &_vStartPoint[0], &_vEndPoint[0], &tFilter);
    if((tStatus & DT_FAILURE) || (tStatus & DT_STATUS_DETAIL_MASK)) 
    {
        std::cout<<"[CNavigationMeshWrapper::FindPath] couldn't init a sliced path.\n";
        return lPath;
    }
    
    tStatus = m_pNavigationMeshQuery->updateSlicedFindPath(1,0);
    while(dtStatusInProgress(tStatus))
    {
        tStatus = m_pNavigationMeshQuery->updateSlicedFindPath(1,0);
    }
    
    if (dtStatusSucceed(tStatus))
    {
        m_pNavigationMeshQuery->finalizeSlicedFindPath(pPolygonPath, &iPathPolygonsCount, MAX_PATHPOLY);
        if (iPathPolygonsCount)
        {
            float pEndPosition[3];
            rcVcopy(pEndPosition, &_vEndPoint[0]);

            if (pPolygonPath[iPathPolygonsCount - 1] != pEndPolygon)
            {
				m_pNavigationMeshQuery->closestPointOnPoly(pPolygonPath[iPathPolygonsCount - 1], &_vEndPoint[0], pEndPosition);
            }
            
            tStatus = m_pNavigationMeshQuery->findStraightPath(&_vStartPoint[0], &_vEndPoint[0], pPolygonPath, iPathPolygonsCount, pStraightPath, NULL, NULL, &iPathVertexesNum, MAX_PATHPOLY);
            if((tStatus & DT_FAILURE) || (tStatus & DT_STATUS_DETAIL_MASK))
            {
                std::cout<<"[CNavigationMeshWrapper::FindPath] couldn't create a path.\n";
                return lPath; 
            }
        }
    }
    
    /*tStatus = m_pNavigationMeshQuery->findPath(pStartPolygon, pEndPolygon, pStartPolygonNeighbors, pEndPolygonNeighbors, &tFilter, pPolygonPath, &iPathPolygonsCount, MAX_PATHPOLY) ;
    if((tStatus & DT_FAILURE) || (tStatus & DT_STATUS_DETAIL_MASK)) 
    {
        std::cout<<"[CNavigationMeshWrapper::FindPath] couldn't create a path.\n";
        return lPath; 
    }
    if(iPathPolygonsCount == 0) 
    {
        std::cout<<"[CNavigationMeshWrapper::FindPath] couldn't find a path.\n";
        return lPath; 
    }
    
    tStatus = m_pNavigationMeshQuery->findStraightPath(pStartPolygonNeighbors, pEndPolygonNeighbors, pPolygonPath, iPathPolygonsCount, pStraightPath, NULL, NULL, &iPathVertexesNum, MAX_PATHVERT);
    if((tStatus & DT_FAILURE) || (tStatus & DT_STATUS_DETAIL_MASK))
    {
        std::cout<<"[CNavigationMeshWrapper::FindPath] couldn't create a path.\n";
        return lPath; 
    }*/
    if(iPathVertexesNum == 0) 
    {
        std::cout<<"[CNavigationMeshWrapper::FindPath] couldn't find a path.\n";
        return lPath;
    }
    
    int iIndex=0 ;
    for(unsigned int i = 0 ; i < iPathVertexesNum; ++i)
    {
        glm::vec2 vPosition;
        vPosition.x = pStraightPath[iIndex++];
        iIndex++;
        vPosition.y = pStraightPath[iIndex++];
        std::cout<<"[CNavigationMeshWrapper::FindPath] path point : "<<vPosition.x<<","<<vPosition.y<<"\n";
        lPath.push_back(vPosition);
    }
    std::reverse(lPath.begin(), lPath.end());
    return lPath;
}

void CNavigationMeshMgr::Create_VisualMesh(void)
{
    const int iMaxVertexesPerPolygon = m_pPolygonMesh->nvp; 
    const float fCellWidth = m_pPolygonMesh->cs;
    const float fCellHeight = m_pPolygonMesh->ch;
    const float* pBoundingBoxOffset = m_pPolygonMesh->bmin;
    
    std::vector<glm::vec3> lVertexesData;
    lVertexesData.clear();
    std::vector<unsigned short> lIndexesData;
    lIndexesData.clear();
    
    unsigned int iIndex = 0;
    if(m_pPolygonMesh->npolys > 0)
    {
        for (unsigned int i = 0; i < m_pPolygonMesh->npolys; ++i) 
        {
            if (m_pPolygonMesh->areas[i] == SAMPLE_POLYAREA_GROUND)
            {
                const unsigned short* pPolygonIndex = &m_pPolygonMesh->polys[i * iMaxVertexesPerPolygon * 2];
                
                unsigned short pVertexesIndex[3];
                for (int j = 2; j < iMaxVertexesPerPolygon; ++j)
                {
                    if (pPolygonIndex[j] == RC_MESH_NULL_IDX) 
                    {
                        break;
                    }
                    pVertexesIndex[0] = pPolygonIndex[0  ];
                    pVertexesIndex[1] = pPolygonIndex[j-1];
                    pVertexesIndex[2] = pPolygonIndex[j  ];
                    for (int k = 0; k < 3; ++k) 
                    {
                        const unsigned short* pVertexes = &m_pPolygonMesh->verts[pVertexesIndex[k] * 3];
                        const float fX = pBoundingBoxOffset[0] + pVertexes[0] * fCellWidth;
                        const float fY = pBoundingBoxOffset[1] + (pVertexes[1]+1) * fCellHeight;
                        const float fZ = pBoundingBoxOffset[2] + pVertexes[2] * fCellWidth;
                        
                        glm::vec3 vPosition = glm::vec3(fX, fY, fZ);
                        lVertexesData.push_back(vPosition);
                    }
                    lIndexesData.push_back(iIndex + 0);
                    lIndexesData.push_back(iIndex + 1);
                    lIndexesData.push_back(iIndex + 2);
                    iIndex += 3 ;
                }
            }
        }
        
        CMesh::SSource* pSource = new CMesh::SSource();
        pSource->m_iNumVertexes = lVertexesData.size();
        pSource->m_iNumIndexes  = lIndexesData.size();
        
        pSource->m_pIB = new CIndexBuffer(pSource->m_iNumIndexes);
        unsigned short* pIndexesData = pSource->m_pIB->Get_Data();
        for(unsigned int i = 0; i < pSource->m_iNumIndexes; ++i)
        {
            pIndexesData[i] = lIndexesData[i];
        }
        
        pSource->m_pVB = new CVertexBuffer(pSource->m_iNumVertexes);
       
        glm::vec3* pPositionData = pSource->m_pVB->CreateOrReUse_PositionData();
        glm::u8vec4* pColorData = pSource->m_pVB->CreateOrReUse_ColorData();
        for(unsigned int i = 0; i < pSource->m_iNumVertexes; i++)
        {
            pPositionData[i] = lVertexesData[i];
            pColorData[i] = glm::u8vec4(0, 255, 0, 255);
        }
        
        lVertexesData.clear();
        lIndexesData.clear();
        
        
        m_pVisualMesh = new CMesh();
        m_pVisualMesh->Set_Source(pSource);
        m_pVisualMesh->Set_Name("navigation_mesh");
        m_pVisualMesh->Get_VB()->CommitToRAM();
        m_pVisualMesh->Get_VB()->CommitFromRAMToVRAM();
    }
    else
    {
        std::cout<<"[CNavigationMeshWrapper::Create_VisualMesh] Error : Polygon count = 0\n";
    }
}

void CNavigationMeshMgr::Set_NavigationModel(INode *_pNode)
{
    size_t iNumVertexes = _pNode->Get_Mesh()->Get_NumVertexes();
    glm::vec3* pPositionData = _pNode->Get_Mesh()->Get_VB()->CreateOrReUse_PositionData();
    float* pNavigationMeshVertexesData = new float[iNumVertexes * 3];
    
    float pBoundingBoxMin[3];
    float pBoundingBoxMax[3];
    
    pBoundingBoxMin[0] =  k_BOUND_BOX_VALUE;
    pBoundingBoxMin[1] =  k_BOUND_BOX_VALUE;
    pBoundingBoxMin[2] =  k_BOUND_BOX_VALUE;
    pBoundingBoxMax[0] = -k_BOUND_BOX_VALUE;
    pBoundingBoxMax[1] = -k_BOUND_BOX_VALUE;
    pBoundingBoxMax[2] = -k_BOUND_BOX_VALUE;
    
    for(size_t index = 0; index < iNumVertexes; index++)
    {
        pNavigationMeshVertexesData[index*3    ] = pPositionData[index].x;
        pNavigationMeshVertexesData[index*3 + 1] = pPositionData[index].y;
        pNavigationMeshVertexesData[index*3 + 2] = pPositionData[index].z;
        
        if(pPositionData[index].x < pBoundingBoxMin[0]) pBoundingBoxMin[0] = pPositionData[index].x;
        if(pPositionData[index].y < pBoundingBoxMin[1]) pBoundingBoxMin[1] = pPositionData[index].y;
        if(pPositionData[index].z < pBoundingBoxMin[2]) pBoundingBoxMin[2] = pPositionData[index].z;
        
        if(pPositionData[index].x > pBoundingBoxMax[0]) pBoundingBoxMax[0] = pPositionData[index].x;
        if(pPositionData[index].y > pBoundingBoxMax[1]) pBoundingBoxMax[1] = pPositionData[index].y;
        if(pPositionData[index].z > pBoundingBoxMax[2]) pBoundingBoxMax[2] = pPositionData[index].z;
    }
    
    size_t iNumIndexes = _pNode->Get_Mesh()->Get_NumIndexes();
    size_t iNumTriangles = iNumIndexes / 3;
    unsigned short* pNodeIndexesData = _pNode->Get_Mesh()->Get_IB()->Get_Data();
    int* pNavigationMeshIndexesData = new int[iNumIndexes] ;
    
    for(size_t index =0; index < iNumIndexes; index+= 3)
    {
        pNavigationMeshIndexesData[index    ] = pNodeIndexesData[index    ];
        pNavigationMeshIndexesData[index + 1] = pNodeIndexesData[index + 1];
        pNavigationMeshIndexesData[index + 2] = pNodeIndexesData[index + 2];
    }
    
    m_pNavigationMeshContext = new rcContext(false) ;

    rcVcopy(m_cfg.bmin, pBoundingBoxMin);
    rcVcopy(m_cfg.bmax, pBoundingBoxMax);
    rcCalcGridSize(m_cfg.bmin, m_cfg.bmax, m_cfg.cs, &m_cfg.width, &m_cfg.height);
    
    m_pHeightField = rcAllocHeightfield();
    if (!m_pHeightField)
    {
        std::cout<<"[CNavigationMeshWrapper::SetupNavigationMesh] Out of memory 'solid'.\n";
        return;
    }
    if (!rcCreateHeightfield(m_pNavigationMeshContext, *m_pHeightField, m_cfg.width, m_cfg.height, m_cfg.bmin, m_cfg.bmax, m_cfg.cs, m_cfg.ch))
    {
        std::cout<<"[CNavigationMeshWrapper::SetupNavigationMesh] Could not create solid heightfield.\n";
        return;
    }
    

    m_pTriangleAreas = new unsigned char[iNumTriangles];
    if (!m_pTriangleAreas)
    {
        std::cout<<"[CNavigationMeshWrapper::SetupNavigationMesh] Out of memory 'm_triareas'.\n"; 
        return;
    }
    
    memset(m_pTriangleAreas, 0x0, iNumTriangles * sizeof(unsigned char));
    rcMarkWalkableTriangles(m_pNavigationMeshContext, m_cfg.walkableSlopeAngle, pNavigationMeshVertexesData, iNumVertexes, pNavigationMeshIndexesData, iNumTriangles, m_pTriangleAreas);
    rcRasterizeTriangles(m_pNavigationMeshContext, pNavigationMeshVertexesData, iNumVertexes, pNavigationMeshIndexesData, m_pTriangleAreas, iNumTriangles, *m_pHeightField, m_cfg.walkableClimb);
    
    rcFilterLowHangingWalkableObstacles(m_pNavigationMeshContext, m_cfg.walkableClimb, *m_pHeightField);
	rcFilterLedgeSpans(m_pNavigationMeshContext, m_cfg.walkableHeight, m_cfg.walkableClimb, *m_pHeightField);
	rcFilterWalkableLowHeightSpans(m_pNavigationMeshContext, m_cfg.walkableHeight, *m_pHeightField);
    
	m_pCompactHeightField = rcAllocCompactHeightfield();
	if (!m_pCompactHeightField)
	{
        std::cout<<"[CNavigationMeshWrapper::SetupNavigationMesh] Out of memory 'chf'.\n"; 
		return;
	}
	if (!rcBuildCompactHeightfield(m_pNavigationMeshContext, m_cfg.walkableHeight, m_cfg.walkableClimb, *m_pHeightField, *m_pCompactHeightField))
	{
        std::cout<<"[CNavigationMeshWrapper::SetupNavigationMesh] Could not build compact data.\n"; 
		return;
	}
    
	if (!rcErodeWalkableArea(m_pNavigationMeshContext, m_cfg.walkableRadius, *m_pCompactHeightField))
	{
        std::cout<<"[CNavigationMeshWrapper::SetupNavigationMesh] Could not erode.\n"; 
		return;
	}
    
    if (!rcBuildDistanceField(m_pNavigationMeshContext, *m_pCompactHeightField))
    {
        std::cout<<"[CNavigationMeshWrapper::SetupNavigationMesh] Could not build distance field.\n";
        return;
    }
        
    if (!rcBuildRegions(m_pNavigationMeshContext, *m_pCompactHeightField, 0, m_cfg.minRegionArea, m_cfg.mergeRegionArea))
    {
        std::cout<<"[CNavigationMeshWrapper::SetupNavigationMesh] Could not build regions.\n";
        return;
    }
    
    m_pContour = rcAllocContourSet();
	if (!m_pContour)
	{
        std::cout<<"[CNavigationMeshWrapper::SetupNavigationMesh] Out of memory 'cset'.\n";
		return;
	}
	if (!rcBuildContours(m_pNavigationMeshContext, *m_pCompactHeightField, m_cfg.maxSimplificationError, m_cfg.maxEdgeLen, *m_pContour))
	{
        std::cout<<"[CNavigationMeshWrapper::SetupNavigationMesh] Could not create contours.\n";
		return;
	}
	
	m_pPolygonMesh = rcAllocPolyMesh();
	if (!m_pPolygonMesh)
	{
        std::cout<<"[CNavigationMeshWrapper::SetupNavigationMesh] Out of memory 'pmesh'.\n";
		return;
	}
	if (!rcBuildPolyMesh(m_pNavigationMeshContext, *m_pContour, m_cfg.maxVertsPerPoly, *m_pPolygonMesh))
	{
        std::cout<<"[CNavigationMeshWrapper::SetupNavigationMesh] Could not triangulate contours.\n";
		return;
	}
	
	m_pPolygonMeshDetail = rcAllocPolyMeshDetail();
	if (!m_pPolygonMeshDetail)
	{
        std::cout<<"[CNavigationMeshWrapper::SetupNavigationMesh] Out of memory 'pmdtl'.\n";
		return;
	}
    
	if (!rcBuildPolyMeshDetail(m_pNavigationMeshContext, *m_pPolygonMesh, *m_pCompactHeightField, m_cfg.detailSampleDist, m_cfg.detailSampleMaxError, *m_pPolygonMeshDetail))
	{
        std::cout<<"[CNavigationMeshWrapper::SetupNavigationMesh] Could not build detail mesh.\n";
		return;
	}
    
    if (m_cfg.maxVertsPerPoly <= DT_VERTS_PER_POLYGON)
    {
        unsigned char* pNavigationData = NULL;
        int iNavigationDataSize = 0;
        
        for (int i = 0; i < m_pPolygonMesh->npolys; ++i)
        {
            if (m_pPolygonMesh->areas[i] == RC_WALKABLE_AREA)
            {
                m_pPolygonMesh->areas[i] = SAMPLE_POLYAREA_GROUND;
                m_pPolygonMesh->flags[i] = SAMPLE_POLYFLAGS_WALK;
            }
        }
         
        dtNavMeshCreateParams params;
        memset(&params, 0, sizeof(params));
        params.verts = m_pPolygonMesh->verts;
        params.vertCount = m_pPolygonMesh->nverts;
        params.polys = m_pPolygonMesh->polys;
        params.polyAreas = m_pPolygonMesh->areas;
        params.polyFlags = m_pPolygonMesh->flags;
        params.polyCount = m_pPolygonMesh->npolys;
        params.nvp = m_pPolygonMesh->nvp;
        params.detailMeshes = m_pPolygonMeshDetail->meshes;
        params.detailVerts = m_pPolygonMeshDetail->verts;
        params.detailVertsCount = m_pPolygonMeshDetail->nverts;
        params.detailTris = m_pPolygonMeshDetail->tris;
        params.detailTriCount = m_pPolygonMeshDetail->ntris;
        
        params.walkableHeight = m_cfg.walkableHeight;
        params.walkableRadius = m_cfg.walkableRadius;
        params.walkableClimb = m_cfg.walkableRadius;
        rcVcopy(params.bmin, m_pPolygonMesh->bmin);
        rcVcopy(params.bmax, m_pPolygonMesh->bmax);
        params.cs = m_cfg.cs;
        params.ch = m_cfg.ch;
        
        if (!dtCreateNavMeshData(&params, &pNavigationData, &iNavigationDataSize))
        {
            return;
        }
        
        m_pNavigationMesh = dtAllocNavMesh();
        if (!m_pNavigationMesh)
        {
            dtFree(pNavigationData);
            return;
        }
        
        dtStatus tStatus;
        tStatus = m_pNavigationMesh->init(pNavigationData, iNavigationDataSize, DT_TILE_FREE_DATA);
        if (dtStatusFailed(tStatus))
        {
            dtFree(pNavigationData);
            return;
        }
        
        m_pNavigationMeshQuery = dtAllocNavMeshQuery();
        tStatus = m_pNavigationMeshQuery->init(m_pNavigationMesh, 2048);
        
        if (dtStatusFailed(tStatus))
        {
            return;
        }
    }
    
    if(m_pTriangleAreas != NULL)
    {
        delete[] m_pTriangleAreas;
    }
    rcFreeHeightField(m_pHeightField);
    m_pHeightField = NULL;
    rcFreeCompactHeightfield(m_pCompactHeightField);
    m_pCompactHeightField = NULL;
    rcFreeContourSet(m_pContour);
    m_pContour = NULL;
    rcFreePolyMeshDetail(m_pPolygonMeshDetail);
    m_pPolygonMeshDetail = 0;
    if(m_pNavigationMeshContext != NULL) 
    {
        delete m_pNavigationMeshContext;
    }
    
    std::cout<<"[CNavigationMeshWrapper::SetupNavigationMesh] Created Vertexes : "<<m_pPolygonMesh->nverts<<" Created Polygons "<<m_pPolygonMesh->npolys<<"\n"; 
    Create_VisualMesh();
}



