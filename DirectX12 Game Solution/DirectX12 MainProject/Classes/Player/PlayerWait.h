#pragma once

#include "Classes/Player/PlayerActionState.h"

namespace player {
	class PlayerWait : public PlayerActionState {
		virtual void Initialize() {};
		virtual void Update(const float deltaTime, Player* const player);
	};
}