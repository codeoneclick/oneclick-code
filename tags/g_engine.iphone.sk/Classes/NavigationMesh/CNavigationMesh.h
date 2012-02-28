//
//  CNavigationMesh.h
//  gEngine
//
//  Created by sergey.sergeev on 2/22/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CNavigationMesh_h
#define gEngine_CNavigationMesh_h

#include "Recast.h"
#include "INode.h"
#include "CMesh.h"
#include "DetourNavMesh.h"
#include "DetourNavMeshBuilder.h"
#include "DetourNavMeshQuery.h"

#define MAX_PATHSLOT      128 
#define MAX_PATHPOLY      256 
#define MAX_PATHVERT      512 
#define k_BOUND_BOX_VALUE 2048

class CNavigationMesh
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
    CMesh* m_pVisualMesh;
    void Create_VisualMesh(void);
public:
    CNavigationMesh(void);
    ~CNavigationMesh(void);
    void Set_NavigationModel(INode* _pNode);
    CMesh* Get_VisualMesh(void) { return m_pVisualMesh; }
    std::vector<CVector2d> FindPath(CVector3d _vStartPoint, CVector3d _vEndPoint);
};

#endif
