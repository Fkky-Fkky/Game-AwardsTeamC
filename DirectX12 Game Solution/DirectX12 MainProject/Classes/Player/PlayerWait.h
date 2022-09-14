#pragma once

#include "Classes/Player/PlayerState.h"

namespace player {
	class PlayerWait : public PlayerState {
		virtual void Initialize() {};
		virtual void Update(const float deltaTime, Player* const player);
	};
}