//
//  CShootMgr.h
//  iGaia
//
//  Created by sergey sergeev on 5/25/12.
//
//

#ifndef __iGaia__CShootMgr__
#define __iGaia__CShootMgr__

#include <iostream>
#include "CBullet.h"

class CGameShooterMgr
{
protected:
    std::vector<CBullet*> m_lBulletsContainer;
public:
    CGameShooterMgr(void);
    ~CGameShooterMgr(void);
    
    void Update(void);
    void CreateBullet(const glm::vec3& _vStartPosition, const glm::vec3& _vEndPosition, const glm::vec3& _vRotation);
};

#endif /* defined(__iGaia__CShootMgr__) */
