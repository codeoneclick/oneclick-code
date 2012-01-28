//
//  CBatchMgr.h
//  gEngine
//
//  Created by sergey.sergeev on 1/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CBatchMgr_h
#define gEngine_CBatchMgr_h

#include "CBatch.h"
#include "CBoundingBox.h"
#include "ICollider.h"

#define BATCH_COLLIDER_BOX 0
#define BATCH_BOUNDING_BOX 1

class CBatchMgr
{
private:
    static CBatchMgr* m_pInstance;
    std::map<int, CBatch*> m_lContainer;
public:
    static CBatchMgr* Instance();
    CBatchMgr();
    ~CBatchMgr();
    
    void PushToColliderBatch(ICollider* _pNode);
    void PushToBoundingBatch(CBoundingBox* _pNode);
    void PushToNodesBatch(INode* _pNode);
    
    void RenderColliderBatch(void);
    void RenderBoundingBatch(void);
    void RenderNodesBatch(void);
};

#endif
