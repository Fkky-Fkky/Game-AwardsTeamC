#include "Classes/Enemy/Boss/Parts/Hands/Attack/RightSlap.h"
#include "Classes/Enemy/Boss/Boss.h"

void RightSlap::Update(const float deltaTime, SimpleMath::Vector3 player_pos, Boss* boss) {
	SimpleMath::Vector3 pos = boss_handR_->GetHandPos();
	SimpleMath::Vector3 rote = boss_handR_->GetRotation();
	
	if (!hand_return_flag_) {
		boss_handR_->SetAttackFlag(true);
		slap_time_ += deltaTime;
		pos.x -= SLAP_SPEED_ * slap_time_ - HALF_ * SLAP_GRAVITY_ * slap_time_ * slap_time_;
		pos.y = std::max(pos.y - 10.0f * deltaTime, 2.0f);
		pos.z = std::max(pos.z - MOVE_SPEED_Z_ * deltaTime, 0.0f);
		rote.x = std::min(rote.x + 1.0f * deltaTime, XM_PIDIV2);
	}
	else {
		pos.x  = std::min(pos.x + MOVE_SPEED_X_ * deltaTime, HAND_R_INITIAL_POS_X_);
		pos.z  = std::min(pos.z + MOVE_SPEED_Z_ * deltaTime, HAND_INITIAL_POS_Z_);
		rote.x = std::max(rote.x - 10.0f * deltaTime, XM_PIDIV4);
	}


	if (pos.x >= HAND_LIMIT_POS_X_) {
		pos.x = -HAND_RETURN_POS_X_;
		pos.y = HAND_INITIAL_POS_Y_;
		hand_return_flag_ = true;
		boss_handR_->SetAttackFlag(false);
	}

	if (pos.x >= HAND_R_INITIAL_POS_X_ && hand_return_flag_) {
		slap_time_ = 0.0f;
		hand_return_flag_ = false;
		boss->ActionEnd();
	}

	boss_handR_->SetHandPos(pos);
	boss_handR_->SetHandRote(rote);
}