#include "Classes/Enemy/Boss/Parts/Hands/Attack/Weak.h"
#include "Classes/Enemy/Boss/Parts/Hands/ActionManager.h"
#include "Classes/Object/ObjectManager.h"

void boss::Weak::Update(const float deltaTime, const ObjectManager* const obj_m, ActionManager* const act_m) {
	pos_r_ = boss_handR_->GetHandPos();
	pos_l_ = boss_handL_->GetHandPos();
	rot_r_ = boss_handR_->GetRotation();
	rot_l_ = boss_handL_->GetRotation();

	time_delta_ = deltaTime;
	switch (weak_state_) {
	case ATK_CANCEL:	   AtkCancel(act_m);		break;
	case READY:			   Ready(act_m);			break;
	case WEAK:			   BossWeak(obj_m, act_m);	break;
	case INITIAL_POS_MOVE: InitialPosMove();		break;
	case ACTION_END:	   act_m->ActionEnd();		break;
	}

	boss_handR_->SetHandPos(pos_r_);
	boss_handL_->SetHandPos(pos_l_);
	boss_handR_->SetHandRote(rot_r_);
	boss_handL_->SetHandRote(rot_l_);
}

void boss::Weak::AtkCancel(ActionManager* const act_m) {	//攻撃フラグを降ろす
	boss_handL_->SetAttackFlag(false);
	boss_handR_->SetAttackFlag(false);
	boss_handL_->SetHandMotion(HAND_MOTION::WAIT_MOTION);
	boss_handR_->SetHandMotion(HAND_MOTION::WAIT_MOTION);
	act_m->SetSideShake(false);
	act_m->SetVerticalShake(false);
	weak_state_ = READY;
}

void boss::Weak::Ready(ActionManager* const act_m) {	//両手の移動処理
	const float WEAK_SPEED_Y_ = 2.0f;
	const float WEAK_GRAVITY_ = 6.0f;
	weak_time_y_ += time_delta_;
	weak_y_ = WEAK_SPEED_Y_ * weak_time_y_ - HALF_ * WEAK_GRAVITY_ * weak_time_y_ * weak_time_y_;

	ReadyR();
	ReadyL();
	const bool is_set_l_pos_end_ = pos_l_.x ==  WEAK_POS_X_ && pos_l_.y <= WEAK_POS_Y_ && pos_l_.z >= HAND_INITIAL_POS_Z_;
	const bool is_set_r_pos_end_ = pos_r_.x == -WEAK_POS_X_ && pos_r_.y <= WEAK_POS_Y_ && pos_r_.z >= HAND_INITIAL_POS_Z_;
	const bool is_set_l_rot_end_ = rot_l_.x >= WEAK_ROT_X_;
	const bool is_set_r_rot_end_ = rot_r_.x >= WEAK_ROT_X_;
	const bool ready_end_l_ = is_set_l_pos_end_ && is_set_l_rot_end_;
	const bool ready_end_r_ = is_set_r_pos_end_ && is_set_r_rot_end_;
	if (ready_end_l_ && ready_end_r_) {
		act_m->SetVerticalShake(true);
		weak_state_ = WEAK;
	}
}

void boss::Weak::ReadyR() {	//右手の移動
	if (pos_r_.x <= -WEAK_POS_X_) {
		pos_r_.x = std::min(pos_r_.x + MOVE_SPEED_X_ * time_delta_, -WEAK_POS_X_);
	}
	else {
		pos_r_.x = std::max(pos_r_.x - MOVE_SPEED_X_ * time_delta_, -WEAK_POS_X_);
	}
	pos_r_.y += weak_y_;
	if (pos_r_.y <= WEAK_POS_Y_) {
		pos_r_.y = WEAK_POS_Y_;
	}
	pos_r_.z = std::min(pos_r_.z + MOVE_SPEED_Z_ * time_delta_, HAND_INITIAL_POS_Z_);
	rot_r_.x = std::min(rot_r_.x + ROTE_SPEED_ + time_delta_, WEAK_ROT_X_);
}

void boss::Weak::ReadyL() {	//左手の移動
	if (pos_l_.x <= WEAK_POS_X_) {
		pos_l_.x = std::min(pos_l_.x + MOVE_SPEED_X_ * time_delta_, WEAK_POS_X_);
	}
	else {
		pos_l_.x = std::max(pos_l_.x - MOVE_SPEED_X_ * time_delta_, WEAK_POS_X_);
	}
	pos_l_.y += weak_y_;
	if (pos_l_.y <= WEAK_POS_Y_) {
		pos_l_.y = WEAK_POS_Y_;
	}
	pos_l_.z = std::min(pos_l_.z + MOVE_SPEED_Z_ * time_delta_, HAND_INITIAL_POS_Z_);
	rot_l_.x = std::min(rot_l_.x + ROTE_SPEED_ * time_delta_, WEAK_ROT_X_);
}

void boss::Weak::BossWeak(const ObjectManager* const obj_m, ActionManager* const act_m) {	//ウィーク状態維持
	act_m->SetVerticalShake(false);
	if (!obj_m->IsBossWeak()) {
		weak_state_ = INITIAL_POS_MOVE;
	}
}

void boss::Weak::InitialPosMove() {	//手を初期座標に移動
	pos_r_.x = std::min(pos_r_.x + MOVE_SPEED_X_ * time_delta_, HAND_R_INITIAL_POS_X_);
	pos_l_.x = std::max(pos_l_.x - MOVE_SPEED_X_ * time_delta_, HAND_L_INITIAL_POS_X_);
	
	pos_r_.y = std::min(pos_r_.y + MOVE_SPEED_Y_ * time_delta_, HAND_INITIAL_POS_Y_);
	pos_l_.y = std::min(pos_l_.y + MOVE_SPEED_Y_ * time_delta_, HAND_INITIAL_POS_Y_);

	rot_r_.x = std::max(rot_r_.x - ROTE_SPEED_ * time_delta_, HAND_INITIAL_ROT_X_);
	rot_l_.x = std::max(rot_l_.x - ROTE_SPEED_ * time_delta_, HAND_INITIAL_ROT_X_);
	bool is_init_pos_r_ = pos_r_.x <= HAND_R_INITIAL_POS_X_ && pos_r_.y >= HAND_INITIAL_POS_Y_ && pos_r_.z >= HAND_INITIAL_POS_Z_;
	bool is_init_pos_l_ = pos_l_.x >= HAND_L_INITIAL_POS_X_ && pos_l_.y >= HAND_INITIAL_POS_Y_ && pos_l_.z >= HAND_INITIAL_POS_Z_;
	bool is_init_rot_r_ = rot_r_.x >= HAND_INITIAL_ROT_X_;
	bool is_init_rot_l_ = rot_l_.x >= HAND_INITIAL_ROT_X_;
	bool is_move_end_r_ = is_init_pos_r_ && is_init_rot_r_;
	bool is_move_end_l_ = is_init_pos_l_ && is_init_rot_l_;
	if (is_move_end_r_ && is_move_end_l_) {
		weak_state_ = ACTION_END;
	}
}