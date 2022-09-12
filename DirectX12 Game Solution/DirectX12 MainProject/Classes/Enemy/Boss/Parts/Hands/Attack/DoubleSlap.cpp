#include "Classes/Enemy/Boss/Parts/Hands/Attack/DoubleSlap.h"
#include "Classes/Enemy/Boss/Parts/Hands/HandManager.h"

void DoubleSlap::Update(const float deltaTime, const ObjectManager* const obj_m, HandManager* const hand_m)	{
	r_pos_  = boss_handR_->GetHandPos();
	r_rote_ = boss_handR_->GetRotation();
	l_pos_  = boss_handL_->GetHandPos();
	l_rote_ = boss_handL_->GetRotation();

	time_delta_ = deltaTime;

	switch (action_state_) {
	case HAND_CHECK:	HandCheck(hand_m);		break;
	case READY:			Ready();				break;
	case ATTACK:		Attack();				break;
	case RESET:			Reset();				break;
	case RETURN:		HandReturn();			break;
	case ACTION_END:	hand_m->ActionEnd();	break;
	}

	boss_handR_->SetHandPos(r_pos_);
	boss_handR_->SetHandRote(r_rote_);
	boss_handL_->SetHandPos(l_pos_);
	boss_handL_->SetHandRote(l_rote_);
}

void DoubleSlap::HandCheck(const HandManager* const hand_m) {	//手の状態を確認
	hand_state_	= hand_m->GetHandState();
	if (!hand_state_) {
		boss_handR_->SetHandMotion(HAND_MOTION::ROCK);
		boss_handL_->SetHandMotion(HAND_MOTION::ROCK);
	}
	else { 
		boss_handR_->SetHandMotion(HAND_MOTION::PAPER); 
		boss_handL_->SetHandMotion(HAND_MOTION::PAPER);
	}
	
	action_state_ = READY;
}

void DoubleSlap::Ready() {	//予備動作
	ReadyR();
	ReadyL();

	if (ready_end_r_ && ready_end_l_) {
		boss_handR_->SetVerticalShakeFlag(true);
		action_state_ = ATTACK;
	}
}

void DoubleSlap::ReadyR() {	//右手構え
	r_slap_time_y_ += time_delta_;
	float r_slap_y_ = SLAP_SPEED_Y_ * r_slap_time_y_ - HALF_ * SLAP_GRAVITY_Y_ * r_slap_time_y_ * r_slap_time_y_;
	r_pos_.y += r_slap_y_;
	r_pos_.z  = std::max(r_pos_.z  - MOVE_SPEED_Z_ * time_delta_, 0.0f);
	r_rote_.x = std::min(r_rote_.x + ROTE_SPEED_   * time_delta_, SLAP_ROT_X_);
	if (r_pos_.y <= R_HAND_DEST_Y_) {
		r_pos_.y  = R_HAND_DEST_Y_;
		ready_end_r_ = true;
	}
}

void DoubleSlap::ReadyL() {	//左手構え
	l_slap_time_y_ += time_delta_;
	float l_slap_y_ = SLAP_SPEED_Y_ * l_slap_time_y_ - HALF_ * SLAP_GRAVITY_Y_ * l_slap_time_y_ * l_slap_time_y_;
	l_pos_.y += l_slap_y_;
	l_pos_.z  = std::max(l_pos_.z  - MOVE_SPEED_Z_ * time_delta_, 0.0f);
	l_rote_.x = std::min(l_rote_.x + ROTE_SPEED_   * time_delta_, SLAP_ROT_X_);
	if (l_pos_.y <= L_HAND_DEST_Y_) {
		l_pos_.y  = L_HAND_DEST_Y_;
		ready_end_l_ = true;
	}
}

void DoubleSlap::Attack() {	//薙ぎ払い攻撃
	wait_time_ = std::min(wait_time_ + time_delta_, WAIT_TIME_MAX_);
	boss_handR_->SetVerticalShakeFlag(false);

	if (wait_time_ >= ATTACK_START_TIME_R_) {
		SlapR();
	}
	
	if (wait_time_ >= WAIT_TIME_MAX_) {
		SlapL();
	}

	if (atk_end_r_ && atk_end_l_) {
		action_state_ = RESET;
	}
}

void DoubleSlap::SlapR() {	//右手薙ぎ払い
	boss_handR_->SetAttackFlag(true);
	r_slap_time_x_ += time_delta_;
	float r_slap_x_ = SLAP_SPEED_X_ * r_slap_time_x_ - HALF_ * SLAP_GRAVITY_X_ * r_slap_time_x_ * r_slap_time_x_;
	r_pos_.x -= r_slap_x_;
	if (r_pos_.x >= HAND_LIMIT_POS_X_) {
		atk_end_r_ = true;
	}
}

void DoubleSlap::SlapL() {	//左手薙ぎ払い
	boss_handL_->SetAttackFlag(true);
	l_slap_time_x_ += time_delta_;
	float l_slap_x_ = SLAP_SPEED_X_ * l_slap_time_x_ - HALF_ * SLAP_GRAVITY_X_ * l_slap_time_x_ * l_slap_time_x_;
	l_pos_.x += l_slap_x_;
	if (l_pos_.x <= -HAND_LIMIT_POS_X_) {
		atk_end_l_ = true;
	}
}

void DoubleSlap::Reset() {	//それぞれの手を画面の反対へ移動
	r_pos_.x  = -HAND_RETURN_POS_X_;
	r_pos_.y  = HAND_INITIAL_POS_Y_;
	r_pos_.z  = HAND_INITIAL_POS_Z_;
	r_rote_.x = HAND_INITIAL_ROT_X_;
	boss_handR_->SetAttackFlag(false);
	boss_handR_->SetHandMotion(HAND_MOTION::WAIT_MOTION);

	l_pos_.x  = HAND_RETURN_POS_X_;
	l_pos_.y  = HAND_INITIAL_POS_Y_;
	l_pos_.z  = HAND_INITIAL_POS_Z_;
	l_rote_.x = HAND_INITIAL_ROT_X_;
	boss_handL_->SetAttackFlag(false);
	boss_handL_->SetHandMotion(HAND_MOTION::WAIT_MOTION);

	action_state_ = RETURN;
}

void DoubleSlap::HandReturn() {	//手を元の座標に戻す
	const bool is_r_hand_init_pos_ = r_pos_.x >= HAND_R_INITIAL_POS_X_;
	const bool is_l_hand_init_pos_ = l_pos_.x <= HAND_L_INITIAL_POS_X_;

	r_pos_.x = std::min(r_pos_.x + MOVE_SPEED_X_ * time_delta_, HAND_R_INITIAL_POS_X_);
	if (is_r_hand_init_pos_) {
		return_end_r_ = true;
	}

	l_pos_.x = std::max(l_pos_.x - MOVE_SPEED_X_ * time_delta_, HAND_L_INITIAL_POS_X_);
	if (is_l_hand_init_pos_) {
		return_end_l_ = true;
	}	

	if (return_end_r_ && return_end_l_) {
		action_state_ = ACTION_END;
	}
}