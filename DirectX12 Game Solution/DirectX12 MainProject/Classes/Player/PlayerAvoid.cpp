#include "Classes/Player/PlayerAvoid.h"
#include "Classes/Player/Player.h"

PlayerAvoid::PlayerAvoid() {
	action_state_ = READY;
	
	avoid_speed_   = 0.0f;
	player_dest_x_ = 0.0f;
	cool_time_  = 0.0f;
	time_delta_ = 0.0f;

	invincible_flag_ = false;

	player_rote_ = SimpleMath::Vector3::Zero;
}

void PlayerAvoid::Update(const float deltaTime, Player& player) {
	pos_ = player.GetPlayerPosition();
	rot_ = player.GetPlayerRotation();

	time_delta_ = deltaTime;

	switch (action_state_) {
	case READY:			Ready();		break;
	case AVOID:			Avoid();		break;
	case COOL_TIME:		CoolTime();		break;
	}

	player.SetPlayerPosition(pos_);
	player.SetPlayerRotation(rot_);
	if (action_state_ == ACTION_END) {
		action_state_ = READY;
		player.SwitchState(PLAYER_STATE::WAIT);
	}
}

void PlayerAvoid::Ready() {	//回避に必要な変数の準備
	invincible_flag_ = true;
	player_rote_   = rot_;
	float add_pos_ = (IsPayerRightWard()) ? -ADD_POS_X_ : ADD_POS_X_;
	player_dest_x_ = pos_.x + add_pos_;
	player_dest_x_ = std::clamp(player_dest_x_, PLAYER_LIMIT_MIN_POS_X_, PLAYER_LIMIT_MAX_POS_X_);
	action_state_  = AVOID;
}

void PlayerAvoid::Avoid() {	//回避
	avoid_speed_ = std::min(avoid_speed_ + ADD_AVOID_SPEED_ * time_delta_, AVOID_MAX_SPEED_);
	pos_.x = (IsPayerRightWard()) ?
		std::max(pos_.x - avoid_speed_ * time_delta_, player_dest_x_) :
		std::min(pos_.x + avoid_speed_ * time_delta_, player_dest_x_);
	if (pos_.x == player_dest_x_) {
		invincible_flag_ = false;
		avoid_speed_	 = 0.0f;
		action_state_	 = COOL_TIME;
	}
}

void PlayerAvoid::CoolTime() {	//クールタイム
	cool_time_ += time_delta_;

	//クールタイム中も移動可能
	if (DXTK->KeyState->A) {
		pos_.x -= PLAYER_MOVE_SPEED_ * time_delta_;
		rot_.y  = PLAYER_ROTATION_ANGLE_;
	}
	if (DXTK->KeyState->D) {
		pos_.x += PLAYER_MOVE_SPEED_ * time_delta_;
		rot_.y  = -PLAYER_ROTATION_ANGLE_;
	}

	pos_.x = std::clamp(pos_.x, PLAYER_LIMIT_MIN_POS_X_, PLAYER_LIMIT_MAX_POS_X_);

	if (cool_time_ >= COOL_TIME_MAX) {
		cool_time_	   = 0.0f;
		player_dest_x_ = 0.0f;
		action_state_  = ACTION_END;
	}
}