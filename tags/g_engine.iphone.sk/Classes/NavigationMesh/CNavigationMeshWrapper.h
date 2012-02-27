//
//  CNavigationMeshWrapper.h
//  gEngine
//
//  Created by sergey.sergeev on 2/22/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CNavigationMeshWrapper_h
#define gEngine_CNavigationMeshWrapper_h

#include "Recast.h"
#include "INode.h"
#include "CMesh.h"
#include "DetourNavMesh.h"
#include "DetourNavMeshBuilder.h"
#include "DetourNavMeshQuery.h"

#define MAX_PATHSLOT      128 // how many paths we can store
#define MAX_PATHPOLY      256 // max number of polygons in a path
#define MAX_PATHVERT      512 // most verts in a path 
#define k_BOUND_BOX_VALUE 2048

class CNavigationMeshWrapper
{
enum SamplePolyAreas
{
    SAMPLE_POLYAREA_GROUND,
    SAMPLE_POLYAREA_WATER,
    SAMPLE_POLYAREA_ROAD,
    SAMPLE_POLYAREA_DOOR,
    SAMPLE_POLYAREA_GRASS,
    SAMPLE_POLYAREA_JUMP,
};
enum SamplePolyFlags
{
    SAMPLE_POLYFLAGS_WALK = 0x01,     
    SAMPLE_POLYFLAGS_SWIM = 0x02,      
    SAMPLE_POLYFLAGS_DOOR = 0x04,      
    SAMPLE_POLYFLAGS_JUMP = 0x08,   
    SAMPLE_POLYFLAGS_DISABLED = 0x10,
    SAMPLE_POLYFLAGS_ALL = 0xffff   
};    
    
private:
    rcConfig m_cfg; 
    rcContext* m_pNavigationMeshContext;
    rcHeightfield* m_pHeightField;
    unsigned char* m_pTriangleAreas;
    rcCompactHeightfield* m_pCompactHeightField;
    rcContourSet* m_pContour;
    rcPolyMesh* m_pPolygonMesh;
    rcPolyMeshDetail* m_pPolygonMeshDetail;
    class dtNavMesh* m_pNavigationMesh;
    class dtNavMeshQuery* m_pNavigationMeshQuery;
    static CNavigationMeshWrapper* m_pInstance;
public:
    CNavigationMeshWrapper(void);
    ~CNavigationMeshWrapper(void);
    static CNavigationMeshWrapper* Instance(void);
    void SetupNavigationMesh(INode* _pNode);
    CMesh* CreateRenderNavMesh();
    std::vector<CVector2d> FindPath(CVector3d _vStartPoint, CVector3d _vEndPoint);
};

#endif
