#pragma once

#include "Classes/Player/PlayerState.h"

namespace player {
	class PlayerDeath : public PlayerState {
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
	};
}