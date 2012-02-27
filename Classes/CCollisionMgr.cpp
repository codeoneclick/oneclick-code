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
#include "glu.h"
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
    
    
	CVector3d nearPoint;
	CVector3d farPoint;
	CVector3d rayVector;
    
    CMatrix4x4 mView = CSceneMgr::Instance()->Get_Camera()->Get_View();
    CMatrix4x4 mProjection = CSceneMgr::Instance()->Get_Camera()->Get_Projection();
    CWindow::SViewport tViewport = CWindow::Get_Viewport();
	
	//Retreiving position projected on near plan
	gluUnProject( _vTouchPoint.x, _vTouchPoint.y , 0.0f, mView.m, mProjection.m, tViewport.v, &nearPoint.x, &nearPoint.y, &nearPoint.z);
    
	//Retreiving position projected on far plan
	gluUnProject( _vTouchPoint.x, _vTouchPoint.y,  1.0f, mView.m, mProjection.m, tViewport.v, &farPoint.x, &farPoint.y, &farPoint.z);

    CVector3d temp = CVector3d(_vTouchPoint.x, _vTouchPoint.y, 1.0f);
    farPoint = Unproject(temp, mView, mProjection, tViewport.v);
    
    
    nearPoint = CSceneMgr::Instance()->Get_Camera()->Get_Position();
    rayVector.x = farPoint.x - nearPoint.x;
	rayVector.y = farPoint.y - nearPoint.y;
	rayVector.z = farPoint.z - nearPoint.z;
    
    CVector2d vScreenCoord = _vTouchPoint;
    m_vTouchRay = Unproject(vScreenCoord, mView, mProjection, tViewport.v);
    CEventMgr::Instance()->OnEvent(CEventMgr::E_EVENT_TOUCH);

    std::cout<<"[CCollisionMgr] OnTouch Ray : "<<rayVector.x<<","<<rayVector.y<<","<<rayVector.z<<"\n";
}

bool CCollisionMgr::RayPlaneIntersection(CVector3d &vTrianglePoint_01, CVector3d &vTrianglePoint_02, CVector3d &vTrianglePoint_03, CRay3d& tRay, CVector3d *vIntersectPoint)
{
    CVector3d vEdge_01 = vTrianglePoint_02 - vTrianglePoint_01;
	CVector3d vEdge_02 = vTrianglePoint_03 - vTrianglePoint_01;
    
    CVector3d vNormal = Cross(vEdge_01, vEdge_02);
    vNormal.Normalize();
    
    CVector3d vOffset_01 = tRay.m_vOrigin - vTrianglePoint_01;
    CVector3d vOffset_02 = tRay.m_vEnd - vTrianglePoint_01;
    
    float fValue_01 = Dot(vOffset_01, vNormal);
    float fValue_02 = Dot(vOffset_02, vNormal);
    
    if((fValue_01 >= 0.0f && fValue_02 >= 0.0f) || (fValue_01 <= 0.0f && fValue_02 <= 0.0f))
    {
        return false;
    }
    *vIntersectPoint = (tRay.m_vEnd * fValue_01 - tRay.m_vOrigin * fValue_02) / (fValue_01 - fValue_02);
    return true;
}

bool CCollisionMgr::RayTriangleIntersection(CVector3d& vTrianglePoint_01, CVector3d& vTrianglePoint_02, CVector3d& vTrianglePoint_03, CRay3d& tRay, CVector3d* vIntersectPoint)
{
    CVector3d vEdge_01 = vTrianglePoint_02 - vTrianglePoint_01;
	CVector3d vEdge_02 = vTrianglePoint_03 - vTrianglePoint_01;
    
    CVector3d vPVector = Cross(tRay.m_vDirection, vEdge_02);
	float fDeterminant = Dot(vEdge_01, vPVector);
	if(fabs(fDeterminant) < 0.0001f) 
    {
        return false;
    }
    
    float fInvDeterminant = 1.0f / fDeterminant;
    
	CVector3d vTVector = tRay.m_vOrigin - vTrianglePoint_01;
	float fU = Dot(vTVector, vPVector) * fInvDeterminant;  
    if ( fU < -0.0001f || fU > 1.0001f )
    {
        return false;
    }
    
    CVector3d vQVector = Cross(vTVector, vEdge_01);
	float fV = Dot(tRay.m_vDirection, vQVector) * fInvDeterminant; 
	if ( fV < -0.0001f || (fV + fU) > 1.0001f )
    {
        return false;
    }

    //float fT = Dot(vEdge_02, vQVector) * fInvDeterminant; 
	*vIntersectPoint = vTrianglePoint_01 + (vEdge_01 * fU) + (vEdge_02 * fV);
	return true;
}

void CCollisionMgr::Update()
{
   /* glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    std::map<unsigned int,ICollider*>::iterator pBIterator = m_lContainer.begin();
    std::map<unsigned int,ICollider*>::iterator pEIterator = m_lContainer.end();
    
    while (pBIterator != pEIterator)
    {
        ICollider* pCollider = (*pBIterator).second;
        pCollider->Render();
        if(m_bIsTouch == true)
        {
            m_iHexColliderID = 0;
            pCollider->Set_TouchCollided(false);
        }
        ++pBIterator;
    }
    
    CSceneMgr::Instance()->Get_BatchMgr()->RenderColliderBatch();
    
    if(m_bIsTouch == true)
    {
        ICollider::SColliderID tTouchColliderID;
        unsigned char pColor[4];
        glReadPixels(static_cast<GLint>(m_vTouch2DPoint.x), static_cast<GLint>(m_vTouch2DPoint.y), 1, 1, GL_RGBA, GL_BYTE, &tTouchColliderID.v);
        
        CMatrix4x4 mView = CSceneMgr::Instance()->Get_Camera()->Get_View();
        CMatrix4x4 mProjection = CSceneMgr::Instance()->Get_Camera()->Get_Projection();
        CWindow::SViewport tViewport = CWindow::Get_Viewport();
        CVector3d vTouchPoint;
        
        //Retreiving position projected on near plan
        float fTouchZ = tTouchColliderID.v[0] / 255;
        gluUnProject( m_vTouch2DPoint.x, m_vTouch2DPoint.y , tTouchColliderID.v[0], mView.m, mProjection.m, tViewport.v, &vTouchPoint.x, &vTouchPoint.y, &vTouchPoint.z);
        std::cout<<"[CCollisionMgr] Depth : "<<fTouchZ<<"\n";
        std::cout<<"[CCollisionMgr] OnTouch Ray : "<<vTouchPoint.x<<","<<vTouchPoint.y<<","<<vTouchPoint.z<<"\n";
        m_vTouch3DPoint = vTouchPoint;
        CEventMgr::Instance()->OnEvent(CEventMgr::E_EVENT_TOUCH);

        //unsigned int iHexColliderID = RgbToHex(tTouchColliderID.r, tTouchColliderID.g, tTouchColliderID.b);
        //std::map<unsigned int,ICollider*>::iterator pIterator = m_lContainer.find(iHexColliderID);
        //if(pIterator != m_lContainer.end())
        //{
        //   ICollider* pCollider = (*pIterator).second;
        //   pCollider->Set_TouchCollided(true);
            
        //    m_iHexColliderID = iHexColliderID;
        //    CEventMgr::Instance()->OnEvent(CEventMgr::E_EVENT_TOUCH);
        //}
    }
    m_bIsTouch = false;
    glFlush();*/
}








