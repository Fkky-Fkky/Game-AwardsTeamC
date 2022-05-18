#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class PlayerAvoid {
public:
	PlayerAvoid();
	~PlayerAvoid() {};
	void Update(const float deltaTime, SimpleMath::Vector3& pos, SimpleMath::Vector3& rote_);
	bool IsInvincible() { return invincible_flag_; }
private:
	bool IsPayerRightWard() { return player_rote_.y >= PLAYER_ROTATION_ANGLE_; }

	float avoid_speed_;
	float player_dest_x_;
	bool avoid_flag_;
	bool invincible_flag_;

	SimpleMath::Vector3 player_rote_;

	const float PLAYER_ROTATION_ANGLE_  = 90.0f;
	const float PLAYER_LIMIT_MAX_POS_X_ = 17.0f;
	const float PLAYER_LIMIT_MIN_POS_X_ = -14.0f;
	const float ADD_POS_X_ = 8.0f;
	const float ADD_AVOID_SPEED_ = 100.0f;
	const float AVOID_MAX_SPEED_ = 100.0f;
};