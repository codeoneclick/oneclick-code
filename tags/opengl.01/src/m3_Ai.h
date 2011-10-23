#pragma once
#ifndef _M3_AI_H_
#define _M3_AI_H_
#include "Vector3d.h"
#include "m3_Util.h"

enum AI_STATE { AI_STAND = 0, AI_MOVE, AI_CHASE, AI_MOVEBACK, AI_ATTACK, AI_DISABLE }; 
enum TIME_STATE { TIME_STAND = 0, TIME_MOVE };

class m3_Ai
{
protected :
	AI_STATE _aiState;
	TIME_STATE _timeState;
	DWORD _lastTimeValue;
	Vector3d _vMovePoint;
	Vector3d _vMainPosition;
	Vector3d _vTargetPosition;
	DWORD _timeStateDuration;
	float _moveSpeed;
	bool _IsTimeOver(DWORD _timeDuration);
	void _GenerateTimeState();
	void _GenerateMovePoint();
	void _UpdateMainPosition(Vector3d _targetPointPosition, float _distance);
public :
	m3_Ai();
	void UpdateAI();
	__forceinline void SetMainPosition(Vector3d vPosition) { _vMainPosition = vPosition; }
	__forceinline Vector3d GetMainPosition() { return _vMainPosition; }
	__forceinline void SetTargetPosition(Vector3d vPosition) { _vTargetPosition = vPosition; }
	__forceinline Vector3d GetMovePosition() { return _vMovePoint; }
};

#endif