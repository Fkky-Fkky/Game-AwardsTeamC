#include "Classes/Enemy/Boss/Parts/Hands/Attack/RightSlap.h"
#include "Classes/Enemy/Boss/Parts/Hands/HandManager.h"

void boss::RightSlap::Update(const float deltaTime, const ObjectManager* const obj_m, HandManager* const hand_m) {
	pos_  = boss_handR_->GetHandPos();
	
	time_delta_ = deltaTime;
	switch (action_state_) {
	case HAND_CHECK:	HandCheck(hand_m);			break;
	case READY:			Ready(hand_m);				break;
	case WAIT:			Wait(hand_m);				break;
	case ATTACK:		RightSlapAttack(hand_m);	break;
	case RESET:			Reset();					break;
	case RETURN:		HandReturn();				break;
	case ACTION_END:	hand_m->ActionEnd();		break;
	}

	boss_handR_->SetHandPos(pos_);
}

void boss::RightSlap::HandCheck(const HandManager* const hand_m) {	//手の状態を確認
	hand_state_ = hand_m->GetHandState();
	(!hand_state_) ? boss_handR_->SetHandMotion(HAND_MOTION::ROCK) : boss_handR_->SetHandMotion(HAND_MOTION::PAPER);
	action_state_ = READY;
}

void boss::RightSlap::Ready(HandManager* const hand_m) {	//予備動作
	pos_.y += SlapY(time_delta_);
	pos_.z  = std::max(pos_.z  - MOVE_SPEED_Z_ * time_delta_, ATTACK_POS_Z_);
	if (pos_.y <= SLAP_POS_Y_) {
		pos_.y  = SLAP_POS_Y_;
		hand_m->SetVerticalShake(true);
		action_state_ = WAIT;
	}
}

void boss::RightSlap::Wait(HandManager* const hand_m) {	//待機
	hand_m->SetVerticalShake(false);
	wait_time_ = std::min(wait_time_ + time_delta_, WAIT_TIME_MAX_);
	if (wait_time_ >= WAIT_TIME_MAX_) {
		action_state_ = ATTACK;
	}
}

void boss::RightSlap::RightSlapAttack(HandManager* const hand_m) {	//右手薙ぎ払い攻撃
	boss_handR_->SetAttackFlag(true);
	SlapAttackBase(time_delta_, hand_m);
	pos_.x = std::min(pos_.x + slap_speed_ * time_delta_, HAND_LIMIT_POS_X_);

	if (pos_.x >= HAND_LIMIT_POS_X_) {
		hand_m->SetSideShake(false);
		action_state_ = RESET;
	}
}

void boss::RightSlap::Reset() {	//手を画面の反対側に移動
	boss_handR_->SetAttackFlag(false);
	boss_handR_->SetHandMotion(HAND_MOTION::WAIT_MOTION);
	pos_.x  = -HAND_RETURN_POS_X_;
	pos_.y  = HAND_INITIAL_POS_Y_;
	pos_.z  = HAND_INITIAL_POS_Z_;
	action_state_ = RETURN;
}

void boss::RightSlap::HandReturn() {	//画面外から初期位置へ移動
	pos_.x = std::min(pos_.x + MOVE_SPEED_X_ * time_delta_, HAND_R_INITIAL_POS_X_);
	if (pos_.x >= HAND_R_INITIAL_POS_X_ ) {
		action_state_ = ACTION_END;
	}
}