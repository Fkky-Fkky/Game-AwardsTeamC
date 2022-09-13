#include "Classes/Enemy/Boss/Parts/Hands/Attack/Wait.h"
#include "Classes/Enemy/Boss/Parts/Hands/HandManager.h"
#include "Classes/Collision/ObjectManager.h"

void Wait::Update(const float deltaTime, const ObjectManager* const obj_m, HandManager* const hand_m) {
	float boss_hp_ = obj_m->GetBossHP();

	bool normal_time_ = boss_hp_ <= HP_NORMAL_MAX_ && boss_hp_ > HP_NORMAL_MIN_;
	bool hard_time_   = boss_hp_ <= HP_NORMAL_MIN_ && boss_hp_ > HP_HARD_MIN_;

	if (normal_time_) {	//�{�XHP3/3���̑ҋ@����
		max_wait_time_ = MAX_WAIT_TIME_NORMAL_;
	}
	else if (hard_time_) {	//�{�XHP2/3���̑ҋ@����
		max_wait_time_ = MAX_WAIT_TIME_HARD_;
	}
	else {	//�{�XHP1/3���̑ҋ@����
		max_wait_time_ = MAX_WAIT_TIME_VERY_HARD_;
	}

	if (!first_processed_flag_) {
		boss_handL_->SetHandMotion(HAND_MOTION::WAIT_MOTION);
		boss_handR_->SetHandMotion(HAND_MOTION::WAIT_MOTION);
		first_processed_flag_ = true;
	}

	wait_time_ = std::min(wait_time_ + deltaTime, max_wait_time_);
	if (wait_time_ >= max_wait_time_) {
		hand_m->RandomAttackState();
	}
}