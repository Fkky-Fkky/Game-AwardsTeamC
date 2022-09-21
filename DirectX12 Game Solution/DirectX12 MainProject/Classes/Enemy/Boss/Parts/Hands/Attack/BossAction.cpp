#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAction.h"
#include "Classes/Enemy/Boss/Parts/Hands/HandManager.h"

void boss::BossAction::SlapAttackBase(const float deltaTime, HandManager* const hand_m) {
	if (!is_shake_set_) {
		hand_m->SetSideShake(true);
		is_shake_set_ = true;
	}
	const float MAX_SPEED_ = 40.0f;
	const float ADD_SPEED_ = 20.0f;
	slap_speed_ = std::min(slap_speed_ + ADD_SPEED_ * deltaTime, MAX_SPEED_);
	if (!is_se_play_) {
		hand_m->PlaySlapSE();
		is_se_play_ = true;
	}
}