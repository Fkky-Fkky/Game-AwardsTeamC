#include "Classes/Enemy/Boss/Parts/Hands/Attack/LeftSlap.h"
#include "Classes/Enemy/Boss/Boss.h"

void LeftSlap::Update(const float deltaTime, SimpleMath::Vector3 player_pos, Boss* boss){
	pos_  = boss_handL_->GetHandPos();
	rote_ = boss_handL_->GetRotation();

	time_delta_ = deltaTime;

	switch (action_state_) {
	case ATTACK:	LeftSlapAttack();	break;
	case RESET:		Reset();			break;
	case RETURN:	HandReturn();		break;
	case ACTION_END:
		boss->ActionEnd();
		action_state_ = ATTACK;			break;
	}

	boss_handL_->SetHandPos(pos_);
	boss_handL_->SetHandRote(rote_);
}

void LeftSlap::LeftSlapAttack() {	//ç∂éËì„Ç¨ï•Ç¢çUåÇ
	boss_handL_->SetAttackFlag(true);
	slap_time_ += time_delta_;
	float slap_ = SLAP_SPEED_ * slap_time_ - HALF_ * SLAP_GRAVITY_ * slap_time_ * slap_time_;
	pos_.x += slap_;
	pos_.y  = std::max(pos_.y - MOVE_SPEED_Y_ * time_delta_, SLAP_POS_Y_);
	pos_.z  = std::max(pos_.z - MOVE_SPEED_Z_ * time_delta_, 0.0f);
	rote_.x = std::min(rote_.x + ROTE_SPEED_ * time_delta_, XM_PIDIV2);
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
	action_state_ = RETURN;
}

void LeftSlap::HandReturn() {	//âÊñ äOÇ©ÇÁèâä˙à íuÇ÷à⁄ìÆ
	pos_.x = std::max(pos_.x - MOVE_SPEED_X_ * time_delta_, HAND_L_INITIAL_POS_X_);
	if (pos_.x == HAND_L_INITIAL_POS_X_) {
		slap_time_	  = 0.0f;
		action_state_ = ACTION_END;
	}
}