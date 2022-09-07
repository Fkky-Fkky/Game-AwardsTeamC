#include "Classes/Enemy/Boss/Boss.h"
#include "Classes/Collision/ObjectManager.h"

void Boss::Initialize() {
	body.Initialize();
	core.Initialize();
	hand_damage_num_ = 0;
}

void Boss::LoadAseets() {
	body.LoadAssets();
	core.LoadAssets();
}

void Boss::Update(const float deltaTime, const ObjectManager* const obj_m) {
	time_delta_ = deltaTime;
	body.Update(deltaTime, obj_m);
	core.Update(deltaTime, obj_m->GetBossDmgFlag(), this);
	//if (obj_m->IsBossHandLDmg() ||
	//	obj_m->IsBossHandRDmg()) {
	//	SwitchStateDamage();
	//}
	HandDamage(obj_m);
}

void Boss::Render() const {
	body.Render();
	core.Render();
}

void Boss::Render2D() const {
	core.Render2D();
}

void Boss::HandDamage(const ObjectManager* const obj_m) {
	if (obj_m->IsBossHandLDmg() || obj_m->IsBossHandRDmg()) {
		if (!is_invincible_) {
			hand_damage_num_++;
			is_invincible_ = true;
			boss_invincible_time_ = 1.0f;
		}
	}

	boss_invincible_time_ = std::max(boss_invincible_time_ - time_delta_, 0.0f);

	if (boss_invincible_time_ <= 0.0f) {
		is_invincible_ = false;
	}

	//if (hand_damage_num_ >= 3) {
	//	WeakStateStart();
	//	hand_damage_num_ = 0;
	//}

}