#include "Classes/Enemy/Boss/Parts/Hands/Attack/LeftSlap.h"
#include "Classes/Enemy/Boss/Boss.h"

void LeftSlap::Update(const float deltaTime, SimpleMath::Vector3 player_pos, Boss* boss) {
	pos_  = boss_handL_->GetHandPos();
	rote_ = boss_handL_->GetRotation();

	time_delta_ = deltaTime;

	switch (action_state_) {
	case READY:			Ready();				break;
	case WAIT:			Wait();					break;
	case ATTACK:		LeftSlapAttack(boss);	break;
	case RESET:			Reset();				break;
	case RETURN:		HandReturn();			break;
	case ACTION_END:	boss->ActionEnd();		break;
	}

	boss_handL_->SetHandPos(pos_);
	boss_handL_->SetHandRote(rote_);
}

void LeftSlap::Ready() {	//ó\îıìÆçÏ
	slap_time_y_ += time_delta_;
	pos_.y += SLAP_SPEED_Y_ * slap_time_y_ - HALF_ * SLAP_GRAVITY_Y_ * slap_time_y_ * slap_time_y_;
	pos_.z  = std::max(pos_.z - MOVE_SPEED_Z_ * time_delta_, 0.0f);
	rote_.x = std::min(rote_.x + ROTE_SPEED_ * time_delta_, XM_PIDIV2);

	if (pos_.y <= SLAP_POS_Y_) {
		pos_.y  = SLAP_POS_Y_;
		action_state_ = WAIT;
	}
}

void LeftSlap::Wait() {	//ë“ã@
	wait_time_ = std::min(wait_time_ + time_delta_, WAIT_TIME_MAX_);
	if (wait_time_ >= WAIT_TIME_MAX_) {
		action_state_ = ATTACK;
	}
}

void LeftSlap::LeftSlapAttack(Boss* boss) {	//ç∂éËì„Ç¨ï•Ç¢çUåÇ
	boss_handL_->SetAttackFlag(true);
	slap_time_x_ += time_delta_;
	float slap_x_ = SLAP_SPEED_X_ * slap_time_x_ - HALF_ * SLAP_GRAVITY_X_ * slap_time_x_ * slap_time_x_;
	pos_.x += slap_x_;
	
	if (!is_se_play_) {
		boss->PlaySlapSE();
		is_se_play_ = true;
	}
	if (pos_.x <= -HAND_LIMIT_POS_X_) {
		action_state_ = RESET;
	}
}

void LeftSlap::Reset() {	//éËÇâÊñ ÇÃîΩëŒë§Ç…à⁄ìÆ
	boss_handL_->SetAttackFlag(false);
	pos_.x  = HAND_RETURN_POS_X_;
	pos_.y  = HAND_INITIAL_POS_Y_;
	pos_.z  = HAND_INITIAL_POS_Z_;
	rote_.x = XM_PIDIV4;
	is_se_play_ = false;
	action_state_ = RETURN;
}

void LeftSlap::HandReturn() {	//âÊñ äOÇ©ÇÁèâä˙à íuÇ÷à⁄ìÆ
	pos_.x = std::max(pos_.x - MOVE_SPEED_X_ * time_delta_, HAND_L_INITIAL_POS_X_);
	if (pos_.x == HAND_L_INITIAL_POS_X_) {
		action_state_ = ACTION_END;
	}
}