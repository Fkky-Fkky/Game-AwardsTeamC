#include "Classes/Enemy/Boss/Status.h"
#include "Classes/Collision/ObjectManager.h"

void Status::Initialize() {
	hp_ = 0.0f;
	hit_flag_ = false;
}

void Status::Update(const float deltaTime, const ObjectManager* const obj_m) {
	if (obj_m->IsBossHandLDmg() || obj_m->IsBossHandRDmg()) {

	}
}

void Status::HitProcessing() {
	hp_--;
	hit_flag_ = true;
}