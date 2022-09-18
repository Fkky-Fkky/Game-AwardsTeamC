#pragma once

#include "Classes/Player/PlayerState.h"

namespace player {
	class PlayerDeath : public PlayerState {
	public:
		PlayerDeath() {

		};
		~PlayerDeath() {};

		virtual void Initialize();
		virtual void Update(const float deltaTime, Player* const player);

	private:
	};
}