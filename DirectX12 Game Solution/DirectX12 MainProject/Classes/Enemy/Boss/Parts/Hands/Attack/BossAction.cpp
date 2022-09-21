#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAction.h"
#include "Classes/Enemy/Boss/Parts/Hands/HandManager.h"

void boss::BossAction::Initialize(BossHand* const boss_handL, BossHand* const bosshandR) {
	boss_handL_ = boss_handL;
	boss_handR_ = bosshandR;
	slap_speed_  = 0.0f;
	slap_y_time_ = 0.0f;
	is_se_play_	  = false;
	is_shake_set_ = false;
}

void boss::BossAction::SlapAttackBase(const float deltaTime, HandManager* const hand_m) {
	if (!is_shake_set_) {
		hand_m->SetSideShake(true);
		is_shake_set_ = true;
	}
	slap_speed_ = std::min(slap_speed_ + ADD_SLAP_SPEED_ * deltaTime, SLAP_SPEED_MAX_X_);
	if (!is_se_play_) {
		hand_m->PlaySlapSE();
		is_se_play_ = true;
	}
}

float boss::BossAction::SlapY(const float deltaTime) {
	slap_y_time_ += deltaTime;
	float r_slap_y_ = SLAP_SPEED_Y_ * slap_y_time_ - HALF_ * SLAP_GRAVITY_Y_ * slap_y_time_ * slap_y_time_;
	return r_slap_y_;
}