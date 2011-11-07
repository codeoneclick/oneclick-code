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

INode* CSceneController::AddNode(INode::SResourceParam &_param)
{
    INode* node = NULL;
    switch (_param.m_eNode)
    {
        case INode::E_SHAPE:
        {
            node = new CShape();
            ((CShape*)node)->Load(_param);
        }
            break;
        case INode::E_SPRITE:
        {
            node = new CSprite();
            ((CSprite*)node)->Load(_param);
        }
            break;
        case INode::E_MOVIECLIP:
        {
            node = new CMovieClip();
            ((CMovieClip*)node)->Load(_param);
        }
            break;
        default:
        {
            
        }
            break;
    }
    m_source[_param.m_sName] = node;
       
    return node;
}

INode* CSceneController::AddNode(INode::SResourceParam &_param, INode *_node)
{
    INode* node = NULL;
    switch (_param.m_eNode)
    {
        case INode::E_SHAPE:
        {
            node = new CShape();
            ((CShape*)node)->Load(_param);
        }
            break;
        case INode::E_SPRITE:
        {
            node = new CSprite();
            ((CSprite*)node)->Load(_param);
        }
            break;
        case INode::E_MOVIECLIP:
        {
            node = new CMovieClip();
            ((CMovieClip*)node)->Load(_param);
        }
            break;
        default:
        {
            
        }
            break;
    }
    m_source[_param.m_sName] = node;
    _node->AddChild(node);
    return _node;
}

void CSceneController::RemoveNode(INode *_node)
{
    std::map<std::string, INode*>::iterator pBNode = m_source.begin();
    std::map<std::string, INode*>::iterator pENode = m_source.end();
    while( pBNode != pENode)
    {
        if((*pBNode).second == _node)
        {
            m_source.erase(pBNode);
            std::vector<INode*> lChilds = _node->Get_Childs();
            std::vector<INode*>::iterator pBNodeChild = lChilds.begin();
            std::vector<INode*>::iterator pENodeChild = lChilds.end();
            
            while (pBNodeChild != pENodeChild)
            {
                this->RemoveNode((*pBNodeChild));
                ++pBNodeChild;
            }

            delete _node;
            _node = NULL;
            return;
        }
        ++pBNode;
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
        std::vector<INode*> lChilds = node->Get_Childs();
        std::vector<INode*>::iterator pBNodeChild = lChilds.begin();
        std::vector<INode*>::iterator pENodeChild = lChilds.end();
        
        while (pBNodeChild != pENodeChild)
        {
            this->RemoveNode((*pBNodeChild));
            ++pBNodeChild;
        }

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



