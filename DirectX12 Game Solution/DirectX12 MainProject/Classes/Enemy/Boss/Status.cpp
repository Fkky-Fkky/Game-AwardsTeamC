#include "Classes/Enemy/Boss/Status.h"
#include "Classes/Collision/ObjectManager.h"

void boss::Status::Initialize() {
	damage_type_ = HAND;
	weak_count_ = 0;
	hp_ = BOSS_HP_MAX_;
	invincible_time_ = 0.0f;
	weak_time_ = 0.0f;
	is_set_weak_time_ = false;
}

void boss::Status::Update(const float deltaTime, const ObjectManager* const obj_m) {
	invincible_time_ = std::max(invincible_time_ - deltaTime, 0.0f);
	if (IsWeak()) {
		weak_time_ = std::max(weak_time_ - deltaTime, 0.0f);
		if (weak_time_ <= 0.0f) {
			weak_count_ = 0;
			is_set_weak_time_ = false;
		}
	}

	bool is_invincible_ = invincible_time_ > 0.0f;
	if (obj_m->IsBossHandDmg()) {
		if (!is_invincible_) {
			damage_type_ = HAND;
			DamageProcess();
			weak_count_++;
		}
	}
	if (obj_m->IsBossBodyDmg()) {
		if (!is_invincible_) {
			damage_type_ = BODY;
			DamageProcess();
		}
	}
	if (IsWeak() && !is_set_weak_time_) {
		weak_time_ = WEAK_TIME_MAX_;
		is_set_weak_time_ = true;
	}
}

void boss::Status::DamageProcess() {
	float damage_num_ = 0.0f;
	switch (damage_type_) {
	case HAND:	damage_num_ = HAND_DAMAGE_;	break;
	case BODY:	damage_num_ = BODY_DAMAGE_;	break;
	default:	break;
	}
	hp_ -= damage_num_;
	invincible_time_ = INVINCIBLE_TIME_MAX_;
}