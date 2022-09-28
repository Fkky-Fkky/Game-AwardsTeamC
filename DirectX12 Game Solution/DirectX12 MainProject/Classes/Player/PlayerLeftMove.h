#pragma once

#include "Classes/Player/PlayerActionState.h"

namespace player {
	class PlayerLeftMove : public PlayerActionState {
	public:
		PlayerLeftMove() {};
		~PlayerLeftMove() {};

		virtual void Initialize() {};
		virtual void Update(const float deltaTime, Player* const player);
	};
}