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
    float fWidth = CCamera::Instance()->Get_Width();
    float fHeight = CCamera::Instance()->Get_Height();
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
    return sprite;
}

INode* CSceneEngine::AddNode(CResourceController::SResource &_resource, INode *_node)
{
    m_source[_resource.sName] = _node;
    return _node;
}

void CSceneEngine::Update(float _fTime)
{
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



