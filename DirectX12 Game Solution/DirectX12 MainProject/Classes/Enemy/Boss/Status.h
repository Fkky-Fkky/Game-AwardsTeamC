#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"

using namespace DirectX;

class ObjectManager;

namespace boss {
	class Status {
	public:
		Status() {
			damage_type_ = HAND;
			weak_count_ = 0;
			hp_ = 0.0f;
			invincible_time_ = 0.0f;
			weak_time_ = 0.0f;
			is_set_weak_time_ = false;
		};

		void Initialize();
		void Update(const float deltaTime, const ObjectManager* const obj_m);

		float GetBossHP() const { return hp_; }
		bool IsWeak() const { return weak_count_ >= WEAK_COUNT_MAX_; }
	private:
		void DamageProcess();

		int damage_type_;
		int weak_count_;
		float hp_;
		float invincible_time_;
		float weak_time_;
		bool is_set_weak_time_;
		const int WEAK_COUNT_MAX_ = 3;
		const float BOSS_HP_MAX_ = 30.0f;
		const float HAND_DAMAGE_ = 1.0f;
		const float BODY_DAMAGE_ = 5.0f;
		const float INVINCIBLE_TIME_MAX_ = 2.0f;
		const float WEAK_TIME_MAX_ = 5.0f;

		enum DAMAGE_TYPE_ {
			HAND,
			BODY
		};
	};
}