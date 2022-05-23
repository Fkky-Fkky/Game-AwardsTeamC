#include "Classes/Enemy/Boss/Parts/Hands/Attack/DoubleSlap.h"
#include "Classes/Enemy/Boss/Boss.h"

void DoubleSlap::Update(const float deltaTime, SimpleMath::Vector3 player_pos, Boss* boss)	{
	r_pos_  = boss_handR_->GetHandPos();
	r_rote_ = boss_handR_->GetRotation();
	l_pos_  = boss_handL_->GetHandPos();
	l_rote_ = boss_handL_->GetRotation();

	time_delta_ = deltaTime;

	switch (action_state_) {
	case ATTACK:	Attack();		break;
	case RESET:		Reset();		break;
	case RETURN:	HandReturn();	break;
	case ACTION_END:
		boss->ActionEnd();
		action_state_ = ATTACK;		break;
	}

	boss_handR_->SetHandPos(r_pos_);
	boss_handR_->SetHandRote(r_rote_);
	boss_handL_->SetHandPos(l_pos_);
	boss_handL_->SetHandRote(l_rote_);
}

void DoubleSlap::Attack() {
	SlapR();

	wait_time_ = std::min(wait_time_ + time_delta_, WAIT_TIME_MAX_);
	if (wait_time_ == WAIT_TIME_MAX_) {
		SlapL();
	}

	if (r_pos_.x >=  HAND_LIMIT_POS_X_ &&
		l_pos_.x <= -HAND_LIMIT_POS_X_) {
		action_state_ = RESET;
	}
}

void DoubleSlap::SlapR() {
	boss_handR_->SetAttackFlag(true);
	r_slap_time_ += time_delta_;
	float r_slap_ = SLAP_SPEED_ * r_slap_time_ - HALF_ * SLAP_GRAVITY_ * r_slap_time_ * r_slap_time_;
	r_pos_.x -= r_slap_;
	r_pos_.y  = std::max(r_pos_.y  - MOVE_SPEED_Y_ * time_delta_, R_HAND_DEST_Y_);
	r_pos_.z  = std::max(r_pos_.z  - MOVE_SPEED_Z_ * time_delta_, 0.0f);
	r_rote_.x = std::min(r_rote_.x + ROTE_SPEED_   * time_delta_, XM_PIDIV2);
}

void DoubleSlap::SlapL() {
	boss_handL_->SetAttackFlag(true);
	l_slap_time_ += time_delta_;
	float l_slap_ = SLAP_SPEED_ * l_slap_time_ - HALF_ * SLAP_GRAVITY_ * l_slap_time_ * l_slap_time_;
	l_pos_.x += l_slap_;
	l_pos_.y  = std::max(l_pos_.y  - MOVE_SPEED_Y_ * time_delta_, L_HAND_DEST_Y_);
	l_pos_.z  = std::max(l_pos_.z  - MOVE_SPEED_Z_ * time_delta_, 0.0f);
	l_rote_.x = std::min(l_rote_.x + ROTE_SPEED_   * time_delta_, XM_PIDIV2);
}

void DoubleSlap::Reset() {
	r_pos_.x  = -HAND_RETURN_POS_X_;
	r_pos_.y  = HAND_INITIAL_POS_Y_;
	r_pos_.z  = HAND_INITIAL_POS_Z_;
	r_rote_.x = XM_PIDIV4;
	boss_handR_->SetAttackFlag(false);

	l_pos_.x  = HAND_RETURN_POS_X_;
	l_pos_.y  = HAND_INITIAL_POS_Y_;
	l_pos_.z  = HAND_INITIAL_POS_Z_;
	l_rote_.x = XM_PIDIV4;
	boss_handL_->SetAttackFlag(false);

	wait_time_ = 0.0f;

	action_state_ = RETURN;
}

void DoubleSlap::HandReturn() {
	r_pos_.x = std::min(r_pos_.x + MOVE_SPEED_X_ * time_delta_, HAND_R_INITIAL_POS_X_);
	l_pos_.x = std::max(l_pos_.x - MOVE_SPEED_X_ * time_delta_, HAND_L_INITIAL_POS_X_);

	if (r_pos_.x == HAND_R_INITIAL_POS_X_ &&
		l_pos_.x == HAND_L_INITIAL_POS_X_) {
		action_state_ = ACTION_END;
	}
}