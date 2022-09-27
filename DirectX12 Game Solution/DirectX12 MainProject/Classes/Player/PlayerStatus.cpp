#include "Classes/Player/PlayerStatus.h"
#include "Classes/Object/ObjectManager.h"

void player::PlayerStatus::Initialize() {
	hp_ = PLAYER_HP_MAX_;
	invincible_time_ = 0.0f;
	damage_ = 0.0f;
	is_invincible_ = false;
}

void player::PlayerStatus::Update(const float deltatime, const ObjectManager* const obj_m) {
	invincible_time_ = std::max(invincible_time_ - deltatime, 0.0f);
	if (invincible_time_ <= 0.0f) {
		is_invincible_ = false;
	}

	if (obj_m->IsPlayerDmg() && !is_invincible_) {
		is_invincible_ = true;
		if (obj_m->IsBossHandOpen()) {
			damage_ = OPEN_DAMAGE_;
		}
		else {
			damage_ = CLOSE_DAMAGE_;
		}
		DamageProcess();
	}
}

void player::PlayerStatus::DamageProcess() {	//プレイヤーのダメージ処理
	hp_ -= damage_;
	invincible_time_ = INVINCIBLE_TIME_MAX_;
}