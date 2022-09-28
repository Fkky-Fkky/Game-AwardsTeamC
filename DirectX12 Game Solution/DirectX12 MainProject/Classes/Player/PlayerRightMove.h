#pragma once

#include "Classes/Player/PlayerActionState.h"

namespace player {
	class PlayerRightMove : public PlayerActionState {
	public:
		PlayerRightMove() {};
		~PlayerRightMove() {};

		virtual void Initialize() {};
		virtual void Update(const float deltaTime, Player* const player);
	};
}