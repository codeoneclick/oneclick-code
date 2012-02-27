//
//  CNavigationMeshWrapper.cpp
//  gEngine
//
//  Created by sergey.sergeev on 2/22/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CNavigationMeshWrapper.h"
#include "CVector.h"

CNavigationMeshWrapper* CNavigationMeshWrapper::m_pInstance = NULL;

CNavigationMeshWrapper::CNavigationMeshWrapper(void)
{
    /*m_cellSize = 1.0 ;//0.3;
    m_cellHeight = 4.0 ;//0.2;
    m_agentMaxSlope = 45;
    m_agentHeight = 64.0;
    m_agentMaxClimb = 16;
    m_agentRadius = 16;
    m_edgeMaxLen = 512;
    m_edgeMaxError = 1.3;
    m_regionMinSize = 50;
    m_regionMergeSize = 20;
    m_vertsPerPoly = 6;
    m_detailSampleDist = 6;
    m_detailSampleMaxError = 1;
    m_keepInterResults = false;*/
    
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

CNavigationMeshWrapper::~CNavigationMeshWrapper(void)
{
    
}

CNavigationMeshWrapper* CNavigationMeshWrapper::Instance(void)
{
    if(m_pInstance == NULL)
    {
        m_pInstance = new CNavigationMeshWrapper();
    }
    return m_pInstance;
}

void CNavigationMeshWrapper::FindPath(CVector3d vStartPos, CVector3d vEndPos)
{
    m_lPath.clear();
    dtStatus status ;
    float pExtents[3]={2.0f, 4.0f, 2.0f} ; // size of box around start/end points to look for l polygons
    dtPolyRef StartPoly ;
    float StartNearest[3] ;
    dtPolyRef EndPoly ;
    float EndNearest[3] ;
    dtPolyRef PolyPath[MAX_PATHPOLY] ;
    int nPathCount=0 ;
    float StraightPath[MAX_PATHVERT*3] ;
    int nVertCount=0 ;
    
    // setup the filter
    dtQueryFilter Filter;
    Filter.setIncludeFlags(SAMPLE_POLYFLAGS_ALL ^ SAMPLE_POLYFLAGS_DISABLED);
    Filter.setExcludeFlags(0) ;
    Filter.setAreaCost(SAMPLE_POLYAREA_GROUND, 1.0f) ;
    
    // find the start polygon
    status=m_navQuery->findNearestPoly(&vStartPos.v[0], pExtents, &Filter, &StartPoly, StartNearest) ;
    if((status&DT_FAILURE) || (status&DT_STATUS_DETAIL_MASK)) 
        return; // couldn't find a polygon
    
    // find the end polygon
    status=m_navQuery->findNearestPoly(&vEndPos.v[0], pExtents, &Filter, &EndPoly, EndNearest) ;
    if((status&DT_FAILURE) || (status&DT_STATUS_DETAIL_MASK)) 
        return; // couldn't find a polygon
    
    status=m_navQuery->findPath(StartPoly, EndPoly, StartNearest, EndNearest, &Filter, PolyPath, &nPathCount, MAX_PATHPOLY) ;
    if((status&DT_FAILURE) || (status&DT_STATUS_DETAIL_MASK)) 
        return ; // couldn't create a path
    if(nPathCount==0) 
        return ; // couldn't find a path
    
    status=m_navQuery->findStraightPath(StartNearest, EndNearest, PolyPath, nPathCount, StraightPath, NULL, NULL, &nVertCount, MAX_PATHVERT) ;
    if((status&DT_FAILURE) || (status&DT_STATUS_DETAIL_MASK))
        return; // couldn't create a path
    if(nVertCount==0) 
        return; // couldn't find a path
    
    // At this point we have our path.  Copy it to the path store
    int nIndex=0 ;
    for(int nVert=0 ; nVert<nVertCount ; nVert++)
    {
        //std::cout<<StraightPath[nIndex++]<<","<<StraightPath[nIndex++]<<","<<StraightPath[nIndex++]<<"\n";
        CVector2d vPosition;// = CVector2d(StraightPath[nIndex++], StraightPath[nIndex++]);
        vPosition.x = StraightPath[nIndex++];
        nIndex++;
        vPosition.y = StraightPath[nIndex++];
        m_lPath.push_back(vPosition);
        std::reverse(m_lPath.begin(), m_lPath.end());
        //m_PathStore[nPathSlot].PosX[nVert]=StraightPath[nIndex++] ;
        //m_PathStore[nPathSlot].PosY[nVert]=StraightPath[nIndex++] ;
        //m_PathStore[nPathSlot].PosZ[nVert]=StraightPath[nIndex++] ;
        
        //sprintf(m_chBug, "Path Vert %i, %f %f %f", nVert, m_PathStore[nPathSlot].PosX[nVert], m_PathStore[nPathSlot].PosY[nVert], m_PathStore[nPathSlot].PosZ[nVert]) ;
        //m_pLog->logMessage(m_chBug);
    }
    //m_PathStore[nPathSlot].MaxVertex=nVertCount ;
    //m_PathStore[nPathSlot].Target=nTarget ;
    
    //return nVertCount ;
}


void CNavigationMeshWrapper::SetupNavigationMesh(INode *_pNode)
{
    size_t iNumVertexes = _pNode->Get_Mesh()->Get_NumVertexes();
    CVertexBuffer::SVertexVTN* pNodeVertexData = static_cast<CVertexBuffer::SVertexVTN*>(_pNode->Get_Mesh()->Get_VB()->Get_Data()); 
    float* pNavMeshVertexData = new float[iNumVertexes * 3];
    
    float pBoundingBoxMin[3];
    float pBoundingBoxMax[3];
    
    pBoundingBoxMin[0] = SPLAT_BANKDISTANCE;
    pBoundingBoxMin[1] = SPLAT_BANKDISTANCE;
    pBoundingBoxMin[2] = SPLAT_BANKDISTANCE;
    pBoundingBoxMax[0] =-SPLAT_BANKDISTANCE;
    pBoundingBoxMax[1] =-SPLAT_BANKDISTANCE;
    pBoundingBoxMax[2] =-SPLAT_BANKDISTANCE;
    
    for(size_t index = 0; index < iNumVertexes; index++)
    {
        pNavMeshVertexData[index*3    ] = pNodeVertexData[index].m_vPosition.x;
        pNavMeshVertexData[index*3 + 1] = pNodeVertexData[index].m_vPosition.y;
        pNavMeshVertexData[index*3 + 2] = pNodeVertexData[index].m_vPosition.z;
        
        if(pNodeVertexData[index].m_vPosition.x < pBoundingBoxMin[0]) pBoundingBoxMin[0] = pNodeVertexData[index].m_vPosition.x;
        if(pNodeVertexData[index].m_vPosition.y < pBoundingBoxMin[1]) pBoundingBoxMin[1] = pNodeVertexData[index].m_vPosition.y;
        if(pNodeVertexData[index].m_vPosition.z < pBoundingBoxMin[2]) pBoundingBoxMin[2] = pNodeVertexData[index].m_vPosition.z;
        
        if(pNodeVertexData[index].m_vPosition.x > pBoundingBoxMax[0]) pBoundingBoxMax[0] = pNodeVertexData[index].m_vPosition.x;
        if(pNodeVertexData[index].m_vPosition.y > pBoundingBoxMax[1]) pBoundingBoxMax[1] = pNodeVertexData[index].m_vPosition.y;
        if(pNodeVertexData[index].m_vPosition.z > pBoundingBoxMax[2]) pBoundingBoxMax[2] = pNodeVertexData[index].m_vPosition.z;
    }
    
    size_t iNumIndexes = _pNode->Get_Mesh()->Get_NumIndexes();
    size_t iNumTriangles = iNumIndexes / 3;
    unsigned short* pNodeIndexData = _pNode->Get_Mesh()->Get_IB()->Get_Data();
    int* pNavMeshIndexData = new int[iNumIndexes] ;
    float* pNavMeshNormalData = new float[iNumIndexes] ;
    
    for(size_t index =0; index < iNumIndexes; index+= 3)
    {
        pNavMeshIndexData[index    ] = pNodeIndexData[index    ];
        pNavMeshIndexData[index + 1] = pNodeIndexData[index + 1];
        pNavMeshIndexData[index + 2] = pNodeIndexData[index + 2];
        
        CVector3d vPoint_01 = pNodeVertexData[pNodeIndexData[index    ]].m_vPosition;
        CVector3d vPoint_02 = pNodeVertexData[pNodeIndexData[index + 1]].m_vPosition;
        CVector3d vPoint_03 = pNodeVertexData[pNodeIndexData[index + 2]].m_vPosition;
        
        CVector3d vEdge_01 = vPoint_02 - vPoint_01;
        CVector3d vEdge_02 = vPoint_03 - vPoint_01;
        
        CVector3d vNormal = Cross(vEdge_01, vEdge_02);
        vNormal.Normalize();
        
        pNavMeshNormalData[index    ] = vNormal.x;
        pNavMeshNormalData[index + 1] = vNormal.y;
        pNavMeshNormalData[index + 2] = vNormal.z;
    }
    
    m_ctx = new rcContext(true) ;
    m_ctx->resetTimers();
    m_ctx->startTimer(RC_TIMER_TOTAL);

    rcVcopy(m_cfg.bmin, pBoundingBoxMin);
    rcVcopy(m_cfg.bmax, pBoundingBoxMax);
    rcCalcGridSize(m_cfg.bmin, m_cfg.bmax, m_cfg.cs, &m_cfg.width, &m_cfg.height);
    
    m_solid = rcAllocHeightfield();
    if (!m_solid)
    {
        m_ctx->log(RC_LOG_ERROR, "buildNavigation: Out of memory 'solid'.");
        std::cout<<"buildNavigation: Out of memory 'solid'.";
        return;
    }
    if (!rcCreateHeightfield(m_ctx, *m_solid, m_cfg.width, m_cfg.height, m_cfg.bmin, m_cfg.bmax, m_cfg.cs, m_cfg.ch))
    {
        m_ctx->log(RC_LOG_ERROR,"buildNavigation: Could not create solid heightfield.");
        std::cout<<"buildNavigation: Could not create solid heightfield.";
        return;
    }
    

    m_triareas = new unsigned char[iNumTriangles];
    if (!m_triareas)
    {
        m_ctx->log(RC_LOG_ERROR, "buildNavigation: Out of memory 'm_triareas' (%d).", iNumTriangles);
        std::cout<<"buildNavigation: Out of memory 'm_triareas'."; 
        return;
    }
    
    memset(m_triareas, 0x0, iNumTriangles * sizeof(unsigned char));
    rcMarkWalkableTriangles(m_ctx, m_cfg.walkableSlopeAngle, pNavMeshVertexData, iNumVertexes, pNavMeshIndexData, iNumTriangles, m_triareas);
    rcRasterizeTriangles(m_ctx, pNavMeshVertexData, iNumVertexes, pNavMeshIndexData, m_triareas, iNumTriangles, *m_solid, m_cfg.walkableClimb);

    std::cout<<"STEP 1 DONE";
    
    rcFilterLowHangingWalkableObstacles(m_ctx, m_cfg.walkableClimb, *m_solid);
	rcFilterLedgeSpans(m_ctx, m_cfg.walkableHeight, m_cfg.walkableClimb, *m_solid);
	rcFilterWalkableLowHeightSpans(m_ctx, m_cfg.walkableHeight, *m_solid);
    
    std::cout<<"STEP 2 DONE";
    
	m_chf = rcAllocCompactHeightfield();
	if (!m_chf)
	{
		m_ctx->log(RC_LOG_ERROR, "buildNavigation: Out of memory 'chf'.");
        std::cout<<"buildNavigation: Out of memory 'chf'."; 
		return;
	}
	if (!rcBuildCompactHeightfield(m_ctx, m_cfg.walkableHeight, m_cfg.walkableClimb, *m_solid, *m_chf))
	{
		m_ctx->log(RC_LOG_ERROR, "buildNavigation: Could not build compact data.");
        std::cout<<"buildNavigation: Could not build compact data."; 
		return;
	}
    
	if (!rcErodeWalkableArea(m_ctx, m_cfg.walkableRadius, *m_chf))
	{
		m_ctx->log(RC_LOG_ERROR, "buildNavigation: Could not erode.");
        std::cout<<"buildNavigation: Could not erode."; 
		return;
	}
    
    if (!rcBuildDistanceField(m_ctx, *m_chf))
    {
        m_ctx->log(RC_LOG_ERROR, "buildNavigation: Could not build distance field.");
        std::cout<<"buildNavigation: Could not build distance field.";
        return;
    }
        
    if (!rcBuildRegions(m_ctx, *m_chf, 0, m_cfg.minRegionArea, m_cfg.mergeRegionArea))
    {
        m_ctx->log(RC_LOG_ERROR, "buildNavigation: Could not build regions.");
        std::cout<<"buildNavigation: Could not build regions.";
        return;
    }

    std::cout<<"STEP 3 DONE";
    
    m_cset = rcAllocContourSet();
	if (!m_cset)
	{
		m_ctx->log(RC_LOG_ERROR, "buildNavigation: Out of memory 'cset'.");
        std::cout<<"buildNavigation: Out of memory 'cset'.";
		return;
	}
	if (!rcBuildContours(m_ctx, *m_chf, m_cfg.maxSimplificationError, m_cfg.maxEdgeLen, *m_cset))
	{
		m_ctx->log(RC_LOG_ERROR, "buildNavigation: Could not create contours.");
        std::cout<<"buildNavigation: Could not create contours.";
		return;
	}
    
    std::cout<<"STEP 4 DONE";
	
	m_pmesh = rcAllocPolyMesh();
	if (!m_pmesh)
	{
		m_ctx->log(RC_LOG_ERROR, "buildNavigation: Out of memory 'pmesh'.");
        std::cout<<"buildNavigation: Out of memory 'pmesh'.";
		return;
	}
	if (!rcBuildPolyMesh(m_ctx, *m_cset, m_cfg.maxVertsPerPoly, *m_pmesh))
	{
		m_ctx->log(RC_LOG_ERROR, "buildNavigation: Could not triangulate contours.");
        std::cout<<"buildNavigation: Could not triangulate contours.";
		return;
	}
    
    std::cout<<"STEP 5 DONE";
	
	m_dmesh = rcAllocPolyMeshDetail();
	if (!m_dmesh)
	{
		m_ctx->log(RC_LOG_ERROR, "buildNavigation: Out of memory 'pmdtl'.");
        std::cout<<"buildNavigation: Out of memory 'pmdtl'.";
		return;
	}
    
	if (!rcBuildPolyMeshDetail(m_ctx, *m_pmesh, *m_chf, m_cfg.detailSampleDist, m_cfg.detailSampleMaxError, *m_dmesh))
	{
		m_ctx->log(RC_LOG_ERROR, "buildNavigation: Could not build detail mesh.");
        std::cout<<"buildNavigation: Could not build detail mesh.";
		return;
	}
    
    std::cout<<"STEP 6 DONE\n";
    
    if (m_cfg.maxVertsPerPoly <= DT_VERTS_PER_POLYGON)
    {
        //m_pLog->logMessage("Detour 1000");
        
        unsigned char* navData = 0;
        int navDataSize = 0;
        
        
        // Update poly flags from areas.
        for (int i = 0; i < m_pmesh->npolys; ++i)
        {
            if (m_pmesh->areas[i] == RC_WALKABLE_AREA)
            {
                m_pmesh->areas[i] = SAMPLE_POLYAREA_GROUND;
                m_pmesh->flags[i] = SAMPLE_POLYFLAGS_WALK;
            }
        }
        
        
        dtNavMeshCreateParams params;
        memset(&params, 0, sizeof(params));
        params.verts = m_pmesh->verts;
        params.vertCount = m_pmesh->nverts;
        params.polys = m_pmesh->polys;
        params.polyAreas = m_pmesh->areas;
        params.polyFlags = m_pmesh->flags;
        params.polyCount = m_pmesh->npolys;
        params.nvp = m_pmesh->nvp;
        params.detailMeshes = m_dmesh->meshes;
        params.detailVerts = m_dmesh->verts;
        params.detailVertsCount = m_dmesh->nverts;
        params.detailTris = m_dmesh->tris;
        params.detailTriCount = m_dmesh->ntris;
        
        params.walkableHeight = m_cfg.walkableHeight;
        params.walkableRadius = m_cfg.walkableRadius;
        params.walkableClimb = m_cfg.walkableRadius;
        rcVcopy(params.bmin, m_pmesh->bmin);
        rcVcopy(params.bmax, m_pmesh->bmax);
        params.cs = m_cfg.cs;
        params.ch = m_cfg.ch;
        
        if (!dtCreateNavMeshData(&params, &navData, &navDataSize))
        {
            m_ctx->log(RC_LOG_ERROR, "Could not build Detour navmesh.");
            return;
        }
        
        m_navMesh = dtAllocNavMesh();
        if (!m_navMesh)
        {
            dtFree(navData);
            m_ctx->log(RC_LOG_ERROR, "Could not create Detour navmesh");
            return;
        }
        
        dtStatus status;
        
        status = m_navMesh->init(navData, navDataSize, DT_TILE_FREE_DATA);
        if (dtStatusFailed(status))
        {
            dtFree(navData);
            m_ctx->log(RC_LOG_ERROR, "Could not init Detour navmesh");
            return;
        }
        
        m_navQuery = dtAllocNavMeshQuery();
        status = m_navQuery->init(m_navMesh, 2048);
        
        if (dtStatusFailed(status))
        {
            m_ctx->log(RC_LOG_ERROR, "Could not init Detour navmesh query");
            return;
        }
    }

    
    m_ctx->stopTimer(RC_TIMER_TOTAL);

	m_ctx->log(RC_LOG_PROGRESS, ">> Polymesh: %d vertices  %d polygons", m_pmesh->nverts, m_pmesh->npolys);
    std::cout<<">> Polymesh: "<<m_pmesh->nverts<<" vertices and "<<m_pmesh->npolys<<" polygons\n"; 
	std::cout<<">> Time : "<<m_ctx->getAccumulatedTime(RC_TIMER_TOTAL)<<"\n"; 
    
    for(size_t index = 0; index < m_pmesh->nverts; index++)
    {
        //std::cout<<"VERTEX: "<<m_pmesh->verts
    }
    /*static const int MAX_OFFMESH_CONNECTIONS = 256;
    float m_offMeshConVerts[MAX_OFFMESH_CONNECTIONS*3*2];
    float m_offMeshConRads[MAX_OFFMESH_CONNECTIONS];
    unsigned char m_offMeshConDirs[MAX_OFFMESH_CONNECTIONS];
    unsigned char m_offMeshConAreas[MAX_OFFMESH_CONNECTIONS];
    unsigned short m_offMeshConFlags[MAX_OFFMESH_CONNECTIONS];
    unsigned int m_offMeshConId[MAX_OFFMESH_CONNECTIONS];
    int m_offMeshConCount;
    
    int nLoop=0 ;
    
    float*           rc_verts;
    unsigned int     rc_nverts;
    int*             rc_tris;
    float*           rc_trinorms;
    unsigned int     rc_ntris;
    float            rc_bmin[3];
    float            rc_bmax[3];
    
    
    CVector3d VertA ;
    CVector3d VertB ;
    CVector3d VertC ;
    CVector3d TriNorm ;
    int nVert=0 ;
    
    
    rc_bmin[0] = SPLAT_BANKDISTANCE;
    rc_bmin[1] = SPLAT_BANKDISTANCE;
    rc_bmin[2] = SPLAT_BANKDISTANCE;
    rc_bmax[0] =-SPLAT_BANKDISTANCE;
    rc_bmax[1] =-SPLAT_BANKDISTANCE;
    rc_bmax[2] =-SPLAT_BANKDISTANCE;
    
    rc_nverts = _pNode->Get_Mesh()->Get_NumVertexes();
    CVertexBuffer::SVertexVTN* pData = static_cast<CVertexBuffer::SVertexVTN*>(_pNode->Get_Mesh()->Get_VB()->Get_Data());  
    rc_verts = new float[rc_nverts * 3];
    for(nLoop=0 ; nLoop<rc_nverts ; nLoop++)
    {
        rc_verts[nLoop*3+0] = pData[nLoop].m_vPosition.x;
        rc_verts[nLoop*3+1] = pData[nLoop].m_vPosition.y;
        rc_verts[nLoop*3+2] = pData[nLoop].m_vPosition.z;
        
        if(pData[nLoop].m_vPosition.x < rc_bmin[0]) rc_bmin[0] = pData[nLoop].m_vPosition.x;
        if(pData[nLoop].m_vPosition.y < rc_bmin[1]) rc_bmin[1] = pData[nLoop].m_vPosition.y;
        if(pData[nLoop].m_vPosition.z < rc_bmin[2]) rc_bmin[2] = pData[nLoop].m_vPosition.z;
        
        if(pData[nLoop].m_vPosition.x > rc_bmax[0]) rc_bmax[0] = pData[nLoop].m_vPosition.x;
        if(pData[nLoop].m_vPosition.y > rc_bmax[1]) rc_bmax[1] = pData[nLoop].m_vPosition.y;
        if(pData[nLoop].m_vPosition.z > rc_bmax[2]) rc_bmax[2] = pData[nLoop].m_vPosition.z;
    }
    
    // work out how many triangles we need.  We don't use every triangle, for instance we don't use def light boxes.
    // we only used opaque, gel or alphat triangles.
    int nMaxTri = _pNode->Get_Mesh()->Get_NumIndexes() / 3;
    /*int nTextureCategory=0 ;
    rc_ntris=0 ;
    for(nLoop=0 ; nLoop<nMaxTri; nLoop++)
    {
        nTextureCategory=m_OgreBZNBSP->m_pTextureCat[  m_OgreBZNBSP->m_pTriangle[nLoop].Texture  ] ;
        if((nTextureCategory>=TEXCAT_OPAQUE) && (nTextureCategory<=TEXCAT_ALPHAT2))
            rc_ntris++ ;
    }*/
    
    /*m_ctx = new rcContext(true) ;
    
    // setup recast triangles
    rc_tris= new int[rc_ntris*3] ;
    rc_trinorms = new float[rc_ntris*3] ;
    
    int nTriCount=0 ;
    unsigned short* pIBData = _pNode->Get_Mesh()->Get_IB()->Get_Data();
    for(nLoop=0 ; nLoop < nMaxTri ; nLoop++)
    {
        // not all triangles should be added, for instance we don't want deferred light boxes.
        // So check the texture category.  We only accept opaque, gel or alphat textures.
        //nTextureCategory=m_OgreBZNBSP->m_pTextureCat[  m_OgreBZNBSP->m_pTriangle[nLoop].Texture  ] ;
        //if((nTextureCategory<TEXCAT_OPAQUE) || (nTextureCategory>TEXCAT_ALPHAT2))
        //    continue ;
        
        
        // vertex indices
        rc_tris[nTriCount*3+0] = pIBData[nTriCount*3+0];
        rc_tris[nTriCount*3+1] = pIBData[nTriCount*3+1];
        rc_tris[nTriCount*3+2] = pIBData[nTriCount*3+2];
        
        
        // calculate normal for this triangle.  
        // Why doesn't it exist already?  Because we usually use normals on verts, not triangles.
        nVert =  pIBData[nTriCount*3+0];
        VertA.x = pData[nVert].m_vPosition.x;
        VertA.y = pData[nVert].m_vPosition.y;
        VertA.z = pData[nVert].m_vPosition.z;
        
        nVert =  pIBData[nTriCount*3+1];
        VertB.x = pData[nVert].m_vPosition.x;
        VertB.y = pData[nVert].m_vPosition.y;
        VertB.z = pData[nVert].m_vPosition.z;
        
        nVert =  pIBData[nTriCount*3+2];
        VertC.x = pData[nVert].m_vPosition.x;
        VertC.y = pData[nVert].m_vPosition.y;
        VertC.z = pData[nVert].m_vPosition.z;
        
        VertA -= VertC ;
        VertB -= VertC ;
        
        VertA = Cross(VertA, VertB);
        VertA.Normalize();
        
        // recast version of the normal
        rc_trinorms[nTriCount*3+0] = VertA.x ;
        rc_trinorms[nTriCount*3+1] = VertA.y ;
        rc_trinorms[nTriCount*3+2] = VertA.z ;
        nTriCount++ ;
    }
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    
    
    //RecastCleanup() ;
    
    
    //
    // Step 1. Initialize build config.
    //
    
    // cellsize (1.5, 1.0) was the most accurate at finding all the places we could go, but was also slow to generate.
    // Might be suitable for pre-generated meshes. Though it also produces a lot more polygons.
    
       
    
    // Reset build times gathering.
    m_ctx->resetTimers();
    
    // Start the build process.   
    m_ctx->startTimer(RC_TIMER_TOTAL);
    
    // Set the area where the navigation will be build.
    // Here the bounds of the input mesh are used, but the
    // area could be specified by an user defined box, etc.
    rcVcopy(m_cfg.bmin, rc_bmin);
    rcVcopy(m_cfg.bmax, rc_bmax);
    rcCalcGridSize(m_cfg.bmin, m_cfg.bmax, m_cfg.cs, &m_cfg.width, &m_cfg.height);
    
    
    //
    // Step 2. Rasterize input polygon soup.
    //
    
    // Allocate voxel heightfield where we rasterize our input data to.
    
    m_solid = rcAllocHeightfield();
    if (!m_solid)
    {
        m_ctx->log(RC_LOG_ERROR, "buildNavigation: Out of memory 'solid'.");
        return;
    }
    if (!rcCreateHeightfield(m_ctx, *m_solid, m_cfg.width, m_cfg.height, m_cfg.bmin, m_cfg.bmax, m_cfg.cs, m_cfg.ch))
    {
        m_ctx->log(RC_LOG_ERROR, "buildNavigation: Could not create solid heightfield.");
        return;
    }
    
    // Allocate array that can hold triangle area types.
    // If you have multiple meshes you need to process, allocate
    // and array which can hold the max number of triangles you need to process.
    m_triareas = new unsigned char[rc_ntris];
    if (!m_triareas)
    {
        m_ctx->log(RC_LOG_ERROR, "buildNavigation: Out of memory 'm_triareas' (%d).", rc_ntris);
        return;
    }
    
    // Find triangles which are walkable based on their slope and rasterize them.
    // If your input data is multiple meshes, you can transform them here, calculate
    // the are type for each of the meshes and rasterize them.
    memset(m_triareas, 0, rc_ntris*sizeof(unsigned char));
    rcMarkWalkableTriangles(m_ctx, m_cfg.walkableSlopeAngle, rc_verts, rc_nverts, rc_tris, rc_ntris, m_triareas);
    rcRasterizeTriangles(m_ctx, rc_verts, rc_nverts, rc_tris, m_triareas, rc_ntris, *m_solid, m_cfg.walkableClimb);
    
    if (!false)
    {
        delete [] m_triareas;
        m_triareas = 0;
    }
    
    //
    // Step 3. Filter walkables surfaces.
    //
    
    // Once all geoemtry is rasterized, we do initial pass of filtering to
    // remove unwanted overhangs caused by the conservative rasterization
    // as well as filter spans where the character cannot possibly stand.
    rcFilterLowHangingWalkableObstacles(m_ctx, m_cfg.walkableClimb, *m_solid);
    rcFilterLedgeSpans(m_ctx, m_cfg.walkableHeight, m_cfg.walkableClimb, *m_solid);
    rcFilterWalkableLowHeightSpans(m_ctx, m_cfg.walkableHeight, *m_solid);
    
    //
    // Step 4. Partition walkable surface to simple regions.
    //
    
    // Compact the heightfield so that it is faster to handle from now on.
    // This will result more cache coherent data as well as the neighbours
    // between walkable cells will be calculated.
    m_chf = rcAllocCompactHeightfield();
    if (!m_chf)
    {
        m_ctx->log(RC_LOG_ERROR, "buildNavigation: Out of memory 'chf'.");
        return;
    }
    if (!rcBuildCompactHeightfield(m_ctx, m_cfg.walkableHeight, m_cfg.walkableClimb, *m_solid, *m_chf))
    {
        m_ctx->log(RC_LOG_ERROR, "buildNavigation: Could not build compact data.");
        return;
    }
    
    if (!false)
    {
        rcFreeHeightField(m_solid);
        m_solid = 0;
    }
    
    // Erode the walkable area by agent radius.
    if (!rcErodeWalkableArea(m_ctx, m_cfg.walkableRadius, *m_chf))
    {
        m_ctx->log(RC_LOG_ERROR, "buildNavigation: Could not erode.");
        return;
    }
    
    // (Optional) Mark areas.
    //const ConvexVolume* vols = m_geom->getConvexVolumes();
    //for (int i  = 0; i < m_geom->getConvexVolumeCount(); ++i)
    //   rcMarkConvexPolyArea(m_ctx, vols[i].verts, vols[i].nverts, vols[i].hmin, vols[i].hmax, (unsigned char)vols[i].area, *m_chf);
    
    // Prepare for region partitioning, by calculating distance field along the walkable surface.
    if (!rcBuildDistanceField(m_ctx, *m_chf))
    {
        m_ctx->log(RC_LOG_ERROR, "buildNavigation: Could not build distance field.");
        return;
    }
    
    // Partition the walkable surface into simple regions without holes.
    if (!rcBuildRegions(m_ctx, *m_chf, m_cfg.borderSize, m_cfg.minRegionArea, m_cfg.mergeRegionArea))
    {
        m_ctx->log(RC_LOG_ERROR, "buildNavigation: Could not build regions.");
        return;
    }
    
    //
    // Step 5. Trace and simplify region contours.
    //
    
    // Create contours.
    m_cset = rcAllocContourSet();
    if (!m_cset)
    {
        m_ctx->log(RC_LOG_ERROR, "buildNavigation: Out of memory 'cset'.");
        return;
    }
    if (!rcBuildContours(m_ctx, *m_chf, m_cfg.maxSimplificationError, m_cfg.maxEdgeLen, *m_cset))
    {
        m_ctx->log(RC_LOG_ERROR, "buildNavigation: Could not create contours.");
        return;
    }
    
    //
    // Step 6. Build polygons mesh from contours.
    //
    
    // Build polygon navmesh from the contours.
    m_pmesh = rcAllocPolyMesh();
    if (!m_pmesh)
    {
        m_ctx->log(RC_LOG_ERROR, "buildNavigation: Out of memory 'pmesh'.");
        return;
    }
    if (!rcBuildPolyMesh(m_ctx, *m_cset, m_cfg.maxVertsPerPoly, *m_pmesh))
    {
        m_ctx->log(RC_LOG_ERROR, "buildNavigation: Could not triangulate contours.");
        return;
    }
    
    //
    // Step 7. Create detail mesh which allows to access approximate height on each polygon.
    //
    
    m_dmesh = rcAllocPolyMeshDetail();
    if (!m_dmesh)
    {
        m_ctx->log(RC_LOG_ERROR, "buildNavigation: Out of memory 'pmdtl'.");
        return;
    }
    
    if (!rcBuildPolyMeshDetail(m_ctx, *m_pmesh, *m_chf, m_cfg.detailSampleDist, m_cfg.detailSampleMaxError, *m_dmesh))
    {
        m_ctx->log(RC_LOG_ERROR, "buildNavigation: Could not build detail mesh.");
        return;
    }
    
    if (!false)
    {
        rcFreeCompactHeightfield(m_chf);
        m_chf = 0;
        rcFreeContourSet(m_cset);
        m_cset = 0;
    }
    
    // At this point the navigation mesh data is ready, you can access it from m_pmesh.
    // See duDebugDrawPolyMesh or dtCreateNavMeshData as examples how to access the data.
    
    //
    // (Optional) Step 8. Create Detour data from Recast poly mesh.
    //
    
    // The GUI may allow more max points per polygon than Detour can handle.
    // Only build the detour navmesh if we do not exceed the limit.
    
    
    /*if (m_cfg.maxVertsPerPoly <= DT_VERTS_PER_POLYGON)
    {
        //m_pLog->logMessage("Detour 1000");
        
        unsigned char* navData = 0;
        int navDataSize = 0;
        
        
        // Update poly flags from areas.
        for (int i = 0; i < m_pmesh->npolys; ++i)
        {
            if (m_pmesh->areas[i] == RC_WALKABLE_AREA)
            {
                m_pmesh->areas[i] = SAMPLE_POLYAREA_GROUND;
                m_pmesh->flags[i] = SAMPLE_POLYFLAGS_WALK;
            }
        }
        
        
        dtNavMeshCreateParams params;
        memset(&params, 0, sizeof(params));
        params.verts = m_pmesh->verts;
        params.vertCount = m_pmesh->nverts;
        params.polys = m_pmesh->polys;
        params.polyAreas = m_pmesh->areas;
        params.polyFlags = m_pmesh->flags;
        params.polyCount = m_pmesh->npolys;
        params.nvp = m_pmesh->nvp;
        params.detailMeshes = m_dmesh->meshes;
        params.detailVerts = m_dmesh->verts;
        params.detailVertsCount = m_dmesh->nverts;
        params.detailTris = m_dmesh->tris;
        params.detailTriCount = m_dmesh->ntris;
        
        // no off mesh connections yet
        m_offMeshConCount = 0 ;
        params.offMeshConVerts = m_offMeshConVerts ;
        params.offMeshConRad = m_offMeshConRads ;
        params.offMeshConDir = m_offMeshConDirs ;
        params.offMeshConAreas = m_offMeshConAreas ;
        params.offMeshConFlags = m_offMeshConFlags ;
        params.offMeshConUserID = m_offMeshConId ;
        params.offMeshConCount = m_offMeshConCount ;
        
        params.walkableHeight = 64.0f;
        params.walkableRadius = 16.0f;
        params.walkableClimb = 16.0f;
        rcVcopy(params.bmin, m_pmesh->bmin);
        rcVcopy(params.bmax, m_pmesh->bmax);
        params.cs = m_cfg.cs;
        params.ch = m_cfg.ch;
        
        //m_pLog->logMessage("Detour 2000");
        
        if (!dtCreateNavMeshData(&params, &navData, &navDataSize))
        {
            m_ctx->log(RC_LOG_ERROR, "Could not build Detour navmesh.");
            return;
        }
        
        //m_pLog->logMessage("Detour 3000");
        
        m_navMesh = dtAllocNavMesh();
        if (!m_navMesh)
        {
            dtFree(navData);
            m_ctx->log(RC_LOG_ERROR, "Could not create Detour navmesh");
            return;
        }
        
        //m_pLog->logMessage("Detour 4000");
        
        dtStatus status;
        
        status = m_navMesh->init(navData, navDataSize, DT_TILE_FREE_DATA);
        if (dtStatusFailed(status))
        {
            dtFree(navData);
            m_ctx->log(RC_LOG_ERROR, "Could not init Detour navmesh");
            return;
        }
        
        //m_pLog->logMessage("Detour 5000");
        
        m_navQuery = dtAllocNavMeshQuery();
        status = m_navQuery->init(m_navMesh, 2048);
        
       // m_pLog->logMessage("Detour 5500");
        
        if (dtStatusFailed(status))
        {
            m_ctx->log(RC_LOG_ERROR, "Could not init Detour navmesh query");
            return;
        }
        
        //m_pLog->logMessage("Detour 6000");
    }
    
    m_ctx->stopTimer(RC_TIMER_TOTAL);
    
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    // cleanup stuff we don't need
    delete [] rc_verts ;
    delete [] rc_tris ;
    delete [] rc_trinorms ;
    
    //m_pLog->logMessage("NavMeshBuild End");
    return ;*/
}
/*
void CreateRecastPolyMesh(const struct rcPolyMesh& mesh)
{
    
    const int nvp = mesh.nvp; 
    const float cs = mesh.cs;
    const float ch = mesh.ch;
    const float* orig = mesh.bmin;
    
    m_flDataX = mesh.npolys ;
    m_flDataY = mesh.nverts ;
    
    // create scenenodes
    m_pRecastSN = m_pSceneMgr->getRootSceneNode()->createChildSceneNode("RecastSN") ;
    
    int nIndex=0 ;
    m_nAreaCount=mesh.npolys ;
    
    
    
    if(m_nAreaCount)
    {
        
        // start defining the manualObject
        m_pRecastMOWalk = m_pSceneMgr->createManualObject("RecastMOWalk");
        m_pRecastMOWalk->begin("recastwalk", RenderOperation::OT_TRIANGLE_LIST) ;
        for (int i = 0; i < mesh.npolys; ++i) // go through all polygons
            if (mesh.areas[i] == SAMPLE_POLYAREA_GROUND)
            {
                const unsigned short* p = &mesh.polys[i*nvp*2];
                
                unsigned short vi[3];
                for (int j = 2; j < nvp; ++j) // go through all verts in the polygon
                {
                    if (p[j] == RC_MESH_NULL_IDX) break;
                    vi[0] = p[0];
                    vi[1] = p[j-1];
                    vi[2] = p[j];
                    for (int k = 0; k < 3; ++k) // create a 3-vert triangle for each 3 verts in the polygon.
                    {
                        const unsigned short* v = &mesh.verts[vi[k]*3];
                        const float x = orig[0] + v[0]*cs;
                        const float y = orig[1] + (v[1]+1)*ch;
                        const float z = orig[2] + v[2]*cs;
                        
                        m_pRecastMOWalk->position(x, y, z) ;
                        if (mesh.areas[i] == SAMPLE_POLYAREA_GROUND)
                            m_pRecastMOWalk->colour(0,0.7,0) ;
                        else
                            m_pRecastMOWalk->colour(0,0.175,0) ;
                        
                    }
                    m_pRecastMOWalk->triangle(nIndex, nIndex+1, nIndex+2) ;
                    nIndex+=3 ;
                }
            }
        m_pRecastMOWalk->end() ;
        m_pRecastSN->attachObject(m_pRecastMOWalk) ;
        
        
        m_pRecastMONeighbour = m_pSceneMgr->createManualObject("RecastMONeighbour");
        m_pRecastMONeighbour->begin("recastline", RenderOperation::OT_LINE_LIST) ;
        
        for (int i = 0; i < mesh.npolys; ++i)
        {
            const unsigned short* p = &mesh.polys[i*nvp*2];
            for (int j = 0; j < nvp; ++j)
            {
                if (p[j] == RC_MESH_NULL_IDX) break;
                if (p[nvp+j] == RC_MESH_NULL_IDX) continue;
                int vi[2];
                vi[0] = p[j];
                if (j+1 >= nvp || p[j+1] == RC_MESH_NULL_IDX)
                    vi[1] = p[0];
                else
                    vi[1] = p[j+1];
                for (int k = 0; k < 2; ++k)
                {
                    const unsigned short* v = &mesh.verts[vi[k]*3];
                    const float x = orig[0] + v[0]*cs;
                    const float y = orig[1] + (v[1]+1)*ch + 0.1f;
                    const float z = orig[2] + v[2]*cs;
                    //dd->vertex(x, y, z, coln);
                    m_pRecastMONeighbour->position(x, y+0.25, z) ;
                    m_pRecastMONeighbour->colour(0,1,1) ;
                    
                }
            }
        }
        
        m_pRecastMONeighbour->end() ;
        m_pRecastSN->attachObject(m_pRecastMONeighbour) ;
        
        
        m_pRecastMOBoundary = m_pSceneMgr->createManualObject("RecastMOBoundary");
        m_pRecastMOBoundary->begin("recastline", RenderOperation::OT_LINE_LIST) ;
        
        for (int i = 0; i < mesh.npolys; ++i)
        {
            const unsigned short* p = &mesh.polys[i*nvp*2];
            for (int j = 0; j < nvp; ++j)
            {
                if (p[j] == RC_MESH_NULL_IDX) break;
                if (p[nvp+j] != RC_MESH_NULL_IDX) continue;
                int vi[2];
                vi[0] = p[j];
                if (j+1 >= nvp || p[j+1] == RC_MESH_NULL_IDX)
                    vi[1] = p[0];
                else
                    vi[1] = p[j+1];
                for (int k = 0; k < 2; ++k)
                {
                    const unsigned short* v = &mesh.verts[vi[k]*3];
                    const float x = orig[0] + v[0]*cs;
                    const float y = orig[1] + (v[1]+1)*ch + 0.1f;
                    const float z = orig[2] + v[2]*cs;
                    //dd->vertex(x, y, z, colb);
                    
                    m_pRecastMOBoundary->position(x, y+0.25, z) ;
                    m_pRecastMOBoundary->colour(0,1,0) ;
                }
            }
        }
        
        m_pRecastMOBoundary->end() ;
        m_pRecastSN->attachObject(m_pRecastMOBoundary) ;
        
        
        
        
    }// end areacount
    
    
}

void OgreFramework::CreateRecastPathLine(int nPathSlot)
{
    if(m_pRecastMOPath)
    {
        m_pRecastSN->detachObject("RecastMOPath") ;
        m_pSceneMgr->destroyManualObject(m_pRecastMOPath) ;
        m_pRecastMOPath=NULL ;
    }
    
    
    m_pRecastMOPath = m_pSceneMgr->createManualObject("RecastMOPath");
    m_pRecastMOPath->begin("recastline", RenderOperation::OT_LINE_STRIP) ;
    
    
    int nVertCount=m_PathStore[nPathSlot].MaxVertex ;
    for(int nVert=0 ; nVert<nVertCount ; nVert++)
    {
        m_pRecastMOPath->position(m_PathStore[nPathSlot].PosX[nVert], m_PathStore[nPathSlot].PosY[nVert]+8.0f, m_PathStore[nPathSlot].PosZ[nVert]) ;
        m_pRecastMOPath->colour(1,0,0) ;
        
        //sprintf(m_chBug, "Line Vert %i, %f %f %f", nVert, m_PathStore[nPathSlot].PosX[nVert], m_PathStore[nPathSlot].PosY[nVert], m_PathStore[nPathSlot].PosZ[nVert]) ;
        //m_pLog->logMessage(m_chBug);
    }
    
    
    
    
    m_pRecastMOPath->end() ;
    m_pRecastSN->attachObject(m_pRecastMOPath) ;
}

*/