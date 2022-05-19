#pragma once

#include "Classes/Player/PlayerState.h"

class PlayerWait : public PlayerState {
	virtual void Update(const float deltaTime, Player& player);

};