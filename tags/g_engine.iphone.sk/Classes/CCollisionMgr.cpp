//
//  CCollisionMgr.cpp
//  gEngine
//
//  Created by sergey.sergeev on 1/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CCollisionMgr.h"
#include "CBatchMgr.h"
#include "CEventMgr.h"
#include "CInput.h"
#include "CSceneMgr.h"
#include "CWindow.h"

CCollisionMgr::CCollisionMgr()
{
    //m_tLastColliderID.r = 0;
    //m_tLastColliderID.g = 0;
    //m_tLastColliderID.b = 0;
    
    m_iHexColliderID = 0;
    
    m_vTouch3DPoint = glm::vec3(0.0f, 0.0f, 0.0f);
    
    m_bIsTouch = false;
}

CCollisionMgr::~CCollisionMgr()
{
    
}

unsigned int CCollisionMgr::RgbToHex(unsigned char _r, unsigned char _g, unsigned char _b)
{
    unsigned int iHex = ((_r & 255) << 16) + ((_g & 255) << 8) + _b;
    return iHex;
}

void CCollisionMgr::Create_Collider(ICollider* _pCollider)
{   
    /*if(m_tLastColliderID.r < 255)
    {
        m_tLastColliderID.r++;
    }
    else if(m_tLastColliderID.g < 255)
    {
        m_tLastColliderID.g++;
        m_tLastColliderID.r = 0;
    }
    else if(m_tLastColliderID.b < 255)
    {
        m_tLastColliderID.b++;
        m_tLastColliderID.r = 0;
        m_tLastColliderID.g = 0;
    }
    
    m_tLastColliderID.m_iHex = RgbToHex(m_tLastColliderID.r, m_tLastColliderID.g, m_tLastColliderID.b);
    _pCollider->Set_ColliredID(m_tLastColliderID);
    m_lContainer[m_tLastColliderID.m_iHex] = _pCollider;*/
}

void CCollisionMgr::Remove_Collider(ICollider* _pCollider)
{
    
}

void CCollisionMgr::OnScreenTouch(glm::vec2 _vTouchPoint) 
{ 
    m_bIsTouch = true; 
    m_vTouch2DPoint = _vTouchPoint; 
    
    glm::mat4x4 mView = CSceneMgr::Instance()->Get_Camera()->Get_View();
    glm::mat4x4 mProjection = CSceneMgr::Instance()->Get_Camera()->Get_Projection();
    
    glm::vec3 vTouchPointNear = glm::vec3(_vTouchPoint, 0.0f);
    glm::vec3 vTouchPointFar  = glm::vec3(_vTouchPoint, 0.9f);
    glm::vec4 vViewport = glm::vec4(0.0f, 0.0f, CWindow::Get_ScreenHeight(), CWindow::Get_ScreenWidth());
    
    glm::vec3 vUnProjectPointNear = glm::unProject(vTouchPointNear, mView, mProjection, vViewport);
    glm::vec3 vUnProjectPointFar  = glm::unProject(vTouchPointFar, mView, mProjection, vViewport);
    
    glm::vec3 vDirection = glm::normalize(vTouchPointFar - vTouchPointNear);
    
    //glm::mat4x4 mvp_inverse = glm::inverse(mView * mProjection);
    //glm::vec4 dir = mvp_inverse * glm::vec4(0, 0, 1, 0);
    //O = glm::vec3(origin.x, origin.y, origin.z);
    //glm::vec3 vDirection = glm::normalize(glm::vec3(dir.x, dir.y, dir.z));
    
    glm::vec3 vCameraPosition = CSceneMgr::Instance()->Get_Camera()->Get_Position();
    
    std::cout<<"[CCollisionMgr::OnScreenTouch] Camera Position : ( "<<vCameraPosition.x<<", "<<vCameraPosition.y<<", "<<vCameraPosition.z<<" )\n";
    
    int pViewport[4];
    pViewport[0] = 0;
    pViewport[1] = 0;
    pViewport[2] = CWindow::Get_ScreenHeight();
    pViewport[3] = CWindow::Get_ScreenWidth();
    glm::vec2 vScreenCoord = _vTouchPoint;
    m_vTouchRay = Unproject(vScreenCoord, mView, mProjection, pViewport);
    CEventMgr::Instance()->OnEvent(CEventMgr::E_EVENT_TOUCH);
}

bool CCollisionMgr::RayPlaneIntersection(glm::vec3& _vTrianglePoint_01, glm::vec3& _vTrianglePoint_02, glm::vec3& _vTrianglePoint_03, SRay3d& _tRay, glm::vec3* _vIntersectPoint)
{
    glm::vec3 vEdge_01 = _vTrianglePoint_02 - _vTrianglePoint_01;
	glm::vec3 vEdge_02 = _vTrianglePoint_03 - _vTrianglePoint_01;
    
    glm::vec3 vNormal = glm::cross(vEdge_01, vEdge_02);
    vNormal = glm::normalize(vNormal);
    
    glm::vec3 vOffset_01 = _tRay.m_vOrigin - _vTrianglePoint_01;
    glm::vec3 vOffset_02 = _tRay.m_vEnd - _vTrianglePoint_01;
    
    float fValue_01 = glm::dot(vOffset_01, vNormal);
    float fValue_02 = glm::dot(vOffset_02, vNormal);
    
    if((fValue_01 >= 0.0f && fValue_02 >= 0.0f) || (fValue_01 <= 0.0f && fValue_02 <= 0.0f))
    {
        return false;
    }
    *_vIntersectPoint = (_tRay.m_vEnd * fValue_01 - _tRay.m_vOrigin * fValue_02) / (fValue_01 - fValue_02);
    return true;
}

bool CCollisionMgr::RayTriangleIntersection(glm::vec3& _vTrianglePoint_01, glm::vec3& _vTrianglePoint_02, glm::vec3& _vTrianglePoint_03, SRay3d& _tRay, glm::vec3* _vIntersectPoint)
{
    glm::vec3 vEdge_01 = _vTrianglePoint_02 - _vTrianglePoint_01;
	glm::vec3 vEdge_02 = _vTrianglePoint_03 - _vTrianglePoint_01;
    
    glm::vec3 vPVector = glm::cross(_tRay.m_vDirection, vEdge_02);
	float fDeterminant = glm::dot(vEdge_01, vPVector);
	if(fabs(fDeterminant) < 0.0001f) 
    {
        return false;
    }
    
    float fInvDeterminant = 1.0f / fDeterminant;
    
	glm::vec3 vTVector = _tRay.m_vOrigin - _vTrianglePoint_01;
	float fU = glm::dot(vTVector, vPVector) * fInvDeterminant;  
    if ( fU < -0.0001f || fU > 1.0001f )
    {
        return false;
    }
    
    glm::vec3 vQVector = glm::cross(vTVector, vEdge_01);
	float fV = glm::dot(_tRay.m_vDirection, vQVector) * fInvDeterminant; 
	if ( fV < -0.0001f || (fV + fU) > 1.0001f )
    {
        return false;
    }

	*_vIntersectPoint = _vTrianglePoint_01 + (vEdge_01 * fU) + (vEdge_02 * fV);
	return true;
}

bool CCollisionMgr::Get_CollisionPoint(CVertexBuffer *_pVB, CIndexBuffer *_pIB, SRay3d& _tRay3d, glm::vec3* _vCollisionPoint)
{
    glm::vec3* pPositionData = _pVB->CreateOrReUse_PositionData();
    unsigned short* pIBData = _pIB->Get_Data();
    unsigned int iNumIndexes = _pIB->Get_NumIndexes();
    for(unsigned int index = 0; index < iNumIndexes; index += 3)
    {
        glm::vec3 vPoint_01 = pPositionData[pIBData[index]];
        glm::vec3 vPoint_02 = pPositionData[pIBData[index + 1]];
        glm::vec3 vPoint_03 = pPositionData[pIBData[index + 2]];
            
        if(RayTriangleIntersection(vPoint_01, vPoint_02, vPoint_03, _tRay3d, _vCollisionPoint))
        {
            return true;
        }
    }
    return false;
}

void CCollisionMgr::Update()
{
    
}








