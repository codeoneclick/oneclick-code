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
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"

class CCollisionMgr
{
public:
    class SRay3d
    {
    public:
        glm::vec3 m_vDirection;
        glm::vec3 m_vOrigin;
        glm::vec3 m_vEnd;
    };
private:
    glm::vec2 m_vTouch2DPoint;
    glm::vec3 m_vTouch3DPoint;
    unsigned int m_iHexColliderID;
    bool m_bIsTouch;
    unsigned int RgbToHex(unsigned char _r, unsigned char _g, unsigned char _b);
    SRay3d m_vTouchRay;
public:
    CCollisionMgr();
    ~CCollisionMgr();
    
    void Create_Collider(ICollider* _pCollider);
    void Remove_Collider(ICollider* _pCollider);

    void OnScreenTouch(glm::vec2 _vTouchPoint);
    
    unsigned int Get_HexColliderID(void) { return m_iHexColliderID; }
    
    inline SRay3d Unproject(const glm::vec2& _vValue, const glm::mat4x4& _mView, const glm::mat4x4& _mProjection, const int* _pViewport)
    {
        glm::vec3 vDirection, vOrigin;
        float fScreenX =  -((( 2.0f * _vValue.x ) / _pViewport[2]) - 1.0f ) / _mProjection[0][0];
        float fScreenY =  -((( 2.0f * _vValue.y ) / _pViewport[3]) - 1.0f ) / _mProjection[1][1];
        glm::mat4x4 mInverseView = glm::inverse(_mView);
        
        vDirection.x  = (fScreenX * mInverseView[0][0] + fScreenY * mInverseView[1][0] + mInverseView[2][0]);
        vDirection.y  = (fScreenX * mInverseView[0][1] + fScreenY * mInverseView[1][1] + mInverseView[2][1]);
        vDirection.z  = (fScreenX * mInverseView[0][2] + fScreenY * mInverseView[1][2] + mInverseView[2][2]);
        vOrigin.x = mInverseView[3][0];
        vOrigin.y = mInverseView[3][1];
        vOrigin.z = mInverseView[3][2];
        std::cout<<"[CCollisionMgr::Unproject] Origin : ( "<<vOrigin.x<<", "<<vOrigin.y<<", "<<vOrigin.z<<" )\n"; 
        SRay3d tRay;
        tRay.m_vDirection = vDirection;
        tRay.m_vOrigin = vOrigin;
        return tRay;
    }
    
    void Set_Touch3DPoint(glm::vec3 _vTouchPoint) { m_vTouch3DPoint = _vTouchPoint; }
    glm::vec3 Get_Touch3DPoint(void) { return m_vTouch3DPoint; }
    SRay3d Get_TouchRay(void) { return m_vTouchRay; }
    bool RayPlaneIntersection(glm::vec3& _vTrianglePoint_01, glm::vec3& _vTrianglePoint_02, glm::vec3& _vTrianglePoint_03, SRay3d& _tRay, glm::vec3* _vIntersectPoint);
    bool RayTriangleIntersection(glm::vec3& _vTrianglePoint_01, glm::vec3& _vTrianglePoint_02, glm::vec3& _vTrianglePoint_03, SRay3d& _tRay, glm::vec3* _vIntersectPoint);
    bool Get_CollisionPoint(CVertexBuffer *_pVB, CIndexBuffer *_pIB, SRay3d& _tRay3d, glm::vec3* _vCollisionPoint);
    void Update(void);
};

#endif
