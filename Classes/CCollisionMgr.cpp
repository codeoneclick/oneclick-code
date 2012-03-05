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
    m_tLastColliderID.r = 0;
    m_tLastColliderID.g = 0;
    m_tLastColliderID.b = 0;
    
    m_iHexColliderID = 0;
    
    m_vTouch3DPoint = CVector3d(0.0f, 0.0f, 0.0f);
    
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
    if(m_tLastColliderID.r < 255)
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
    m_lContainer[m_tLastColliderID.m_iHex] = _pCollider;
}

void CCollisionMgr::Remove_Collider(ICollider* _pCollider)
{
    
}

void CCollisionMgr::OnScreenTouch(CVector2d _vTouchPoint) 
{ 
    m_bIsTouch = true; 
    m_vTouch2DPoint = _vTouchPoint; 
    
    CMatrix4x4 mView = CSceneMgr::Instance()->Get_Camera()->Get_View();
    CMatrix4x4 mProjection = CSceneMgr::Instance()->Get_Camera()->Get_Projection();
    CWindow::SViewport tViewport = CWindow::Get_Viewport();

    
    CVector2d vScreenCoord = _vTouchPoint;
    m_vTouchRay = Unproject(vScreenCoord, mView, mProjection, tViewport.v);
    CEventMgr::Instance()->OnEvent(CEventMgr::E_EVENT_TOUCH);
}

bool CCollisionMgr::RayPlaneIntersection(CVector3d& _vTrianglePoint_01, CVector3d& _vTrianglePoint_02, CVector3d& _vTrianglePoint_03, CRay3d& _tRay, CVector3d* _vIntersectPoint)
{
    CVector3d vEdge_01 = _vTrianglePoint_02 - _vTrianglePoint_01;
	CVector3d vEdge_02 = _vTrianglePoint_03 - _vTrianglePoint_01;
    
    CVector3d vNormal = Cross(vEdge_01, vEdge_02);
    vNormal.Normalize();
    
    CVector3d vOffset_01 = _tRay.m_vOrigin - _vTrianglePoint_01;
    CVector3d vOffset_02 = _tRay.m_vEnd - _vTrianglePoint_01;
    
    float fValue_01 = Dot(vOffset_01, vNormal);
    float fValue_02 = Dot(vOffset_02, vNormal);
    
    if((fValue_01 >= 0.0f && fValue_02 >= 0.0f) || (fValue_01 <= 0.0f && fValue_02 <= 0.0f))
    {
        return false;
    }
    *_vIntersectPoint = (_tRay.m_vEnd * fValue_01 - _tRay.m_vOrigin * fValue_02) / (fValue_01 - fValue_02);
    return true;
}

bool CCollisionMgr::RayTriangleIntersection(CVector3d& _vTrianglePoint_01, CVector3d& _vTrianglePoint_02, CVector3d& _vTrianglePoint_03, CRay3d& _tRay, CVector3d* _vIntersectPoint)
{
    CVector3d vEdge_01 = _vTrianglePoint_02 - _vTrianglePoint_01;
	CVector3d vEdge_02 = _vTrianglePoint_03 - _vTrianglePoint_01;
    
    CVector3d vPVector = Cross(_tRay.m_vDirection, vEdge_02);
	float fDeterminant = Dot(vEdge_01, vPVector);
	if(fabs(fDeterminant) < 0.0001f) 
    {
        return false;
    }
    
    float fInvDeterminant = 1.0f / fDeterminant;
    
	CVector3d vTVector = _tRay.m_vOrigin - _vTrianglePoint_01;
	float fU = Dot(vTVector, vPVector) * fInvDeterminant;  
    if ( fU < -0.0001f || fU > 1.0001f )
    {
        return false;
    }
    
    CVector3d vQVector = Cross(vTVector, vEdge_01);
	float fV = Dot(_tRay.m_vDirection, vQVector) * fInvDeterminant; 
	if ( fV < -0.0001f || (fV + fU) > 1.0001f )
    {
        return false;
    }

	*_vIntersectPoint = _vTrianglePoint_01 + (vEdge_01 * fU) + (vEdge_02 * fV);
	return true;
}

bool CCollisionMgr::Get_CollisionPoint(CVertexBuffer *_pVB, CIndexBuffer *_pIB, CVertexBuffer::E_VERTEX_BUFFER_MODE _eMode,CRay3d& _tRay3d, CVector3d* _vCollisionPoint)
{
    if(_eMode == CVertexBuffer::E_VERTEX_BUFFER_MODE_VTN)
    {
        CVertexBuffer::SVertexVTN* pVBData = static_cast<CVertexBuffer::SVertexVTN*>(_pVB->Get_Data());
        unsigned short* pIBData = _pIB->Get_Data();
        unsigned int iNumIndexes = _pIB->Get_NumIndexes();
        for(unsigned int index = 0; index < iNumIndexes; index += 3)
        {
            CVector3d vPoint_01 = pVBData[pIBData[index]].m_vPosition;
            CVector3d vPoint_02 = pVBData[pIBData[index + 1]].m_vPosition;
            CVector3d vPoint_03 = pVBData[pIBData[index + 2]].m_vPosition;
            
            if(RayTriangleIntersection(vPoint_01, vPoint_02, vPoint_03, _tRay3d, _vCollisionPoint))
            {
                return true;
            }
        }
    }
    else if(_eMode == CVertexBuffer::E_VERTEX_BUFFER_MODE_VC)
    {
        CVertexBuffer::SVertexVC* pVBData = static_cast<CVertexBuffer::SVertexVC*>(_pVB->Get_Data());
        unsigned short* pIBData = _pIB->Get_Data();
        unsigned int iNumIndexes = _pIB->Get_NumIndexes();
        for(unsigned int index = 0; index < iNumIndexes; index += 3)
        {
            CVector3d vPoint_01 = pVBData[pIBData[index]].m_vPosition;
            CVector3d vPoint_02 = pVBData[pIBData[index + 1]].m_vPosition;
            CVector3d vPoint_03 = pVBData[pIBData[index + 2]].m_vPosition;
            
            if(RayTriangleIntersection(vPoint_01, vPoint_02, vPoint_03, _tRay3d, _vCollisionPoint))
            {
                return true;
            }
        }
    }
    return false;
}

void CCollisionMgr::Update()
{
    
}








