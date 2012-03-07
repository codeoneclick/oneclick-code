//
//  CBatchMgr.cpp
//  gEngine
//
//  Created by sergey.sergeev on 1/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include "CBatchMgr.h"

CBatchMgr::CBatchMgr()
{
    CBatch* pColliderBatch = new CBatch();
    CShader* pColliderShader = CShaderComposite::Instance()->Get_Shader(IResource::E_SHADER_COLOR);
    CTexture** pColliderTextures = new CTexture*[TEXTURES_MAX_COUNT];
    pColliderTextures[0] = NULL;
    pColliderTextures[1] = NULL;
    pColliderTextures[2] = NULL;
    pColliderTextures[3] = NULL;
    pColliderBatch->Set_Shader(pColliderShader);
    pColliderBatch->Set_Textures(pColliderTextures);
    pColliderBatch->Set_RenderMode(CBatch::E_RENDER_MODE_TRIANGLES);
    m_lContainer[BATCH_COLLIDER_BOX] = pColliderBatch;
    
    CBatch* pBoundingBatch = new CBatch();
    CShader* pBoundingShader = CShaderComposite::Instance()->Get_Shader(IResource::E_SHADER_COLOR);
    CTexture** pBoundingTextures = new CTexture*[TEXTURES_MAX_COUNT];
    pBoundingTextures[0] = NULL;
    pBoundingTextures[1] = NULL;
    pBoundingTextures[2] = NULL;
    pBoundingTextures[3] = NULL;
    pBoundingBatch->Set_Shader(pBoundingShader);
    pBoundingBatch->Set_Textures(pBoundingTextures);
    pBoundingBatch->Set_RenderMode(CBatch::E_RENDER_MODE_LINES);
    m_lContainer[BATCH_BOUNDING_BOX] = pBoundingBatch;
}

CBatchMgr::~CBatchMgr()
{
    
}

void CBatchMgr::PushToBoundingBatch(CBoundingBox* _pNode)
{
    CBatch* pBatch = m_lContainer[BATCH_BOUNDING_BOX];
    CBatch::SSource tSource(_pNode->Get_Mesh(), _pNode->Get_WorldMatrix());
    pBatch->Push(tSource);
}

void CBatchMgr::PushToColliderBatch(ICollider *_pNode)
{
    CBatch* pBatch = m_lContainer[BATCH_COLLIDER_BOX];
    CBatch::SSource tSource(_pNode->Get_Mesh(), _pNode->Get_WorldMatrix());
    pBatch->Push(tSource);
}

void CBatchMgr::PushToNodesBatch(INode *_pNode)
{
    
}

void CBatchMgr::RenderBoundingBatch()
{
    CBatch* pBatch = m_lContainer[BATCH_BOUNDING_BOX];
    pBatch->Render();
}

void CBatchMgr::RenderColliderBatch()
{
    CBatch* pBatch = m_lContainer[BATCH_COLLIDER_BOX];
    pBatch->Render();
}

void CBatchMgr::RenderNodesBatch()
{
    
}





