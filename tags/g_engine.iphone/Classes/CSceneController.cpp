//
//  CSceneController.cpp
//  gEngine
//
//  Created by sergey.sergeev on 10/24/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CSceneController.h"
#include "CCamera.h"
#include "CPhysicController.h"

CSceneController* CSceneController::m_instance = NULL;

CSceneController* CSceneController::Instance()
{
    if(m_instance == NULL)
    {
        m_instance = new CSceneController();
    }
    
    return m_instance;
}

CSceneController::CSceneController()
{
        
}

CSceneController::~CSceneController()
{
    
}

INode* CSceneController::AddNode(CResourceController::SResource &_resource)
{
    INode* node = NULL;
    switch (_resource.s_tNode)
    {
        case CResourceController::SResource::SPRITE:
        {
            node = new CSprite();
            ((CSprite*)node)->Load(_resource);
        }
            break;
        case CResourceController::SResource::DSPRITE:
        {
            node = new CDSprite();
            ((CDSprite*)node)->Load(_resource);
        }
        default:
        {
            
        }
            break;
    }
    m_source[_resource.s_sName] = node;
       
    return node;
}

INode* CSceneController::AddNode(CResourceController::SResource &_resource, INode *_node)
{
    m_source[_resource.s_sName] = _node;
    return _node;
}

void CSceneController::RemoveNode(INode *_node)
{
    std::map<std::string, INode*>::iterator beginNodeIterator = m_source.begin();
    std::map<std::string, INode*>::iterator endNodeIterator = m_source.end();
    while( beginNodeIterator != endNodeIterator)
    {
        if((*beginNodeIterator).second == _node)
        {
            m_source.erase(beginNodeIterator);
            delete _node;
            _node = NULL;
            return;
        }
        ++beginNodeIterator;
    }
    std::cout<<"[CSceneController] Node not found.";
}

void CSceneController::RemoveNode(std::string _sName)
{
    std::map<std::string, INode*>::iterator nodeIterator = m_source.find(_sName);
    if(nodeIterator != m_source.end())
    {
        INode *node = (*nodeIterator).second;
        m_source.erase(nodeIterator);
        delete node;
        node = NULL;
        return;
    }
    std::cout<<"[CSceneController] Node not found.";
}

void CSceneController::Update(float _fTime)
{
    CCamera::Instance()->Update(_fTime);
    CPhysicController::Instance()->Update(_fTime);
    std::map<std::string, INode*>::iterator beginNodeIterator = m_source.begin();
    std::map<std::string, INode*>::iterator endNodeIterator = m_source.end();
    while( beginNodeIterator != endNodeIterator)
    {
        (*beginNodeIterator).second->Update(_fTime);
        ++beginNodeIterator;
    }
}

void CSceneController::Render()
{
    std::map<std::string, INode*>::iterator beginNodeIterator = m_source.begin();
    std::map<std::string, INode*>::iterator endNodeIterator = m_source.end();
    while( beginNodeIterator != endNodeIterator)
    {
        (*beginNodeIterator).second->Render();
        ++beginNodeIterator;
    }
}


