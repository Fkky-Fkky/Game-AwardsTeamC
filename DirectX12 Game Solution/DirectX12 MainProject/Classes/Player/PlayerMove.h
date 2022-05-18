#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class PlayerMove {
public:
	PlayerMove() {};
	~PlayerMove() {};

	void Update(const float deltaTime, SimpleMath::Vector3& pos_, SimpleMath::Vector3& rot_);

private:
	const float PLAYER_MOVE_SPEED_ = 10.0f;
	const float PLAYER_ROTATION_ANGLE_ = 90.0f;
	const float PLAYER_LIMIT_MAX_POS_X_ = 17.0f;
	const float PLAYER_LIMIT_MIN_POS_X_ = -14.0f;
};