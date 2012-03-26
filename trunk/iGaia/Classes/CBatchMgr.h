//
//  CBatchMgr.h
//  iGaia
//
//  Created by sergey.sergeev on 1/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef iGaia_CBatchMgr_h
#define iGaia_CBatchMgr_h

#include "CBatch.h"
#include "CBoundingBox.h"

#define BATCH_COLLIDER_BOX 0
#define BATCH_BOUNDING_BOX 1

class CBatchMgr
{
private:
    std::map<int, CBatch*> m_lContainer;
public:
    CBatchMgr();
    ~CBatchMgr();
    
    void PushToBoundingBatch(CBoundingBox* _pNode);
    void PushToNodesBatch(INode* _pNode);
    
    void RenderColliderBatch(void);
    void RenderBoundingBatch(void);
    void RenderNodesBatch(void);
};

#endif
