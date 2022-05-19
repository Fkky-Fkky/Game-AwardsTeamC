#include "Classes/Player/PlayerAvoid.h"
#include "Classes/Player/Player.h"

PlayerAvoid::PlayerAvoid() {
	avoid_speed_   = 0.0f;
	player_dest_x_ = 0.0f;

	avoid_flag_		 = false;
	invincible_flag_ = false;

	player_rote_ = SimpleMath::Vector3::Zero;
}

void PlayerAvoid::Update(const float deltaTime, Player& player) {
	SimpleMath::Vector3 pos_ = player.GetPlayerPosition();
	SimpleMath::Vector3 rot_ = player.GetPlayerRotation();

	if (!avoid_flag_) {
		avoid_flag_		 = true;
		invincible_flag_ = true;
		player_rote_   = rot_;
		float add_pos_ = (IsPayerRightWard()) ? -ADD_POS_X_ : ADD_POS_X_;
		player_dest_x_ = pos_.x + add_pos_;
		player_dest_x_ = std::clamp(player_dest_x_, PLAYER_LIMIT_MIN_POS_X_, PLAYER_LIMIT_MAX_POS_X_);
	}

	if (avoid_flag_) {
		avoid_speed_ = std::min(avoid_speed_ + ADD_AVOID_SPEED_ * deltaTime, AVOID_MAX_SPEED_);
		pos_.x = (IsPayerRightWard()) ?
			std::max(pos_.x - avoid_speed_ * deltaTime, player_dest_x_) :
			std::min(pos_.x + avoid_speed_ * deltaTime, player_dest_x_);
	}

	if (pos_.x == player_dest_x_) {
		player_dest_x_ = 0.0f;
		avoid_speed_   = 0.0f;
		avoid_flag_		 = false;
		invincible_flag_ = false;
		player.SwitchState(PLAYER_STATE::WAIT);
	}

	player.SetPlayerPosition(pos_);
	player.SetPlayerRotation(rot_);
}