#include "Classes/Enemy/Boss/Parts/Hands/Attack/Death.h"

void boss::Death::Update(const float deltaTime, const ObjectManager* const obj_m, HandManager* const hand_m) {
	l_pos_ = boss_handL_->GetHandPos();
	r_pos_ = boss_handR_->GetHandPos();
	l_rot_ = boss_handL_->GetRotation();
	r_rot_ = boss_handR_->GetRotation();

	time_delta_ = deltaTime;

	boss_handR_->SetHandPos(r_pos_);
	boss_handL_->SetHandPos(l_pos_);
	boss_handR_->SetHandRote(r_rot_);
	boss_handL_->SetHandRote(l_rot_);
}