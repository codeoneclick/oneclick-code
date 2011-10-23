#include "m3_BattleMachine.h"

m3_BattleMachine::m3_BattleMachine()
{
	aiBlock = new m3_Ai();
}

void m3_BattleMachine::Draw()
{
	Update();
	RenderChunk("_basis");

	Update();
	RenderChunk("_track_01");
	Update();
	RenderChunk("_track_02");

	vRotation.y = fTurretRotation;
	_textureAnimSpeed = 0.0f;
	Update();
	RenderChunk("_turret");
}
