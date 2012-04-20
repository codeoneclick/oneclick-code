//
//  CPhysicMgr.h
//  iGaia
//
//  Created by code_oneclick on 4/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CPhysicMgr_h
#define iGaia_CPhysicMgr_h

class btVehicleTuning;
struct btVehicleRaycaster;
class btCollisionShape;

#include "btRaycastVehicle.h"
#include "INode.h"

class CPhysicMgr
{
protected:
    std::vector<INode*> m_lContainer;
    
    class btDefaultCollisionConfiguration* m_pCollisionConfiguration;
    class btCollisionDispatcher*           m_pDispatcher;
    class btBroadphaseInterface*           m_pOverlappingPairCache;
    class btConstraintSolver*              m_pConstraintSolver;
    class btDiscreteDynamicsWorld*         m_pDynamicsWorld;
public:
    CPhysicMgr(void);
    ~CPhysicMgr(void);
    void Add_CollisionModel(INode* _pNode, float _fMass, glm::vec3 _vOrigin);
    void Add_CollisionLandscape(INode* _pNode);
    void Add_CollisionModelAsVehicle(INode* _pNode, float _fMass, glm::vec3 _vOrigin);
    void Add_WheelToVehicleModel(INode* _pNode, glm::vec3 _vConnectionPoint);
    void Update(void);
};

#endif
