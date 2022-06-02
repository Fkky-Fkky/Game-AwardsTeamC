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
	dmg_time = std::min(dmg_time + deltaTime, DMG_TIME_MAX_);
	if (dmg_time >= DMG_TIME_MAX_) {
		dmg_time = 0.0f;
		player.SetStopInitializeFlag(false);
		player.SwitchState(PLAYER_STATE::WAIT);
	}

	if (!hit_flag_) {
		player.SetStopInitializeFlag(true);
		HitProcessing();
	}

	if (pos_.y >= 0.0f) {
		pos_.y = std::max(pos_.y - FALL_SPEED_ * deltaTime, 0.0f);
	}

	player.SetPlayerPosition(pos_);
	player.SetPlayerRotation(rot_);
}

void PlayerDamage::HitProcessing() {
	player_hp_ -= 1.0f;
	hit_flag_ = true;
}