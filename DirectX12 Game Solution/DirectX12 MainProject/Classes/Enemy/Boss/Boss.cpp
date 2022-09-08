#include "Classes/Enemy/Boss/Boss.h"
#include "Classes/Collision/ObjectManager.h"

void Boss::Initialize() {
	body_.Initialize();
	core_.Initialize();
	hand_.Initialize();
	status_.Initialize();
	hand_damage_num_ = 0;
}

void Boss::LoadAseets() {
	body_.LoadAssets();
	core_.LoadAssets();
	hand_.LoadAssets();
}

void Boss::Update(const float deltaTime, const ObjectManager* const obj_m) {
	time_delta_ = deltaTime;
	body_.Update(deltaTime, obj_m);
	core_.Update(deltaTime, obj_m->IsBossBodyDmg(), this);
	hand_.Update(deltaTime, obj_m);
	status_.Update(deltaTime, obj_m);
	//if (obj_m->IsBossHandLDmg() ||
	//	obj_m->IsBossHandRDmg()) {
	//	SwitchStateDamage();
	//}
	HandDamage(obj_m);
}

void Boss::Render() const {
	body_.Render();
	core_.Render();
	hand_.Render();
}

void Boss::Render2D() const {
	core_.Render2D();
	hand_.Render2D();
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