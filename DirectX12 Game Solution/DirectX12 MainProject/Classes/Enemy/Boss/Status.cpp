#include "Classes/Enemy/Boss/Status.h"
#include "Classes/Collision/ObjectManager.h"

void Status::Initialize() {
	damage_type_ = HAND;
	hp_ = BOSS_HP_MAX_;
	invincible_time_ = 0.0f;
}

void Status::Update(const float deltaTime, const ObjectManager* const obj_m) {
	invincible_time_ = std::max(invincible_time_ - deltaTime, 0.0f);
	
	bool is_invincible_ = invincible_time_ > 0.0f;
	if (obj_m->IsBossHandLDmg() || obj_m->IsBossHandRDmg()) {
		if (!is_invincible_) {
			damage_type_ = HAND;
			DamageProcess();
		}
	}
	if (obj_m->IsBossBodyDmg()) {
		if (!is_invincible_) {
			damage_type_ = BODY;
			DamageProcess();
		}
	}
}

void Status::DamageProcess() {
	float damage_num_ = 0.0f;
	switch (damage_type_) {
	case HAND:	damage_num_ = HAND_DAMAGE_;	break;
	case BODY:	damage_num_ = BODY_DAMAGE_;	break;
	default:	break;
	}
	hp_ -= damage_num_;
	invincible_time_ = INVINCIBLE_TIME_MAX_;
}