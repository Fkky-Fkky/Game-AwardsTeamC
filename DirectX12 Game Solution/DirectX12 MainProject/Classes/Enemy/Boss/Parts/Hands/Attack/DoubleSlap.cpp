#include "Classes/Enemy/Boss/Parts/Hands/Attack/DoubleSlap.h"
#include "Classes/Enemy/Boss/Parts/Hands/HandManager.h"

void boss::DoubleSlap::Update(const float deltaTime, const ObjectManager* const obj_m, HandManager* const hand_m)	{
	r_pos_  = boss_handR_->GetHandPos();
	l_pos_  = boss_handL_->GetHandPos();

	time_delta_ = deltaTime;

	switch (action_state_) {
	case HAND_CHECK:	HandCheck(hand_m);		break;
	case READY:			Ready(hand_m);			break;
	case ATTACK:		Attack(hand_m);			break;
	case RESET:			Reset();				break;
	case RETURN:		HandReturn();			break;
	case ACTION_END:	hand_m->ActionEnd();	break;
	}

	boss_handR_->SetHandPos(r_pos_);
	boss_handL_->SetHandPos(l_pos_);
}

void boss::DoubleSlap::HandCheck(const HandManager* const hand_m) {	//手の状態を確認
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

void boss::DoubleSlap::Ready(HandManager* const hand_m) {	//予備動作
	slap_y_ = SlapY(time_delta_);
	ReadyR();
	ReadyL();

	if (ready_end_r_ && ready_end_l_) {
		hand_m->SetVerticalShake(true);
		action_state_ = ATTACK;
	}
}

void boss::DoubleSlap::ReadyR() {	//右手構え
	r_pos_.y += slap_y_;
	r_pos_.z  = std::max(r_pos_.z  - MOVE_SPEED_Z_ * time_delta_, ATTACK_POS_Z_);
	if (r_pos_.y <= SLAP_POS_Y_) {
		r_pos_.y  = SLAP_POS_Y_;
		ready_end_r_ = true;
	}
}

void boss::DoubleSlap::ReadyL() {	//左手構え
	l_pos_.y += slap_y_;
	l_pos_.z  = std::max(l_pos_.z  - MOVE_SPEED_Z_ * time_delta_, ATTACK_POS_Z_);
	if (l_pos_.y <= L_HAND_DEST_Y_) {
		l_pos_.y  = L_HAND_DEST_Y_;
		ready_end_l_ = true;
	}
}

void boss::DoubleSlap::Attack(HandManager* const hand_m) {	//薙ぎ払い攻撃
	wait_time_ = std::min(wait_time_ + time_delta_, WAIT_TIME_MAX_);
	hand_m->SetVerticalShake(false);

	if (wait_time_ >= ATTACK_START_TIME_R_) {
		SlapR(hand_m);
	}

	if (wait_time_ >= WAIT_TIME_MAX_) {
		SlapL(hand_m);
	}

	if (atk_end_r_ && atk_end_l_) {
		action_state_ = RESET;
	}
}

void boss::DoubleSlap::SlapR(HandManager* const hand_m) {	//右手薙ぎ払い
	boss_handR_->SetAttackFlag(true);
	SlapAttackBase(time_delta_, hand_m);
	r_pos_.x = std::min(r_pos_.x + slap_speed_ * time_delta_, HAND_LIMIT_POS_X_);
	if (r_pos_.x >= HAND_LIMIT_POS_X_) {
		atk_end_r_ = true;
		hand_m->SetSideShake(false);
	}
}

void boss::DoubleSlap::SlapL(HandManager* const hand_m) {	//左手薙ぎ払い
	boss_handL_->SetAttackFlag(true);
	l_slap_speed_x_ = std::min(l_slap_speed_x_ + ADD_SLAP_SPEED_ * time_delta_, SLAP_SPEED_MAX_X_);
	l_pos_.x		= std::max(l_pos_.x - l_slap_speed_x_ * time_delta_, -HAND_LIMIT_POS_X_);
	if (l_pos_.x <= -HAND_LIMIT_POS_X_) {
		atk_end_l_ = true;
	}
}

void boss::DoubleSlap::Reset() {	//それぞれの手を画面の反対へ移動
	r_pos_.x  = -HAND_RETURN_POS_X_;
	r_pos_.y  = HAND_INITIAL_POS_Y_;
	r_pos_.z  = HAND_INITIAL_POS_Z_;
	boss_handR_->SetAttackFlag(false);
	boss_handR_->SetHandMotion(HAND_MOTION::WAIT_MOTION);

	l_pos_.x  = HAND_RETURN_POS_X_;
	l_pos_.y  = HAND_INITIAL_POS_Y_;
	l_pos_.z  = HAND_INITIAL_POS_Z_;
	boss_handL_->SetAttackFlag(false);
	boss_handL_->SetHandMotion(HAND_MOTION::WAIT_MOTION);

	action_state_ = RETURN;
}

void boss::DoubleSlap::HandReturn() {	//手を元の座標に戻す
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