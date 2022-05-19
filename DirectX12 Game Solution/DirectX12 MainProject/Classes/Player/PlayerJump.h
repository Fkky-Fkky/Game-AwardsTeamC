#pragma once

#include "Classes/Player/PlayerState.h"

class PlayerJump : public PlayerState {
public:
	PlayerJump();
	~PlayerJump() {};

	virtual void Update(const float deltaTime, Player& player);

private:
	float time_;
	bool  flag_;

	const float GRAVITY_ = 0.045f;
	const float V0_ = 0.8f;
	const float GROUND_Y_ = 0.0f;
	const float HALF_ = 0.5f;
	const float JUMP_TIME_SPEED_ = 60.0f;
};