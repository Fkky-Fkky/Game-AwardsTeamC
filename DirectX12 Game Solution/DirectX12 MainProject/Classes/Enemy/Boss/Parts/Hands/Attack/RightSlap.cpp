#include "Classes/Enemy/Boss/Parts/Hands/Attack/RightSlap.h"
#include "Classes/Enemy/Boss/Boss.h"

void RightSlap::Update(const float deltaTime, ObjectManager* obj_m, Boss* boss) {
	pos_  = boss_handR_->GetHandPos();
	rote_ = boss_handR_->GetRotation();
	
	time_delta_ = deltaTime;

	switch (action_state_) {
	case READY:			Ready();				break;
	case WAIT:			Wait();					break;
	case ATTACK:		RightSlapAttack(boss);	break;
	case RESET:			Reset();				break;
	case RETURN:		HandReturn();			break;
	case ACTION_END:	boss->ActionEnd();		break;
	}

	boss_handR_->SetHandPos(pos_);
	boss_handR_->SetHandRote(rote_);
}

void RightSlap::Ready() {	//予備動作
	slap_time_y_ += time_delta_;
	float slap_y_ = SLAP_SPEED_Y_ * slap_time_y_ - HALF_ * SLAP_GRAVITY_Y_ * slap_time_y_ * slap_time_y_;
	pos_.y += slap_y_;
	pos_.z  = std::max(pos_.z  - MOVE_SPEED_Z_ * time_delta_, 0.0f);
	rote_.x = std::min(rote_.x + ROTE_SPEED_   * time_delta_, XM_PIDIV2);

	if (pos_.y <= SLAP_POS_Y_) {
		pos_.y  = SLAP_POS_Y_;
		action_state_ = WAIT;
	}
}

void RightSlap::Wait() {	//待機
	wait_time_ = std::min(wait_time_ + time_delta_, WAIT_TIME_MAX_);
	if (wait_time_ >= WAIT_TIME_MAX_) {
		action_state_ = ATTACK;
	}
}

void RightSlap::RightSlapAttack(Boss* boss) {	//右手薙ぎ払い攻撃
	boss_handR_->SetAttackFlag(true);
	slap_time_x_ += time_delta_;
	float slap_x_ = SLAP_SPEED_X_ * slap_time_x_ - HALF_ * SLAP_GRAVITY_X_ * slap_time_x_ * slap_time_x_;
	pos_.x -= slap_x_;
	if (!is_se_play_) {
		boss->PlaySlapSE();
		is_se_play_ = true;
	}
	if (pos_.x >= HAND_LIMIT_POS_X_) {
		action_state_ = RESET;
	}
}

void RightSlap::Reset() {	//手を画面の反対側に移動
	boss_handR_->SetAttackFlag(false);
	pos_.x  = -HAND_RETURN_POS_X_;
	pos_.y  = HAND_INITIAL_POS_Y_;
	pos_.z  = HAND_INITIAL_POS_Z_;
	rote_.x = XM_PIDIV4;
	action_state_ = RETURN;
}

void RightSlap::HandReturn() {	//画面外から初期位置へ移動
	pos_.x = std::min(pos_.x + MOVE_SPEED_X_ * time_delta_, HAND_R_INITIAL_POS_X_);
	if (pos_.x >= HAND_R_INITIAL_POS_X_ ) {
		action_state_ = ACTION_END;
	}
}