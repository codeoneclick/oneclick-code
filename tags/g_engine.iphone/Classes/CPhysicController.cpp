//
//  CPhysicController.cpp
//  gEngine
//
//  Created by sergey.sergeev on 10/27/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CPhysicController.h"

CPhysicController* CPhysicController::m_controller = NULL;

CPhysicController::CPhysicController()
{
    float fWidth = CCamera::Instance()->Get_Width();
    float fHeight = CCamera::Instance()->Get_Height();
	b2Vec2 vGravity = b2Vec2(0.0f,-9.8f);
    
	m_pWorld = new b2World(vGravity);
	m_pWorld->SetContinuousPhysics(true);
    
	b2BodyDef boundBodyDef;
	boundBodyDef.position.Set(0, 0);
	b2Body* boundBody = m_pWorld->CreateBody(&boundBodyDef);

	b2EdgeShape boundBox;
    
	boundBox.Set(b2Vec2(-fWidth / 2, -fHeight / 2), b2Vec2(fWidth / 2, -fHeight / 2));
	boundBody->CreateFixture(&boundBox, 0);
    

	boundBox.Set(b2Vec2(-fWidth / 2, fHeight / 2), b2Vec2(fWidth / 2, fHeight / 2));
	boundBody->CreateFixture(&boundBox, 0);
    

	boundBox.Set(b2Vec2(-fWidth / 2, fHeight / 2), b2Vec2(-fWidth / 2, -fHeight / 2));
	boundBody->CreateFixture(&boundBox, 0);
    

	boundBox.Set(b2Vec2(fWidth / 2, fHeight / 2), b2Vec2(fWidth / 2, -fHeight / 2));
	boundBody->CreateFixture(&boundBox, 0);
}

CPhysicController::~CPhysicController()
{
    
}

CPhysicController* CPhysicController::Instance()
{
    if(m_controller == NULL)
    {
        m_controller = new CPhysicController();
    }
    
    return m_controller;
}

void CPhysicController::Update(float _fTime)
{
    int32 velocityIterations = 8;
	int32 positionIterations = 1;
    
	m_pWorld->Step(1.0f/60.0f, velocityIterations, positionIterations);
    
	//Iterate over the bodies in the physics world
	for (b2Body* b = m_pWorld->GetBodyList(); b; b = b->GetNext())
	{
		if (b->GetUserData() != NULL)
		{
			INode *node = (INode *)b->GetUserData();
            Vector3d vPosition = Vector3d(b->GetPosition().x,b->GetPosition().y, 0.0f);
            node->Set_Position(vPosition);
            node->Set_Rotation(RadToDeg(b->GetAngle()));
		}
	}

}