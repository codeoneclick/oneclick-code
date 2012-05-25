//
//  CGameShooterMgr.cpp
//  iGaia
//
//  Created by sergey sergeev on 5/25/12.
//
//

#include "CGameShooterMgr.h"

CGameShooterMgr::CGameShooterMgr(void)
{
    
}

CGameShooterMgr::~CGameShooterMgr(void)
{
    
}

void CGameShooterMgr::CreateBullet(const glm::vec3 &_vStartPosition, const glm::vec3 &_vEndPosition, const glm::vec3 &_vRotation)
{
    CBullet* pBullet = new CBullet();
    pBullet->Load();
    pBullet->Set_StartPoint(_vStartPosition);
    pBullet->Set_EndPoint(_vEndPosition);
    pBullet->Set_Position(_vStartPosition);
    pBullet->Set_Rotation(_vRotation);
    m_lBulletsContainer.push_back(pBullet);
}

void CGameShooterMgr::Update(void)
{
    std::vector<CBullet*>::iterator pBeginBulletIterator = m_lBulletsContainer.begin();
    std::vector<CBullet*>::iterator pEndBulletIterator = m_lBulletsContainer.end();
    while (pBeginBulletIterator != pEndBulletIterator)
    {
        (*pBeginBulletIterator)->Update();
        ++pBeginBulletIterator;
    }
}