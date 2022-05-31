#include "Classes/Enemy/Boss/Parts/Hands/Attack/RightSlap.h"
#include "Classes/Enemy/Boss/Boss.h"

void RightSlap::Update(const float deltaTime, SimpleMath::Vector3 player_pos, Boss* boss) {
	pos_  = boss_handR_->GetHandPos();
	rote_ = boss_handR_->GetRotation();
	
	time_delta_ = deltaTime;

	switch (action_state_) {
	case ATTACK:		RightSlapAttack(boss);	break;
	case RESET:			Reset();				break;
	case RETURN:		HandReturn();			break;
	case ACTION_END:
		boss->ActionEnd();
		action_state_ = ATTACK;					break;
	}

	boss_handR_->SetHandPos(pos_);
	boss_handR_->SetHandRote(rote_);
}

void RightSlap::RightSlapAttack(Boss* boss) {	//‰EŽè“ã‚¬•¥‚¢UŒ‚
	boss_handR_->SetAttackFlag(true);
	slap_time_ += time_delta_;
	float slap_ = SLAP_SPEED_ * slap_time_ - HALF_ * SLAP_GRAVITY_ * slap_time_ * slap_time_;
	pos_.x -= slap_;
	pos_.y = std::max(pos_.y - MOVE_SPEED_Y_ * time_delta_, SLAP_POS_Y_);
	pos_.z = std::max(pos_.z - MOVE_SPEED_Z_ * time_delta_, 0.0f);
	rote_.x = std::min(rote_.x + ROTE_SPEED_ * time_delta_, XM_PIDIV2);
	if (!is_se_play_) {
		boss->PlaySlapSE();
		is_se_play_ = true;
	}
	if (pos_.x >= HAND_LIMIT_POS_X_) {
		action_state_ = RESET;
	}
}

void RightSlap::Reset() {	//Žè‚ð‰æ–Ê‚Ì”½‘Î‘¤‚ÉˆÚ“®
	boss_handR_->SetAttackFlag(false);
	pos_.x  = -HAND_RETURN_POS_X_;
	pos_.y  = HAND_INITIAL_POS_Y_;
	pos_.z  = HAND_INITIAL_POS_Z_;
	rote_.x = XM_PIDIV4;
	is_se_play_ = false;
	action_state_ = RETURN;
}

void RightSlap::HandReturn() {	//‰æ–ÊŠO‚©‚ç‰ŠúˆÊ’u‚ÖˆÚ“®
	pos_.x = std::min(pos_.x + MOVE_SPEED_X_ * time_delta_, HAND_R_INITIAL_POS_X_);
	if (pos_.x >= HAND_R_INITIAL_POS_X_ ) {
		slap_time_ = 0.0f;
		action_state_ = ACTION_END;
	}
}