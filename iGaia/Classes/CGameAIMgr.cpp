//
//  CGameAIMgr.cpp
//  iGaia
//
//  Created by code_oneclick on 4/20/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "CGameAIMgr.h"
#include "CWorld.h"

CGameAIMgr::CGameAIMgr(void)
{
    srand(time(NULL));
}

CGameAIMgr::~CGameAIMgr(void)
{
    
}

void CGameAIMgr::Add_AICharacterController(ICharacterController *_pCharacterController)
{
    m_lContainer.push_back(static_cast<CCharacterControllerEnemy*>(_pCharacterController));
}

void CGameAIMgr::Remove_AICharacterController(ICharacterController *_pCharacterController)
{
    
}

float CGameAIMgr::_Get_RandomFromRange(float _fMin, float _fMax)
{
    float fRange = _fMax - _fMin;
    return _fMin + float(fRange * rand() / (RAND_MAX + 1.0f)); 
}

glm::vec2 CGameAIMgr::_GenerateMovePoint(void)
{
    float fRandPositionX = _Get_RandomFromRange(1.0f, 31.0f);
    float fRandPositionZ = _Get_RandomFromRange(1.0f, 31.0f);
    return glm::vec2(fRandPositionX, fRandPositionZ);
}

void CGameAIMgr::Update(void)
{
    std::vector<CCharacterControllerEnemy*>::iterator pBeginIterator = m_lContainer.begin();
    std::vector<CCharacterControllerEnemy*>::iterator pEndIterator = m_lContainer.end();
    
    while (pBeginIterator != pEndIterator)
    {
        CCharacterControllerEnemy::E_AI_STATE eState = (*pBeginIterator)->Get_AIState();
        if(eState == CCharacterControllerEnemy::E_AI_STATE_NONE)
        {
            (*pBeginIterator)->Set_AIState(CCharacterControllerEnemy::E_AI_STATE_MOVE, 0);
            glm::vec2 vGeneratedPoint = _GenerateMovePoint();
            (*pBeginIterator)->Set_AITargetPoint(glm::vec3(vGeneratedPoint.x, 0.0f, vGeneratedPoint.y));
        }
        ++pBeginIterator;
    }
}




