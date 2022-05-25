#pragma once

#include "Classes/Player/PlayerState.h"

class PlayerJump : public PlayerState {
public:
	PlayerJump() {
		jump_time_ = 0.0f;
		cool_time_ = 0.0f;
		jump_flag_ = false;
		player_up_flag_ = false;
		landing_flag_ = false;
		old_player_pos_ = SimpleMath::Vector3::Zero;
	}
	~PlayerJump() {};

	virtual void Update(const float deltaTime, Player& player);

private:
	float jump_time_;
	float cool_time_;

	bool  jump_flag_;
	bool  player_up_flag_;
	bool landing_flag_;

	SimpleMath::Vector3 old_player_pos_;

	const float GRAVITY_ = 20.0f;
	const float V0_ = 16.0f;
	const float HALF_ = 0.5f;
	const float DOWN_SPEED_ = 2.0f;
	const float GROUND_Y_ = 0.0f;
	const float COOL_TIME_MAX_ = 0.2f;
};