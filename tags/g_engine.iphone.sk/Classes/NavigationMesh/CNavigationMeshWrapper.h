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
#include "DetourNavMesh.h"
#include "DetourNavMeshBuilder.h"
#include "DetourNavMeshQuery.h"

#define MAX_PATHSLOT      128 // how many paths we can store
#define MAX_PATHPOLY      256 // max number of polygons in a path
#define MAX_PATHVERT      512 // most verts in a path 
#define SPLAT_BANKDISTANCE 2048

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
    rcContext* m_ctx;
    rcHeightfield* m_solid;
    unsigned char* m_triareas;
    rcCompactHeightfield* m_chf;
    rcContourSet* m_cset;
    rcPolyMesh* m_pmesh;
    rcPolyMeshDetail* m_dmesh;
    class dtNavMesh* m_navMesh;
    class dtNavMeshQuery* m_navQuery;
    static CNavigationMeshWrapper* m_pInstance;
    std::vector<CVector2d> m_lPath;
public:
    CNavigationMeshWrapper(void);
    ~CNavigationMeshWrapper(void);
    static CNavigationMeshWrapper* Instance(void);
    void SetupNavigationMesh(INode* _pNode);
    void FindPath(CVector3d vStartPos, CVector3d vEndPos);
    std::vector<CVector2d> Get_Path() { return m_lPath; }
};

/*
// structure for storing output straight line paths
typedef struct
{
    float PosX[MAX_PATHVERT] ;
    float PosY[MAX_PATHVERT] ;
    float PosZ[MAX_PATHVERT] ;
    int MaxVertex ;
    int Target ;
}
PATHDATA ;

// These are just sample areas to use consistent values across the samples.
// The use should specify these base on his needs.

// bzn most aren't used yet, just SAMPLE_POLYAREA_GROUND and SAMPLE_POLYFLAGS_WALK


// Detour/Recast stuff

unsigned char* m_triareas;
rcHeightfield* m_solid;
rcCompactHeightfield* m_chf;
rcContourSet* m_cset;
rcPolyMesh* m_pmesh;
rcConfig m_cfg;   
rcPolyMeshDetail* m_dmesh;

class InputGeom* m_geom;
class dtNavMesh* m_navMesh;
class dtNavMeshQuery* m_navQuery;
unsigned char m_navMeshDrawFlags;

rcContext* m_ctx;

float m_cellSize;
float m_cellHeight;
float m_agentHeight;
float m_agentRadius;
float m_agentMaxClimb;
float m_agentMaxSlope;
float m_regionMinSize;
float m_regionMergeSize;
float m_edgeMaxLen;
float m_edgeMaxError;
float m_vertsPerPoly;
float m_detailSampleDist;
float m_detailSampleMaxError;
bool m_keepInterResults ;

// Off-Mesh connections.  Not used yet.
static const int MAX_OFFMESH_CONNECTIONS = 256;
float m_offMeshConVerts[MAX_OFFMESH_CONNECTIONS*3*2];
float m_offMeshConRads[MAX_OFFMESH_CONNECTIONS];
unsigned char m_offMeshConDirs[MAX_OFFMESH_CONNECTIONS];
unsigned char m_offMeshConAreas[MAX_OFFMESH_CONNECTIONS];
unsigned short m_offMeshConFlags[MAX_OFFMESH_CONNECTIONS];
unsigned int m_offMeshConId[MAX_OFFMESH_CONNECTIONS];
int m_offMeshConCount;

void RecastCleanup() ;
bool NavMeshBuild() ;
int FindPath(float* pStartPos, float* pEndPos, int nPathSlot, int nTarget) ;

// helper debug drawing stuff
int m_nAreaCount ;
INode* m_pNode;
void CreateRecastPolyMesh(const struct rcPolyMesh& mesh) ;
void CreateRecastPathLine(int nPathSlot) ;

float m_flTestStart[3] ;
float m_flTestEnd[3] ;

PATHDATA m_PathStore[MAX_PATHSLOT] ; 
*/

#endif
