#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class ObjectManager;

namespace player {
	class PlayerStatus {
	public:
		PlayerStatus() {
			hp_ = 0.0f;
			invincible_time_ = 0.0f;
			is_invincible_ = false;
		};
		~PlayerStatus() {};

		void Initialize();
		void Update(const float deltatime, const ObjectManager* const obj_m);

		float GetPlayerHP() const { return hp_; }
	private:
		void DamageProcess();
		
		float hp_;
		float invincible_time_;
		bool is_invincible_;

		const float PLAYER_HP_MAX_ = 30.0f;
		const float INVINCIBLE_TIME_MAX_ = 1.0f;
	};
}