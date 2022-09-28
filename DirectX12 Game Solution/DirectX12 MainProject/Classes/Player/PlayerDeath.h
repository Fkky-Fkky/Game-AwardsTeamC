#pragma once

#include "Classes/Player/PlayerActionState.h"

namespace player {
	class PlayerDeath : public PlayerActionState {
	public:
		PlayerDeath() {
			is_player_death_ = false;
		};
		~PlayerDeath() {};

		virtual void Initialize();
		virtual void Update(const float deltaTime, Player* const player);
		
		bool IsPlayerDeath()const { return is_player_death_; }

	private:
		bool is_player_death_;

		const float DEATH_POS_Y_ = 0.1f;
	};
}