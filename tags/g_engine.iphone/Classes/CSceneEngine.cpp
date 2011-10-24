//
//  CSceneEngine.cpp
//  gEngine
//
//  Created by sergey.sergeev on 10/24/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CSceneEngine.h"

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
    
}

CSceneEngine::~CSceneEngine()
{
    
}

INode* CSceneEngine::AddNode(std::string _sName, float _fWidth, float _fHeight)
{
    CSprite *sprite = new CSprite();
    sprite->Load(_sName, _fWidth, _fHeight);
    m_source[_sName] = sprite;
    return sprite;
}

INode* CSceneEngine::AddNode(std::string _sName, INode *_node)
{
    m_source[_sName] = _node;
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



