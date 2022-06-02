#pragma once

#include "Classes/Player/PlayerState.h"

class PlayerRightMove : public PlayerState {
public:
	PlayerRightMove() {};
	~PlayerRightMove() {};

	virtual void Initialize() {};
	virtual void Update(const float deltaTime, Player& player);
};