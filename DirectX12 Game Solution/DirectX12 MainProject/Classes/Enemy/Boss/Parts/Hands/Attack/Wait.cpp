#include "Classes/Enemy/Boss/Parts/Hands/Attack/Wait.h"
#include "Classes/Enemy/Boss/Boss.h"
#include "Classes/Collision/ObjectManager.h"

void Wait::Update(const float deltaTime, ObjectManager* obj_m, Boss* boss) {
	float boss_hp_ = boss->GetBossHP();

	bool normal_time_ = boss_hp_ <= HP_NORMAL_MAX_ && boss_hp_ > HP_NORMAL_MIN_;
	bool hard_time_   = boss_hp_ <= HP_NORMAL_MIN_ && boss_hp_ > HP_HARD_MIN_;

	if (normal_time_) {
		max_wait_time_ = MAX_WAIT_TIME_NORMAL_;
	}
	else if (hard_time_) {
		max_wait_time_ = MAX_WAIT_TIME_HARD_;
	}
	else {
		max_wait_time_ = MAX_WAIT_TIME_VERY_HARD_;
	}

	if (wait_time_ < max_wait_time_) {
		wait_time_ += deltaTime;
	}
	else {
		wait_time_ = 0.0f;
		boss->RandomAttackState();
	}
}