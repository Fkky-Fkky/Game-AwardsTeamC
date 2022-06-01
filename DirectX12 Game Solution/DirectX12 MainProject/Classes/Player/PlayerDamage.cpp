#include "Classes/Player/PlayerDamage.h"
#include "Classes/Player/Player.h"

void PlayerDamage::Initialize() {
	dmg_time = 0.0f;
	hit_flag_ = false;
}

void PlayerDamage::Update(const float deltaTime, Player& player) {
	pos_ = player.GetPlayerPosition();
	rot_ = player.GetPlayerRotation();

	player.SetMotion(PLAYER_MOTION::KNOCK_BACK);

	if (pos_.y >= 0.0f) {
		pos_.y = std::max(pos_.y - 15.0f * deltaTime, 0.0f);
	}

	if (!hit_flag_) {
		HitProcessing();
	}

	dmg_time = std::min(dmg_time + deltaTime, DMG_TIME_MAX);
	if (dmg_time >= DMG_TIME_MAX) {
		dmg_time = 0.0f;
		player.SwitchState(PLAYER_STATE::WAIT);
	}

	player.SetPlayerPosition(pos_);
	player.SetPlayerRotation(rot_);
}

void PlayerDamage::HitProcessing() {
	player_hp_ -= 1.0f;
	hit_flag_ = true;
}