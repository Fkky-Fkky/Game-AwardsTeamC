#include "Classes/Enemy/Boss/Parts/Hands/Attack/Death.h"
#include "Classes/Enemy/Boss/Parts/Hands/ActionManager.h"

void boss::Death::Update(const float deltaTime, const ObjectManager* const obj_m, ActionManager* const act_m) {
	l_pos_ = boss_handL_->GetHandPos();
	r_pos_ = boss_handR_->GetHandPos();
	l_rot_ = boss_handL_->GetRotation();
	r_rot_ = boss_handR_->GetRotation();

	time_delta_ = deltaTime;

	switch (death_state_) {
	case ATK_CANCEL:	AtkCancel(act_m);	break;
	case DEATH_ACTION:	DeathAction(act_m);	break;
	case ACTION_END:
		act_m->DeathActionEnd();
		act_m->SetVerticalShake(false);		break;
	}

	boss_handR_->SetHandPos(r_pos_);
	boss_handL_->SetHandPos(l_pos_);
	boss_handR_->SetHandRote(r_rot_);
	boss_handL_->SetHandRote(l_rot_);
}

void boss::Death::AtkCancel(ActionManager* const act_m) {	//UŒ‚ƒtƒ‰ƒO~‚ë‚·
	boss_handL_->SetAttackFlag(false);
	boss_handR_->SetAttackFlag(false);
	boss_handL_->PlayDeathMotion();
	boss_handR_->PlayDeathMotion();
	act_m->SetSideShake(false);
	act_m->SetVerticalShake(false);
	death_state_ = DEATH_ACTION;
}

void boss::Death::DeathAction(ActionManager* const act_m) {	//‚â‚ç‚ê‚½Žž‚Ì“®‚«
	if (r_pos_.x <= -DEATH_POS_X_) {
		r_pos_.x = std::min(r_pos_.x + MOVE_SPEED_X_ * time_delta_, -DEATH_POS_X_);
	}
	else {
		r_pos_.x = std::max(r_pos_.x - MOVE_SPEED_X_ * time_delta_, -DEATH_POS_X_);
	}
	if (l_pos_.x <= DEATH_POS_X_) {
		l_pos_.x = std::min(l_pos_.x + MOVE_SPEED_X_ * time_delta_, DEATH_POS_X_);
	}
	else {
		l_pos_.x = std::max(l_pos_.x - MOVE_SPEED_X_ * time_delta_, DEATH_POS_X_);
	}

	death_jump_time_ += time_delta_;
	death_jump_y_ = DEATH_JUMP_SPEED_Y_ * death_jump_time_ - HALF_ * DEATH_JUMP_GRAVITY_ * death_jump_time_ * death_jump_time_;
	r_pos_.y += death_jump_y_;
	l_pos_.y += death_jump_y_;
	if (r_pos_.y <= DEATH_POS_Y_) {
		r_pos_.y  = DEATH_POS_Y_;
	}
	if (l_pos_.y <= DEATH_POS_Y_) {
		l_pos_.y  = DEATH_POS_Y_;
	}

	r_pos_.z = std::min(r_pos_.z + MOVE_SPEED_Z_ * time_delta_, HAND_INITIAL_POS_Z_);
	l_pos_.z = std::min(l_pos_.z + MOVE_SPEED_Z_ * time_delta_, HAND_INITIAL_POS_Z_);

	r_rot_.x = std::min(r_rot_.x + ROTE_SPEED_ + time_delta_, DEATH_ROT_X_);
	l_rot_.x = std::min(l_rot_.x + ROTE_SPEED_ * time_delta_, DEATH_ROT_X_);

	const bool is_set_l_pos_end_ = l_pos_.x ==  DEATH_POS_X_ && l_pos_.y <= DEATH_POS_Y_ && l_pos_.z >= HAND_INITIAL_POS_Z_;
	const bool is_set_r_pos_end_ = r_pos_.x == -DEATH_POS_X_ && r_pos_.y <= DEATH_POS_Y_ && r_pos_.z >= HAND_INITIAL_POS_Z_;
	const bool is_set_l_rot_end_ = l_rot_.x >= DEATH_ROT_X_;
	const bool is_set_r_rot_end_ = r_rot_.x >= DEATH_ROT_X_;
	const bool ready_end_l_ = is_set_l_pos_end_ && is_set_l_rot_end_;
	const bool ready_end_r_ = is_set_r_pos_end_ && is_set_r_rot_end_;
	if (ready_end_l_ && ready_end_r_) {
		act_m->SetVerticalShake(true);
		death_state_ = ACTION_END;
	}
}