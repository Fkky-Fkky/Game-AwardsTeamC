#include "Classes/Enemy/Boss/Parts/Hands/Attack/RightSlap.h"

void RightSlap::Update(const float deltaTime, SimpleMath::Vector3 player_pos) {
	if (!hand_return_flag) {
		pos = boss_handR_->GetHandPos();
		rote = boss_handR_->GetRotation();
		boss_handR_->SetAttackFlag(true);
		slap_time += deltaTime;
		pos.x -= SLAP_SPEED * slap_time - HALF * SLAP_GRAVITY * slap_time * slap_time;
		rote.x = std::min(rote.x + 1.0f * deltaTime, XM_PIDIV2);
		pos.y = std::max(pos.y - 10.0f * deltaTime, 2.0f);
	}
	else {
		pos.x = std::min(pos.x + 10.0f * deltaTime, INITIAL_POS_X);
		rote.x = std::max(rote.x - 10.0f * deltaTime, XM_PIDIV4);
		pos.y = std::min(pos.y + 10.0f * deltaTime, INITIAL_POS_Y);
	}


	if (pos.x >= 70.0f) {
		pos.x = -30.0f;
		hand_return_flag = true;
		boss_handR_->SetAttackFlag(false);
	}

	if (pos.x >= INITIAL_POS_X && hand_return_flag) {
		pos.x = INITIAL_POS_X;
		slap_time = 0.0f;
		hand_return_flag = false;
	}

	boss_handR_->SetHandPos(pos);
	boss_handR_->SetHandRote(rote);
}