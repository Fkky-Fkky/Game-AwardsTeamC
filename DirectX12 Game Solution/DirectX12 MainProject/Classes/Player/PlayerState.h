#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class Player;

class PlayerState {
public:
	virtual void Initialize() = 0;
	virtual void Update(const float deltaTime, Player& player) = 0;

protected:
	const float PLAYER_MOVE_SPEED_ = 10.0f;
	const float PLAYER_ROTATION_ANGLE_ = 90.0f;
	const float PLAYER_LIMIT_MAX_POS_X_ = 17.0f;
	const float PLAYER_LIMIT_MIN_POS_X_ = -17.0f;
};