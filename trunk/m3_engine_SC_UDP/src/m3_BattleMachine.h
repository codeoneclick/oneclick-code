#pragma once
#ifndef _M3_BATTLEMACHINE_H_
#define _M3_BATTLEMACHINE_H_

#include "m3_Mesh.h"
#include "m3_Util.h"
#include "m3_Ai.h"

class m3_BattleMachine : public m3_Mesh
{
	private :

	public :
		m3_BattleMachine();
		float fTurretRotation;
		void Draw();
		m3_Ai *aiBlock;
		bool isAi;
};

#endif