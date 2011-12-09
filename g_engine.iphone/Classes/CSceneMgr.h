//
//  CSceneMgr.h
//  gEngine
//
//  Created by sergey.sergeev on 12/1/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CSceneMgr_h
#define gEngine_CSceneMgr_h

#include "INode.h"
#include "CLight.h"
#include "CBatch.h"

class CSceneMgr
{
public:
    enum E_BATCH { E_BATCH_INTERSECTOR = 0, E_BATCH_01, E_BATCH_02 };
    enum E_RENDER_STATE { E_RENDER_STATE_SCREEN = 0, E_RENDER_STATE_PICKER };
private:
    static CSceneMgr* m_pInsatnce;
    INode::SIntersectorID  m_tStoreIntersectorID;
    INode::SIntersectorID  m_tCurretIntersectorID;
    INode* m_pPicker;
    std::vector<INode*> m_lContainer;
    std::map<E_BATCH, CBatch*> m_lBatch;
    CLight* m_pLight;
public:
    CSceneMgr();
    ~CSceneMgr();
    static CSceneMgr* Instance();
    inline CLight* Get_Light() { return m_pLight; }
    inline INode*  Get_Picker() { return m_pPicker; }
    inline void Set_Picker(INode* _pNode) { m_pPicker = _pNode; }
    inline void Set_IntersectorID(INode::SIntersectorID _tIntersectorID) { m_tCurretIntersectorID = _tIntersectorID; }
    INode* AddNode(IResource::SResource _pResource);
    void RemoveNode(INode *_pNode);
    void PushToBatch(E_BATCH _eBatch, INode* _pNode);
    void Update(E_RENDER_STATE _eState, float _fTime);
    void Render();
};

#endif
