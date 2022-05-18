#include "Classes/Player/PlayerAvoid.h"

PlayerAvoid::PlayerAvoid() {
	avoid_speed_   = 0.0f;
	player_dest_x_ = 0.0f;

	avoid_flag_		 = false;
	invincible_flag_ = false;

	player_rote_ = SimpleMath::Vector3::Zero;
}

void PlayerAvoid::Update(const float deltaTime, SimpleMath::Vector3& pos, SimpleMath::Vector3& rote_) {
	if (!avoid_flag_ && DXTK->KeyEvent->pressed.Back) {
		avoid_flag_		 = true;
		invincible_flag_ = true;
		player_rote_   = rote_;
		float add_pos_ = (IsPayerRightWard()) ? -ADD_POS_X_ : ADD_POS_X_;
		player_dest_x_ = pos.x + add_pos_;
		player_dest_x_ = std::clamp(player_dest_x_, PLAYER_LIMIT_MIN_POS_X_, PLAYER_LIMIT_MAX_POS_X_);
	}

	if (avoid_flag_) {
		avoid_speed_ = std::min(avoid_speed_ + ADD_AVOID_SPEED_ * deltaTime, AVOID_MAX_SPEED_);
		pos.x = (IsPayerRightWard()) ?
			std::max(pos.x - avoid_speed_ * deltaTime, player_dest_x_) :
			std::min(pos.x + avoid_speed_ * deltaTime, player_dest_x_);
	}

	if (pos.x == player_dest_x_) {
		player_dest_x_ = 0.0f;
		avoid_speed_   = 0.0f;
		avoid_flag_		 = false;
		invincible_flag_ = false;
	}
}