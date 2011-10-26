//
//  CSceneEngine.cpp
//  gEngine
//
//  Created by sergey.sergeev on 10/24/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CSceneEngine.h"
#include "CCamera.h"

CSceneEngine* CSceneEngine::m_engine = NULL;

CSceneEngine* CSceneEngine::Instance()
{
    if(m_engine == NULL)
    {
        m_engine = new CSceneEngine();
    }
    
    return m_engine;
}

CSceneEngine::CSceneEngine()
{
    float fWidth = CCamera::Instance()->Get_Height() / 2;
    float fHeight = CCamera::Instance()->Get_Width() / 2;
	b2Vec2 gravity;
	gravity.Set(0.0f, -9.8f);
    
	// Construct a world object, which will hold and simulate the rigid bodies.
	m_pPhysicWorldController = new b2World(gravity);
    
	m_pPhysicWorldController->SetContinuousPhysics(true);
    
	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0); // bottom-left corner
    
	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = m_pPhysicWorldController->CreateBody(&groundBodyDef);
    
	// Define the ground box shape.
	b2EdgeShape groundBox;
    
	// bottom
	groundBox.Set(b2Vec2(0,0), b2Vec2(fWidth,0));
	groundBody->CreateFixture(&groundBox, 0);
    
	// top
	groundBox.Set(b2Vec2(0,fHeight), b2Vec2(fWidth,fHeight));
	groundBody->CreateFixture(&groundBox, 0);
    
	// left
	groundBox.Set(b2Vec2(0,fHeight), b2Vec2(0,0));
	groundBody->CreateFixture(&groundBox, 0);
    
	// right
	groundBox.Set(b2Vec2(fWidth,fHeight), b2Vec2(fWidth,0));
	groundBody->CreateFixture(&groundBox, 0);
}

CSceneEngine::~CSceneEngine()
{
    
}

INode* CSceneEngine::AddNode(CResourceController::SResource &_resource)
{
    CSprite *sprite = new CSprite();
    sprite->Load(_resource);
    m_source[_resource.sName] = sprite;
    
    b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
    
	bodyDef.position.Set(0.0f, 0.0f);
	bodyDef.userData = sprite;
    
	// Tell the physics world to create the body
	b2Body *body = m_pPhysicWorldController->CreateBody(&bodyDef);
    
	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
    
	dynamicBox.SetAsBox(_resource.vSize.x, _resource.vSize.y);
    
	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 3.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.5f; // 0 is a lead ball, 1 is a super bouncy ball
	body->CreateFixture(&fixtureDef);
    
	// a dynamic body reacts to forces right away
	body->SetType(b2_dynamicBody);
    
    return sprite;
}

INode* CSceneEngine::AddNode(CResourceController::SResource &_resource, INode *_node)
{
    m_source[_resource.sName] = _node;
    return _node;
}

void CSceneEngine::Update(float _fTime)
{
    
    int32 velocityIterations = 8;
	int32 positionIterations = 1;
    
	// Instruct the world to perform a single step of simulation. It is
	// generally best to keep the time step and iterations fixed.
	m_pPhysicWorldController->Step(1.0f/60.0f, velocityIterations, positionIterations);
    
	//Iterate over the bodies in the physics world
	for (b2Body* b = m_pPhysicWorldController->GetBodyList(); b; b = b->GetNext())
	{
		if (b->GetUserData() != NULL)
		{
			CSprite *sprite = (CSprite *)b->GetUserData();
            
            sprite->m_vPosition.x = b->GetPosition().x;
            sprite->m_vPosition.y = b->GetPosition().y;
		}
	}
    std::map<std::string, INode*>::iterator beginNodeIterator = m_source.begin();
    std::map<std::string, INode*>::iterator endNodeIterator = m_source.end();
    while( beginNodeIterator != endNodeIterator)
    {
        (*beginNodeIterator).second->Update(_fTime);
        ++beginNodeIterator;
    }
}

void CSceneEngine::Render()
{
    std::map<std::string, INode*>::iterator beginNodeIterator = m_source.begin();
    std::map<std::string, INode*>::iterator endNodeIterator = m_source.end();
    while( beginNodeIterator != endNodeIterator)
    {
        (*beginNodeIterator).second->Render();
        ++beginNodeIterator;
    }
}



