//
//  CCollisionMgr.h
//  gEngine
//
//  Created by sergey.sergeev on 1/10/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CCollisionMgr_h
#define gEngine_CCollisionMgr_h

#include "stdlib.h"
#include <vector>
#include <map>
#include "ICollider.h"

class CCollisionMgr
{
private:
    ICollider::SColliderID m_tLastColliderID;
    std::map<unsigned int, ICollider*> m_lContainer;
    static CCollisionMgr* m_pInstance;
    CVector2d m_vTouch2DPoint;
    CVector3d m_vTouch3DPoint;
    unsigned int m_iHexColliderID;
    bool m_bIsTouch;
    unsigned int RgbToHex(unsigned char _r, unsigned char _g, unsigned char _b);
public:
    CCollisionMgr();
    ~CCollisionMgr();
    
    static CCollisionMgr* Instance();
    void Create_Collider(ICollider* _pCollider);
    void Remove_Collider(ICollider* _pCollider);

    void OnScreenTouch(CVector2d _vTouchPoint) { m_bIsTouch = true; m_vTouch2DPoint = _vTouchPoint; }
    
    unsigned int Get_HexColliderID(void) { return m_iHexColliderID; }
    
    void Set_Touch3DPoint(CVector3d _vTouchPoint) { m_vTouch3DPoint = _vTouchPoint; }
    CVector3d Get_Touch3DPoint(void) { return m_vTouch3DPoint; }
   
    void Update(void);
};

#endif
