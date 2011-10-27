//
//  CDSprite.cpp
//  gEngine
//
//  Created by sergey.sergeev on 10/27/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CDSprite.h"
#include "CPhysicController.h"

CDSprite::CDSprite()
{
    
}

CDSprite::~CDSprite()
{
    
}

void CDSprite::Set_Position(Vector3d &_vPosition)
{
    m_vPosition = _vPosition;
    m_physicBody.position.Set(_vPosition.x, _vPosition.y);
}

void CDSprite::Set_Rotation(float _fRotation)
{
    m_fRotation = _fRotation;
    m_physicBody.angle = RadToDeg(_fRotation);
}

void CDSprite::Set_Scale(Vector2d &_vScale)
{
    m_vScale = _vScale;
}


void CDSprite::Load(CResourceController::SResource &_resource)
{
    CSprite::Load(_resource);
    
    m_physicBody.type = b2_dynamicBody;
    
	m_physicBody.position.Set(m_vPosition.x, m_vPosition.y);
	m_physicBody.userData = this;
    
	b2Body *body = CPhysicController::Instance()->World()->CreateBody(&m_physicBody);
	b2PolygonShape dynamicBox;
    
	dynamicBox.SetAsBox(m_fWidth / 2,m_fHeight / 2);
    
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 3.0f;
	fixtureDef.friction = 0.3f;
	fixtureDef.restitution = 0.5f; 
	body->CreateFixture(&fixtureDef);
	body->SetType(b2_dynamicBody);
}

