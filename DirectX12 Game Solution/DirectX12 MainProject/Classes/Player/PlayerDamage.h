#pragma once

#include "Classes/Player/PlayerState.h"

class PlayerDamage : public PlayerState {
public:
	virtual void Update(const float deltaTime, Player& player);

private:

};