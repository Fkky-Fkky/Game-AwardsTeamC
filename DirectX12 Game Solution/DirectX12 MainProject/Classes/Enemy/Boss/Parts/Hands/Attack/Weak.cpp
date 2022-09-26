#include "Classes/Enemy/Boss/Parts/Hands/Attack/Weak.h"
#include "Classes/Enemy/Boss/Parts/Hands/ActionManager.h"
#include "Classes/Object/ObjectManager.h"

/**
* @brief Weak処理更新
*
* @param[in] deltaTime 時間
* @param[out] obj_m オブジェクトマネージャー
* @param[out] act_m アクションマネージャー
*/
void boss::Weak::Update(const float deltaTime, const ObjectManager* const obj_m, ActionManager* const act_m) {
	pos_r_ = boss_handR_->GetHandPos();
	pos_l_ = boss_handL_->GetHandPos();
	rot_r_ = boss_handR_->GetRotation();
	rot_l_ = boss_handL_->GetRotation();

	time_delta_ = deltaTime;
	switch (weak_state_) {
	case ATK_CANCEL:	   AtkCancel(act_m);	break;
	case WEAK_ACTION:	   WeakAction(act_m);	break;
	case WAIT:			   Wait(obj_m, act_m);	break;
	case INITIAL_POS_MOVE: InitialPosMove();	break;
	case ACTION_END:	   act_m->ActionEnd();	break;
	}

	boss_handR_->SetHandPos(pos_r_);
	boss_handL_->SetHandPos(pos_l_);
	boss_handR_->SetHandRote(rot_r_);
	boss_handL_->SetHandRote(rot_l_);
}

/**
* @brief 攻撃のキャンセル
* 
* @param[out] act_m アクションマネージャー
*/
void boss::Weak::AtkCancel(ActionManager* const act_m) {
	boss_handL_->SetAttackFlag(false);
	boss_handR_->SetAttackFlag(false);
	boss_handL_->SetHandMotion(HAND_MOTION::WAIT_MOTION);
	boss_handR_->SetHandMotion(HAND_MOTION::WAIT_MOTION);
	act_m->SetSideShake(false);
	act_m->SetVerticalShake(false);
	weak_state_ = WEAK_ACTION;
}

/**
* @brief 両手の移動処理
* 
* @param[out] act_m アクションマネージャー
*/
void boss::Weak::WeakAction(ActionManager* const act_m) {
	weak_time_y_ += time_delta_;
	weak_y_ = WEAK_SPEED_Y_ * weak_time_y_ - HALF_ * WEAK_GRAVITY_ * weak_time_y_ * weak_time_y_;

	WeakR();
	WeakL();
	const bool is_l_weak_pos_ = pos_l_.x ==  WEAK_POS_X_ && pos_l_.y <= WEAK_POS_Y_ && pos_l_.z >= HAND_INITIAL_POS_Z_;
	const bool is_r_weak_pos_ = pos_r_.x == -WEAK_POS_X_ && pos_r_.y <= WEAK_POS_Y_ && pos_r_.z >= HAND_INITIAL_POS_Z_;
	const bool is_l_weak_rot_ = rot_l_.x >= WEAK_ROT_X_;
	const bool is_r_weak_rot_ = rot_r_.x >= WEAK_ROT_X_;
	const bool is_l_weak_ = is_l_weak_pos_ && is_l_weak_rot_;
	const bool is_r_weak_ = is_r_weak_pos_ && is_r_weak_rot_;
	if (is_l_weak_ && is_r_weak_) {
		act_m->SetVerticalShake(true);
		weak_state_ = WAIT;
	}
}

/**
* @brief 右手の移動
*/
void boss::Weak::WeakR() {
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

/**
* @brief 左手の移動
*/
void boss::Weak::WeakL() {
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

/**
* @brief ウィーク状態維持
*/
void boss::Weak::Wait(const ObjectManager* const obj_m, ActionManager* const act_m) {
	act_m->SetVerticalShake(false);
	if (!obj_m->IsBossWeak()) {
		weak_state_ = INITIAL_POS_MOVE;
	}
}

/**
* @brief 手を初期座標に移動
*/
void boss::Weak::InitialPosMove() {
	pos_r_.x = std::min(pos_r_.x + MOVE_SPEED_X_ * time_delta_, HAND_R_INITIAL_POS_X_);
	pos_l_.x = std::max(pos_l_.x - MOVE_SPEED_X_ * time_delta_, HAND_L_INITIAL_POS_X_);
	
	pos_r_.y = std::min(pos_r_.y + MOVE_SPEED_Y_ * time_delta_, HAND_INITIAL_POS_Y_);
	pos_l_.y = std::min(pos_l_.y + MOVE_SPEED_Y_ * time_delta_, HAND_INITIAL_POS_Y_);

	rot_r_.x = std::max(rot_r_.x - ROTE_SPEED_ * time_delta_, HAND_INITIAL_ROT_X_);
	rot_l_.x = std::max(rot_l_.x - ROTE_SPEED_ * time_delta_, HAND_INITIAL_ROT_X_);
	bool is_r_init_pos_ = pos_r_.x <= HAND_R_INITIAL_POS_X_ && pos_r_.y >= HAND_INITIAL_POS_Y_ && pos_r_.z >= HAND_INITIAL_POS_Z_;
	bool is_l_init_pos_ = pos_l_.x >= HAND_L_INITIAL_POS_X_ && pos_l_.y >= HAND_INITIAL_POS_Y_ && pos_l_.z >= HAND_INITIAL_POS_Z_;
	bool is_r_init_rot_ = rot_r_.x >= HAND_INITIAL_ROT_X_;
	bool is_l_init_rot_ = rot_l_.x >= HAND_INITIAL_ROT_X_;
	bool is_r_move_end_ = is_r_init_pos_ && is_r_init_rot_;
	bool is_l_move_end_ = is_l_init_pos_ && is_l_init_rot_;
	if (is_r_move_end_ && is_l_move_end_) {
		weak_state_ = ACTION_END;
	}
}