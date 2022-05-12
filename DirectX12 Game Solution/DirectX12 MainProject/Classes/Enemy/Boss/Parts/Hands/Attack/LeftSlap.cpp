#include "Classes/Enemy/Boss/Parts/Hands/Attack/LeftSlap.h"
#include "Classes/Enemy/Boss/Boss.h"

void LeftSlap::Update(const float deltaTime, SimpleMath::Vector3 player_pos, Boss* boss){
	SimpleMath::Vector3 pos  = boss_handL_->GetHandPos();
	SimpleMath::Vector3 rote = boss_handL_->GetRotation();

	if (!hand_return_flag_) {
		boss_handL_->SetAttackFlag(true);
		slap_time_ += deltaTime;
		pos.x += SLAP_SPEED_ * slap_time_ - HALF_ * SLAP_GRAVITY_ * slap_time_ * slap_time_;
		pos.y = std::max(pos.y - MOVE_SPEED_Y_ * deltaTime, 2.0f);
		pos.z = std::max(pos.z - MOVE_SPEED_Z_ * deltaTime, 0.0f);
		rote.x = std::min(rote.x + ROTE_SPEED_ * deltaTime, XM_PIDIV2);
	}
	else {
		pos.x = std::max(pos.x - MOVE_SPEED_X_ * deltaTime, HAND_L_INITIAL_POS_X_);
	}


	if (pos.x <= -HAND_LIMIT_POS_X_) {
		pos.x = HAND_RETURN_POS_X_;
		pos.y = HAND_INITIAL_POS_Y_;
		pos.z = HAND_INITIAL_POS_Z_;
		rote.x = XM_PIDIV4;
		hand_return_flag_ = true;
		boss_handL_->SetAttackFlag(false);
	}

	if (pos.x <= HAND_L_INITIAL_POS_X_ && pos.y == HAND_INITIAL_POS_Y_ && hand_return_flag_) {
		pos.x = HAND_L_INITIAL_POS_X_;
		slap_time_ = 0.0f;
		hand_return_flag_ = false;
		boss->ActionEnd();
	}

	boss_handL_->SetHandPos(pos);
	boss_handL_->SetHandRote(rote);
}