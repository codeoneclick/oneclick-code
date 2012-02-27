//
//  CCollisionMgr.h
//  gEngine
//
//  Created by sergey.sergeev on 1/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CCollisionMgr_h
#define gEngine_CCollisionMgr_h

#include "stdlib.h"
#include <vector>
#include <map>
#include "ICollider.h"

class CCollisionMgr
{
private:
    ICollider::SColliderID m_tLastColliderID;
    std::map<unsigned int, ICollider*> m_lContainer;
    CVector2d m_vTouch2DPoint;
    CVector3d m_vTouch3DPoint;
    unsigned int m_iHexColliderID;
    bool m_bIsTouch;
    unsigned int RgbToHex(unsigned char _r, unsigned char _g, unsigned char _b);
    CRay3d m_vTouchRay;
public:
    CCollisionMgr();
    ~CCollisionMgr();
    
    void Create_Collider(ICollider* _pCollider);
    void Remove_Collider(ICollider* _pCollider);

    void OnScreenTouch(CVector2d _vTouchPoint);
    
    unsigned int Get_HexColliderID(void) { return m_iHexColliderID; }
    
    void Set_Touch3DPoint(CVector3d _vTouchPoint) { m_vTouch3DPoint = _vTouchPoint; }
    CVector3d Get_Touch3DPoint(void) { return m_vTouch3DPoint; }
    CRay3d Get_TouchRay(void) { return m_vTouchRay; }
    bool RayPlaneIntersection(CVector3d& vTrianglePoint_01, CVector3d& vTrianglePoint_02, CVector3d& vTrianglePoint_03, CRay3d& tRay, CVector3d* vIntersectPoint);
    bool RayTriangleIntersection(CVector3d& vTrianglePoint_01, CVector3d& vTrianglePoint_02, CVector3d& vTrianglePoint_03, CRay3d& tRay, CVector3d* vIntersectPoint);
    void Update(void);
};

#endif
