#include "Classes/Enemy/Boss/Parts/Hands/Attack/Wait.h"
#include "Classes/Enemy/Boss/Boss.h"

void Wait::Update(const float deltaTime, ObjectManager* obj_m, Boss* boss) {
	float boss_hp_ = boss->GetBossHP();

	bool normal_time_ = boss_hp_ <= HP_NORMAL_MAX_ && boss_hp_ > HP_NORMAL_MIN_;
	bool hard_time_   = boss_hp_ <= HP_NORMAL_MIN_ && boss_hp_ > HP_HARD_MIN_;

	if (normal_time_) {	//ボスHP3/3時の待機時間
		max_wait_time_ = MAX_WAIT_TIME_NORMAL_;
	}
	else if (hard_time_) {	//ボスHP2/3時の待機時間
		max_wait_time_ = MAX_WAIT_TIME_HARD_;
	}
	else {	//ボスHP1/3時の待機時間
		max_wait_time_ = MAX_WAIT_TIME_VERY_HARD_;
	}

	if (boss_handL_->GetHandHp() <= 0 &&
		boss_handR_->GetHandHp() <= 0) {
		max_wait_time_ = 5.0f;
	}

	wait_time_ = std::min(wait_time_ + deltaTime, max_wait_time_);
	if (wait_time_ >= max_wait_time_) {
		boss->RandomAttackState();
	}
}