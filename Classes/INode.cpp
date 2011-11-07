//
//  INode.cpp
//  gEngine
//
//  Created by sergey.sergeev on 10/21/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "INode.h"

GLubyte* INode::m_pIb = new GLubyte[6];

INode::INode()
{
    m_mProjection = CCamera::Instance()->Projection();
    m_mView = CCamera::Instance()->View();
    
    m_vScale = Vector2d(1.0f,1.0f);
    m_fRotation = 0.0f;
    m_vPosition = Vector3d(0.0f, 0.0f, 0.0f);
    
    m_pVb = NULL; 
    m_pShader = NULL;
    m_pTexture = NULL;
    
    m_pParent = NULL;
    
    m_pIb[0] = 0;
    m_pIb[1] = 1;
    m_pIb[2] = 2;
    m_pIb[3] = 2;
    m_pIb[4] = 3;
    m_pIb[5] = 0;
}

INode::~INode()
{
    if(m_pVb != NULL)
    {
        delete m_pVb;
        m_pVb = NULL;
    }
    
    m_pTexture->Release();
    m_pTexture = NULL;
    std::cout<<"[INode](Destructor) Call.";
}


void INode::AddChild(INode *_pNode)
{
    if(_pNode->Get_Parent() == NULL)
    {
        _pNode->Set_Parent(this);
        m_lChilds.push_back(_pNode);
    }
    else
    {
        std::cout<<"[INode](AddChild) Can not add child with parent != NULL.";
    }
}

INode* INode::GetChildAt(unsigned int _index)
{
    if(_index < m_lChilds.size())
    {
        return m_lChilds[_index];
    }
    else
    {
        std::cout<<"[INode](GetChildAt) Child not found.";
        return NULL;
    }
}

void INode::RemoveChild(INode *_pNode)
{
    std::vector<INode*>::iterator pBNode = m_lChilds.begin();
    std::vector<INode*>::iterator pENode = m_lChilds.end();
    
    while (pBNode != pENode)
    {
        if(_pNode == (*pBNode))
        {
            m_lChilds.erase(pBNode);
            return;
        }
        ++pBNode;
    }
    std::cout<<"[INode](RemoveChild) Child not found.";
}

void INode::RemoveChildAt(unsigned int _index)
{
    if(_index < m_lChilds.size())
    {
        RemoveChild(m_lChilds[_index]);
    }
    else
    {
        std::cout<<"[INode](RemoveChild) Child not found.";
    }
}

void INode::RemoveChilds()
{
    m_lChilds.clear();
}

void INode::Load(INode::SResourceParam &_param)
{
    m_vSize = _param.m_vSize;
    m_vPosition = _param.m_vPosition;
    
    m_pVb = new CVertexBuffer(4, sizeof(CVertexBuffer::SVertexVTC), CVertexBuffer::VBD_V2FT2FC4F);
    CVertexBuffer::SVertexVTC *data = static_cast<CVertexBuffer::SVertexVTC*>(m_pVb->Data());  
    data[0].s_position = Vector3d(-m_vSize.x / 2, -m_vSize.y / 2, 0.0f);
    data[1].s_position = Vector3d(-m_vSize.x / 2, m_vSize.y  / 2, 0.0f);
    data[2].s_position = Vector3d(m_vSize.x  / 2, m_vSize.y  / 2, 0.0f);
    data[3].s_position = Vector3d(m_vSize.x  / 2, -m_vSize.y / 2, 0.0f);
    
    data[0].s_texcoord = Vector2d(0.0f, 0.0f);
    data[1].s_texcoord = Vector2d(0.0f, 1.0f);
    data[2].s_texcoord = Vector2d(1.0f, 1.0f);
    data[3].s_texcoord = Vector2d(1.0f, 0.0f);
    
    data[0].s_color = _param.m_vColor;
    data[1].s_color = _param.m_vColor;
    data[2].s_color = _param.m_vColor;
    data[3].s_color = _param.m_vColor;
}

void INode::Set_Color(Vector4d &_vColor)
{
    CVertexBuffer::SVertexVTC *data = static_cast<CVertexBuffer::SVertexVTC*>(m_pVb->Data());  
    data[0].s_color = _vColor;
    data[1].s_color = _vColor;
    data[2].s_color = _vColor;
    data[3].s_color = _vColor;
}

void INode::Update(float _fTime)
{
    m_mRotation = Rotation(m_fRotation);
    m_mTranslation = Translation(m_vPosition);
    m_mScale = Scale(m_vScale);
    m_mWorld = m_mScale * m_mRotation * m_mTranslation;
    
    if(m_pParent != NULL)
    {
        m_mWorld = m_mWorld * m_pParent->Get_WorldMatrix();
    }
    
    std::vector<INode*>::iterator pBNode = m_lChilds.begin();
    std::vector<INode*>::iterator pENode = m_lChilds.end();
    
    while (pBNode != pENode)
    {
        INode* pNode = (*pBNode);
        if(pNode != NULL)
        {
            pNode->Update(_fTime);
        }
        else
        {
            std::cout<<"[INode](Update) Critical warning node is NULL.";
        }
        ++pBNode;
    }
}

void INode::Render()
{  
    std::vector<INode*>::iterator pBNode = m_lChilds.begin();
    std::vector<INode*>::iterator pENode = m_lChilds.end();
    
    while (pBNode != pENode)
    {
        INode* pNode = (*pBNode);
        if(pNode != NULL)
        {
            pNode->Render();
        }
        else
        {
            std::cout<<"[INode](Render) Critical warning node is NULL.";
        }
        ++pBNode;
    }
}


