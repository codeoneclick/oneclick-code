//
//  CDSprite.cpp
//  gEngine
//
//  Created by sergey.sergeev on 10/27/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//
/*
#include <iostream>
#include "CDSprite.h"
#include "CPhysicController.h"

CDSprite::CDSprite()
{
    
}

CDSprite::~CDSprite()
{
    CPhysicController::Instance()->World()->DestroyBody(m_pBody);
    std::cout<<"[CDSprite] destructor().";
}

void CDSprite::Set_Position(Vector3d &_vPosition)
{
    m_vPosition = _vPosition;
    m_pBodyDef.position.Set(_vPosition.x, _vPosition.y);
}

void CDSprite::Set_Rotation(float _fRotation)
{
    m_fRotation = _fRotation;
    m_pBodyDef.angle = RadToDeg(_fRotation);
}

void CDSprite::Set_Scale(Vector2d &_vScale)
{
    m_vScale = _vScale;
}

void CDSprite::Load(CResource::SResource &_resource)
{
    CSprite::Load(_resource);
    //m_vb->Commit();
    m_pBodyDef.type = b2_dynamicBody;
    
	m_pBodyDef.position.Set(m_vPosition.x, m_vPosition.y);
	m_pBodyDef.userData = this;
    
	m_pBody = CPhysicController::Instance()->World()->CreateBody(&m_pBodyDef);
	b2PolygonShape dynamicBox;
    
	dynamicBox.SetAsBox(m_vSize.x / 2,m_vSize.y / 2);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 2.0f;
	fixtureDef.friction = 2.0f;
	fixtureDef.restitution = 0.7f; 
	m_pBody->CreateFixture(&fixtureDef);
	m_pBody->SetType(b2_dynamicBody);
}
*/
