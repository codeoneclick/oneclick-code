//
//  CSceneMgr.cpp
//  gEngine
//
//  Created by sergey.sergeev on 12/1/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CSceneMgr.h"
#include "CModel.h"
#include "CMovieModel.h"
#include "CRenderMgr.h"

CSceneMgr* CSceneMgr::m_pInsatnce = NULL;

CSceneMgr::CSceneMgr()
{
    m_pLight = new CLight();
    m_pPicker = NULL;
    
    m_lBatch[E_BATCH_INTERSECTOR] = new CBatch();
    m_lBatch[E_BATCH_01] = new CBatch();
    m_lBatch[E_BATCH_02] = new CBatch();
}

CSceneMgr::~CSceneMgr()
{
    
}

CSceneMgr* CSceneMgr::Instance()
{
    if( m_pInsatnce == NULL)
    {
        m_pInsatnce = new CSceneMgr();
    }    
    return m_pInsatnce;
}

INode* CSceneMgr::AddNode(IResource::SResource _pResource)
{
    INode* pNode = NULL;
    switch (_pResource.m_eMesh) 
    {
        case IResource::E_MESH_PRIMITIVE:
        case IResource::E_MESH_STATIC:
            pNode = new CModel();
            pNode->Load(_pResource);
            break;
        
        case IResource::E_MESH_MOVIE:
            pNode = new CMovieModel();
            pNode->Load(_pResource);
            break;
            
        default:
            break;
    }
    
    if(_pResource.m_eIntersector != IResource::E_INTERSECTOR_NONE)
    {
        if(m_tStoreIntersectorID.r < 255)
        {
            m_tStoreIntersectorID.r++;
        }
        else if(m_tStoreIntersectorID.g < 255)
        {
            m_tStoreIntersectorID.g++;
        }
        else if(m_tStoreIntersectorID.b < 255)
        {
            m_tStoreIntersectorID.b++;
        }
        pNode->Set_IntersectorID(m_tStoreIntersectorID);
    }
       
    m_lContainer.push_back(pNode);
    return pNode;
}

void CSceneMgr::PushToBatch(CSceneMgr::E_BATCH _eBatch, INode* _pNode)
{
    CBatch* pBatch = m_lBatch[_eBatch];
    pBatch->Push(_pNode);
}

void CSceneMgr::RemoveNode(INode *_pNode)
{
    
}

void CSceneMgr::Update(E_RENDER_STATE _eState, float _fTime)
{
    switch (_eState)
    {
        case CSceneMgr::E_RENDER_STATE_SCREEN:
        {
            std::vector<INode*>::iterator pBIterator = m_lContainer.begin();
            std::vector<INode*>::iterator pEIterator = m_lContainer.end();
            
            while (pBIterator != pEIterator)
            {
                (*pBIterator)->Update(_fTime);
                ++pBIterator;
            }
            
            static float fLightAngle = 0.0f;
            fLightAngle += 0.1f;
            m_pLight->Set_Rotation(Vector3d(0.0f, fLightAngle, 0.0f));
            m_pLight->Update();
        }
            break;
        case CSceneMgr::E_RENDER_STATE_PICKER:
        {
            std::vector<INode*>::iterator pBIterator = m_lContainer.begin();
            std::vector<INode*>::iterator pEIterator = m_lContainer.end();
            
            while (pBIterator != pEIterator)
            {
                INode* pNode =  (*pBIterator);
                INode::SIntersectorID tIntersectorID = pNode->Get_IntersectorID();
                //pNode->Intersect(false);
                if((tIntersectorID.r == m_tCurretIntersectorID.r) && (tIntersectorID.g == m_tCurretIntersectorID.g) && (tIntersectorID.b == m_tCurretIntersectorID.b))
                {
                    m_pPicker = pNode;
                    m_pPicker->Intersect(true);
                }
                ++pBIterator;
            }
        }
            break;
        default:
            break;
    }
}

void CSceneMgr::Render()
{
    std::map<E_BATCH, CBatch*>::iterator itBegin = m_lBatch.begin();
    std::map<E_BATCH, CBatch*>::iterator itEnd = m_lBatch.end();
    
    while (itBegin != itEnd)
    {
        (*itBegin).second->Clear();
        itBegin++;
    }
    
    std::vector<INode*>::iterator pBIterator = m_lContainer.begin();
    std::vector<INode*>::iterator pEIterator = m_lContainer.end();
    
    while (pBIterator != pEIterator)
    {
        (*pBIterator)->Render();
        ++pBIterator;
    }
    
    itBegin = m_lBatch.begin();
    itEnd = m_lBatch.end();
    
    while (itBegin != itEnd)
    {
        (*itBegin).second->Render();
        itBegin++;
    }

}

