#pragma once

#include "Classes/Player/PlayerState.h"

class PlayerJump : public PlayerState {
public:
	PlayerJump() {
		action_state_ = READY;
		time_delta_ = 0.0f;
		jump_time_  = 0.0f;
		cool_time_  = 0.0f;
		player_up_flag_ = false;
		pos_ = SimpleMath::Vector3::Zero;
		rot_ = SimpleMath::Vector3::Zero;
		old_player_pos_ = SimpleMath::Vector3::Zero;
	}
	~PlayerJump() {};

	virtual void Update(const float deltaTime, Player& player);

private:
	void Ready();
	void Jump();
	void CoolTime();
	void JumpingMove();

	int action_state_;

	float time_delta_;
	float jump_time_;
	float cool_time_;

	bool  player_up_flag_;

	SimpleMath::Vector3 pos_;
	SimpleMath::Vector3 rot_;
	SimpleMath::Vector3 old_player_pos_;

	enum ACTION_STATE_ {
		READY,
		JUMP,
		COOL_TIME,
		ACTION_END
	};

	const float GRAVITY_ = 20.0f;
	const float V0_ = 16.0f;
	const float HALF_ = 0.5f;
	const float DOWN_SPEED_ = 2.0f;
	const float GROUND_Y_ = 0.0f;
	const float COOL_TIME_MAX_ = 0.2f;
	const float JUMPING_MOVE_SPEED_ = 5.0f;
	const float JUMPING_MOVE_SPEED_REVERSE = 2.5f;
};