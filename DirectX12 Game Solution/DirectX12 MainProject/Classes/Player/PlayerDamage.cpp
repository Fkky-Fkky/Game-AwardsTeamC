#include "Classes/Player/PlayerDamage.h"
#include "Classes/Player/Player.h"

void PlayerDamage::Initialize() {
	dmg_time = 0.0f;
	knock_back_dest_ = 0.0f;
	hit_flag_ = false;
	one_process_flag_ = false;
}

void PlayerDamage::Update(const float deltaTime, Player& player) {
	pos_ = player.GetPlayerPosition();
	rot_ = player.GetPlayerRotation();

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
	
	if (!one_process_flag_) {
		knock_back_dest_ = (rot_.y <= -PLAYER_ROTATION_ANGLE_) ? pos_.x - ADD_DEST_ : pos_.x + ADD_DEST_;
		knock_back_dest_ = std::clamp(knock_back_dest_, PLAYER_LIMIT_MIN_POS_X_, PLAYER_LIMIT_MAX_POS_X_);
		one_process_flag_ = true;
	}

	if (pos_.x >= knock_back_dest_) {
		pos_.x = std::max(pos_.x - KNOCK_BACK_SPEED_ * deltaTime, knock_back_dest_);
	}
	else {
		pos_.x = std::min(pos_.x + KNOCK_BACK_SPEED_ * deltaTime, knock_back_dest_);
	}

	if (pos_.y >= 0.0f) {
		pos_.y = std::max(pos_.y - FALL_SPEED_ * deltaTime, 0.0f);
	}

	player.SetPlayerPosition(pos_);
	player.SetPlayerRotation(rot_);
}

void PlayerDamage::HitProcessing() {
	player_hp_--;
	hit_flag_ = true;
}