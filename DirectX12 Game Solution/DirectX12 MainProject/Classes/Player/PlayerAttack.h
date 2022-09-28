#pragma once

#include "Classes/Player/PlayerActionState.h"

namespace player {
	class PlayerAttack : public PlayerActionState {
	public:
		PlayerAttack() {
			attack_time_ = 0.0f;
			attack_flg_ = false;
		};
		~PlayerAttack() {};

		virtual void Initialize();
		virtual void Update(const float deltaTime, Player* const player);
		bool IsPlayerAttackStart() const { return attack_flg_; }

	private:
		float attack_time_;
		bool attack_flg_;
		const float MAX_ATTACK_TIME_ = 3.3f;
	};
}