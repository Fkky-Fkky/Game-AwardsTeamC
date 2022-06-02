#pragma once

#include "Classes/Player/PlayerState.h"

class PlayerLeftMove : public PlayerState {
public:
	PlayerLeftMove() {};
	~PlayerLeftMove() {};

	virtual void Initialize() {};
	virtual void Update(const float deltaTime, Player& player);
};