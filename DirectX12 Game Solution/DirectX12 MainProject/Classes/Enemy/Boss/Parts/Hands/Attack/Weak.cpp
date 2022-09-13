#include "Classes/Enemy/Boss/Parts/Hands/Attack/Weak.h"
#include "Classes/Enemy/Boss/Parts/Hands/HandManager.h"
#include "Classes/Collision/ObjectManager.h"

void Weak::Update(const float deltaTime, const ObjectManager* const obj_m, HandManager* const hand_m) {
	pos_r_ = boss_handR_->GetHandPos();
	pos_l_ = boss_handL_->GetHandPos();
	rot_r_ = boss_handR_->GetRotation();
	rot_l_ = boss_handL_->GetRotation();

	time_delta_ = deltaTime;
	switch (weak_state_) {
	case ATK_CANCEL:	   AtkCancel(hand_m);	break;
	case READY:			   Ready(obj_m);		break;
	case WEAK:			   BossWeak(obj_m);		break;
	case INITIAL_POS_MOVE: InitialPosMove();	break;
	case ACTION_END:	   hand_m->ActionEnd(); break;
	}

	boss_handR_->SetHandPos(pos_r_);
	boss_handL_->SetHandPos(pos_l_);
	boss_handR_->SetHandRote(rot_r_);
	boss_handL_->SetHandRote(rot_l_);
}

void Weak::AtkCancel(HandManager* const hand_m) {
	boss_handL_->SetAttackFlag(false);
	boss_handR_->SetAttackFlag(false); 
	boss_handL_->SetHandMotion(HAND_MOTION::WAIT_MOTION);
	boss_handR_->SetHandMotion(HAND_MOTION::WAIT_MOTION);
	hand_m->SetSideShake(false);
	hand_m->SetVerticalShake(false);
	weak_state_ = READY;
}

void Weak::Ready(const ObjectManager* const obj_m) {
	const float WEAK_ROT_X_ = 150.0f;
	const float WEAK_POS_Y_ = 3.0f;
	const float WEAK_SPEED_Y_ = 2.0f;
	const float WEAK_GRAVITY_ = 6.0f;
	time_ += time_delta_;
	float weak_y_ = WEAK_SPEED_Y_ * time_ - HALF_ * WEAK_GRAVITY_ * time_ * time_;
	pos_l_.y += weak_y_;
	pos_r_.y += weak_y_;
	if (pos_l_.y <= WEAK_POS_Y_) {
		pos_l_.y  = WEAK_POS_Y_;
	}
	if (pos_r_.y <= WEAK_POS_Y_) {
		pos_r_.y  = WEAK_POS_Y_;
	}
	const float WEAK_POS_X_ = 18.0f;
	if (pos_l_.x <= WEAK_POS_X_) {
		pos_l_.x = std::min(pos_l_.x + MOVE_SPEED_X_ * time_delta_, WEAK_POS_X_);
	}
	else {
		pos_l_.x = std::max(pos_l_.x - MOVE_SPEED_X_ * time_delta_, WEAK_POS_X_);
	}

	if (pos_r_.x <= -WEAK_POS_X_) {
		pos_r_.x = std::min(pos_r_.x + MOVE_SPEED_X_ * time_delta_, -WEAK_POS_X_);
	}
	else {
		pos_r_.x = std::max(pos_r_.x - MOVE_SPEED_X_ * time_delta_, -WEAK_POS_X_);
	}

	//pos_l_.z = std::max(pos_l_.z - MOVE_SPEED_Z_ * time_delta_, ATTACK_POS_Z_);
	//pos_r_.z = std::max(pos_r_.z - MOVE_SPEED_Z_ * time_delta_, ATTACK_POS_Z_);
	pos_r_.z = std::min(pos_r_.z + MOVE_SPEED_Z_ * time_delta_, HAND_INITIAL_POS_Z_);
	pos_l_.z = std::min(pos_l_.z + MOVE_SPEED_Z_ * time_delta_, HAND_INITIAL_POS_Z_);

	rot_l_.x = std::min(rot_l_.x + 200.0f * time_delta_, WEAK_ROT_X_);
	rot_r_.x = std::min(rot_r_.x + 200.0f + time_delta_, WEAK_ROT_X_);

	bool is_set_l_pos_end_ = pos_l_.x == WEAK_POS_X_ && pos_l_.y <= WEAK_POS_Y_ && pos_l_.z >= HAND_INITIAL_POS_Z_;
	bool is_set_l_rot_end_ = rot_l_.x >= WEAK_ROT_X_;
	bool ready_end_l_ = is_set_l_pos_end_ && is_set_l_rot_end_;
	bool is_set_r_pos_end_ = pos_r_.x == -WEAK_POS_X_ && pos_r_.y <= WEAK_POS_Y_ && pos_r_.z >= HAND_INITIAL_POS_Z_;
	bool is_set_r_rot_end_ = rot_r_.x >= WEAK_ROT_X_;
	bool ready_end_r_ = is_set_r_pos_end_ && is_set_r_rot_end_;
	if (ready_end_l_ && ready_end_r_) {
		weak_state_ = WEAK;
	}
}

void Weak::BossWeak(const ObjectManager* const obj_m) {	//ウィーク状態維持
	if (!obj_m->IsBossWeak()) {
		weak_state_ = INITIAL_POS_MOVE;
	}
}

void Weak::InitialPosMove() {//手を初期座標に移動
	pos_r_.y = std::min(pos_r_.y + MOVE_SPEED_Y_ * time_delta_, HAND_INITIAL_POS_Y_);
	//pos_r_.z = std::min(pos_r_.z + MOVE_SPEED_Z_ * time_delta_, HAND_INITIAL_POS_Z_);
	pos_l_.y = std::min(pos_l_.y + MOVE_SPEED_Y_ * time_delta_, HAND_INITIAL_POS_Y_);
	//pos_l_.z = std::min(pos_l_.z + MOVE_SPEED_Z_ * time_delta_, HAND_INITIAL_POS_Z_);

	rot_r_.x = std::max(rot_r_.x - 200.0f * time_delta_, HAND_INITIAL_ROT_X_);
	rot_l_.x = std::max(rot_l_.x - 200.0f * time_delta_, HAND_INITIAL_ROT_X_);
	bool is_init_pos_r_ = pos_r_.y >= HAND_INITIAL_POS_Y_ && pos_r_.z >= HAND_INITIAL_POS_Z_;
	bool is_init_pos_l_ = pos_l_.y >= HAND_INITIAL_POS_Y_ && pos_l_.z >= HAND_INITIAL_POS_Z_;

	if (is_init_pos_r_ && is_init_pos_l_) {
		weak_state_ = ACTION_END;
	}
}