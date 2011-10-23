#include "m3_Ai.h"

m3_Ai::m3_Ai()
{
	_aiState = AI_STAND;
	_timeState = TIME_STAND;
	_lastTimeValue = 0;
	_timeStateDuration = 0;
}

void m3_Ai::UpdateAI()
{
	switch(_aiState)
	{
	case AI_STAND : 
		if(_IsTimeOver(_timeStateDuration))
			_GenerateTimeState();
		break;
	case AI_MOVE :
		_UpdateMainPosition(_vMovePoint, 3.0f);
		break;
	case AI_CHASE :
		_UpdateMainPosition(_vMovePoint, 3.0f);
		break;
	case AI_MOVEBACK :
		break;
	case AI_ATTACK : 
		break;
	case AI_DISABLE :
		break;
	}
}

bool m3_Ai::_IsTimeOver(DWORD _timeDuration)
{
	 DWORD _currentTimeValue = GetTickCount();
     if(_currentTimeValue - _lastTimeValue > _timeDuration )
     {
		_lastTimeValue = _currentTimeValue;
		return true;
	 }
	 else
	 {
		return false;
	 }
}

void m3_Ai::_GenerateTimeState()
{
	_timeStateDuration = (DWORD)m3_Util::GetRandomFromRange(2000.0f, 5000.0f);
	if(m3_Util::GetRandomFromRange(0,100) >= 50)
	{
		_timeState = TIME_MOVE;
		_aiState =  AI_MOVE;
		_GenerateMovePoint();
	}
	else
	{
		_timeState = TIME_STAND;
		_aiState = AI_STAND;
	}
}

void m3_Ai::_GenerateMovePoint()
{
	float fRandPositionX = m3_Util::GetRandomFromRange(16, 192);
	float fRandPositionZ = m3_Util::GetRandomFromRange(64, 256);
	_vMovePoint = Vector3d(fRandPositionX,0.0f,fRandPositionZ);
}

void m3_Ai::_UpdateMainPosition(Vector3d _targetPointPosition, float _distance)
{
	float _pathLength = sqrt(pow(_targetPointPosition.x - _vMainPosition.x,2) + pow(_targetPointPosition.z - _vMainPosition.z,2));
	if(_pathLength <= _distance)
	{
		_timeState = TIME_STAND;
		_aiState = AI_STAND;
		return;
	}
	_moveSpeed = 0.2f;
	_moveSpeed= _moveSpeed / _pathLength;
    _vMainPosition += (_targetPointPosition - _vMainPosition) * _moveSpeed;
}