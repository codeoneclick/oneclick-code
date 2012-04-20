//
//  CPhysicMgr.cpp
//  iGaia
//
//  Created by code_oneclick on 4/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "CPhysicMgr.h"
#include "btDefaultCollisionConfiguration.h"
#include "btCollisionDispatcher.h"
#include "btAxisSweep3.h"
#include "btDiscreteDynamicsWorld.h"
#include "btSequentialImpulseConstraintSolver.h"
#include "btBoxShape.h"
#include "btTriangleIndexVertexArray.h"
#include "btBvhTriangleMeshShape.h"
#include "btDefaultMotionState.h"
#include "btCompoundShape.h"
#include "btRaycastVehicle.h"
#include "CSceneMgr.h"
#include <cmath>

CPhysicMgr::CPhysicMgr(void)
{
    m_pCollisionConfiguration = new btDefaultCollisionConfiguration();
	m_pDispatcher = new btCollisionDispatcher(m_pCollisionConfiguration);
	btVector3 vWorldMin(-1000.0f, -1000.0f, -1000.0f);
	btVector3 vWorldMax( 1000.0f,  1000.0f,  1000.0f);
	m_pOverlappingPairCache = new btAxisSweep3(vWorldMin, vWorldMax);
	m_pConstraintSolver = new btSequentialImpulseConstraintSolver();
	m_pDynamicsWorld = new btDiscreteDynamicsWorld(m_pDispatcher,m_pOverlappingPairCache,m_pConstraintSolver,m_pCollisionConfiguration);
}

CPhysicMgr::~CPhysicMgr(void)
{
    
}

void CPhysicMgr::Add_CollisionModel(INode *_pNode, float _fMass, glm::vec3 _vOrigin)
{
    btCollisionShape* pModelShape = new btBoxShape(btVector3(1.0f,0.5f,1.0f));
	btCompoundShape* pModelCompound = new btCompoundShape();
	btTransform mTransform;
	mTransform.setIdentity();
	mTransform.setOrigin(btVector3(0.0f,1.0f,0.0f));
	pModelCompound->addChildShape(mTransform,pModelShape);
	mTransform.setOrigin(btVector3(_vOrigin.x, _vOrigin.y, _vOrigin.z));
    
	btVector3 vLocalInertia(0.0f,0.0f,0.0f);
    pModelCompound->calculateLocalInertia(_fMass,vLocalInertia);
	btDefaultMotionState* pMotionState = new btDefaultMotionState(mTransform);
	btRigidBody::btRigidBodyConstructionInfo cInfo(_fMass,pMotionState,pModelCompound,vLocalInertia);
	btRigidBody* pBody = new btRigidBody(cInfo);
    btScalar defaultContactProcessingThreshold(BT_LARGE_FLOAT);
	pBody->setContactProcessingThreshold(defaultContactProcessingThreshold);
	m_pDynamicsWorld->addRigidBody(pBody);
    m_lContainer.push_back(_pNode);
    _pNode->Set_RigidBody(pBody);
}

void CPhysicMgr::Add_CollisionModelAsVehicle(INode *_pNode, float _fMass, glm::vec3 _vOrigin)
{
    Add_CollisionModel(_pNode, _fMass, _vOrigin);
    btDefaultVehicleRaycaster* pDefaultVehicleRaycaster = new btDefaultVehicleRaycaster(m_pDynamicsWorld);
    btRaycastVehicle::btVehicleTuning pTuning;
    btRaycastVehicle* pRaycastVehicle = new btRaycastVehicle(pTuning, _pNode->Get_RigidBody(), pDefaultVehicleRaycaster);
    _pNode->Get_RigidBody()->setActivationState(DISABLE_DEACTIVATION);
    m_pDynamicsWorld->addVehicle(pRaycastVehicle);
    pRaycastVehicle->setCoordinateSystem(0, 1, 2);
    _pNode->Set_RaycastVehicle(pRaycastVehicle);
}

void CPhysicMgr::Add_CollisionLandscape(INode *_pNode)
{
    btCollisionShape* pLandscapeCollisionShape = new btBoxShape(btVector3(32,8,32));
    
	int iVertexStride = sizeof(btVector3);
	int iIndexStride = 3 * sizeof(int);
    
    int iWidth = 32;
    int iHeight = 32;
    const int iTotalVertices = iWidth * iHeight;
    const int iTotalTriangles = 2 * (iWidth - 1) * (iHeight - 1);
    
	btVector3 *pVertices = new btVector3[iTotalVertices];
	int* pIndices = new int[iTotalTriangles * 3];
    
    float* pMapData = CSceneMgr::Instance()->Get_HeightMapSetterRef()->Get_HeightMapData();
    
	for (int i = 0; i < iWidth; i++)
	{
		for (int j = 0; j < iHeight; j++)
		{
			float fHeight = pMapData[i + j * iHeight];
			pVertices[i + j * iWidth].setValue(static_cast<float>(i), fHeight, static_cast<float>(j));
		}
	}

	int index = 0;
	for (int i=0; i < iWidth - 1; i++)
	{
		for (int j=0; j < iHeight - 1; j++)
		{
			pIndices[index++] = j * iWidth + i;
			pIndices[index++] = j * iWidth + i + 1;
			pIndices[index++] = (j + 1) * iWidth + i + 1;
            
			pIndices[index++] = j * iWidth + i;
			pIndices[index++] = (j + 1) * iWidth + i + 1;
			pIndices[index++] = (j + 1) * iWidth + i;
		}
	}
	
	btTriangleIndexVertexArray *pIndexVertexArrays = new btTriangleIndexVertexArray(iTotalTriangles,
                                                         pIndices,
                                                         iIndexStride,
                                                         iTotalVertices,(btScalar*) &pVertices[0].x(),iVertexStride);
    pLandscapeCollisionShape = new btBvhTriangleMeshShape(pIndexVertexArrays,true);
    
	btVector3 vLocalInertia(0.0f, 0.0f, 0.0f);
    btTransform mTransform;
    mTransform.setIdentity();
    mTransform.setOrigin(btVector3(0.0f, 0.0f, 0.0f));

	btDefaultMotionState* pMotionState = new btDefaultMotionState(mTransform);
    
	btRigidBody::btRigidBodyConstructionInfo cInfo(0.0f, pMotionState, pLandscapeCollisionShape, vLocalInertia);
	btRigidBody* pBody = new btRigidBody(cInfo);
    btScalar defaultContactProcessingThreshold(BT_LARGE_FLOAT);
	pBody->setContactProcessingThreshold(defaultContactProcessingThreshold);
	m_pDynamicsWorld->addRigidBody(pBody);
    m_lContainer.push_back(_pNode);
    _pNode->Set_RigidBody(pBody);
}

void CPhysicMgr::Add_WheelToVehicleModel(INode *_pNode, glm::vec3 _vConnectionPoint)
{
    std::vector<INode*>::iterator pBeignIterator = m_lContainer.begin();
    std::vector<INode*>::iterator pEndIterator = m_lContainer.end();
    
    while (pBeignIterator != pEndIterator)
    {
        btRaycastVehicle* pVehicle = (*pBeignIterator)->Get_RaycastVehicle();
        if(pVehicle == NULL)
        {
            ++pBeignIterator;
            continue;
        }
        
        if((*pBeignIterator) == _pNode)
        {
            btRaycastVehicle::btVehicleTuning pTuning = (*pBeignIterator)->Get_RigidBodyTuning();
            btVector3 vConnectionPointCSO(_vConnectionPoint.x, _vConnectionPoint.y, _vConnectionPoint.z);
            pVehicle->addWheel(vConnectionPointCSO, btVector3(0.0f, -1.0f, 0.0f), btVector3(-1.0f, 0.0f, 0.0f), 0.5f, 0.5f, pTuning, true);
            btWheelInfo& pWheelInfo = pVehicle->getWheelInfo(pVehicle->getNumWheels() - 1);
            pWheelInfo.m_suspensionStiffness = 10.0f;
            pWheelInfo.m_wheelsDampingRelaxation = 0.5f;
            pWheelInfo.m_wheelsDampingCompression = 0.3f;
            pWheelInfo.m_frictionSlip = 0.8f;
            pWheelInfo.m_rollInfluence = 0.1f;
        }
        ++pBeignIterator;
    }
}

void CPhysicMgr::Update(void)
{
    m_pDynamicsWorld->stepSimulation(1.0f / 60.f);
    
    std::vector<INode*>::iterator pBeignIterator = m_lContainer.begin();
    std::vector<INode*>::iterator pEndIterator = m_lContainer.end();
    
    while (pBeignIterator != pEndIterator)
    {
       
        btRigidBody* pBody = (*pBeignIterator)->Get_RigidBody();
        if(pBody == NULL)
        {
            ++pBeignIterator;
            continue;
        }
        btTransform mTransform;
        pBody->getMotionState()->getWorldTransform(mTransform);
        
        //std::cout << "[CPhysicMgr::Update] m_pTestBody position: "<<mTransform.getOrigin().getX()<<" , "<<mTransform.getOrigin().getY()<<" , "<<mTransform.getOrigin().getZ()<< std::endl;
        glm::vec3 vPosition = glm::vec3(mTransform.getOrigin().getX(), mTransform.getOrigin().getY(), mTransform.getOrigin().getZ());
        
        btMatrix3x3 mRotation;
        mRotation.setIdentity();
        mRotation = mTransform.getBasis();
        glm::vec3 vRotation;
        mRotation.getEulerZYX(vRotation.z, vRotation.y, vRotation.x);
        vRotation.x = glm::degrees(vRotation.x);
        vRotation.y = glm::degrees(vRotation.y);
        vRotation.z = glm::degrees(vRotation.z);
        
        (*pBeignIterator)->OnPhysicEventUpdate(vPosition, vRotation, glm::vec3(1.0f, 1.0f, 1.0f));
    
        //std::cout << "[CPhysicMgr::Update] m_pTestBody rotation: "<<vRotation.x<<" , "<<vRotation.y<<" , "<<vRotation.z<< std::endl;
        
        ++pBeignIterator;
    }
}











