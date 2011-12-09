//
//  CPlayer.h
//  gEngine
//
//  Created by sergey.sergeev on 12/1/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef gEngine_CPlayer_h
#define gEngine_CPlayer_h

#include "IGameObject.h"
#include "CMovieModel.h"

class CPlayer : public IGameObject
{
public:
    enum E_PLAYER_STATE { E_PLAYER_STATE_IDLE = 0, E_PLAYER_STATE_PICK, E_PLAYER_STATE_MOVE, E_PLAYER_STATE_MOVE_END, E_PLAYER_STATE_ATTACK, E_PLAYER_STATE_ATTACK_END }; 
protected:
    INode* m_pModel;
    E_PLAYER_STATE m_eState;
public:
    CPlayer();
    virtual ~CPlayer();
    virtual void Load(std::vector<IResource::SResource> _lResource);
    virtual void Update(float _fTime);
    virtual bool IsPicker();
    inline E_PLAYER_STATE Get_State() { return m_eState; }
    inline void Set_State(E_PLAYER_STATE _eState) { m_eState = _eState; }
};

#endif
