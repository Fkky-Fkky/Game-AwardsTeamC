#pragma once

#include "Classes/Player/PlayerState.h"

namespace player {
	class PlayerDamage : public PlayerState {
	public:
		PlayerDamage() {
			dmg_time = 0.0f;
			knock_back_dest_ = 0.0f;
			one_process_flag_ = false;
			is_invinsible_ = false;
		}
		~PlayerDamage() {};

		virtual void Initialize();
		virtual void Update(const float deltaTime, Player* const player);

		bool IsInvincible() const { return is_invinsible_; }
	private:

		float dmg_time;
		float knock_back_dest_;
		bool one_process_flag_;
		bool is_invinsible_;

		SimpleMath::Vector3 pos_;
		SimpleMath::Vector3 rot_;
		const float ADD_DEST_ = 3.0f;
		const float KNOCK_BACK_SPEED_ = 20.0f;
		const float FALL_SPEED_ = 15.0f;
		const float DMG_TIME_MAX_ = 0.6f;
	};
}