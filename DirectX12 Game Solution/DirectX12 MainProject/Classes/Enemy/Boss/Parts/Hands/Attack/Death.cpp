#include "Classes/Enemy/Boss/Parts/Hands/Attack/Death.h"
#include "Classes/Enemy/Boss/Parts/Hands/ActionManager.h"

/**
* @brief 死亡時行動の更新
* 
* @param[in] deltaTime 時間
* @param[out] obj_m オブジェクトマネージャー
* @param[out] act_m アクションマネージャー
*/
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

/**
* @brief 攻撃フラグ降ろす
* 
* @param[out] act_m アクションマネージャー
*/
void boss::Death::AtkCancel(ActionManager* const act_m) {
	boss_handL_->SetAttackFlag(false);
	boss_handR_->SetAttackFlag(false);
	boss_handL_->PlayDeathMotion();
	boss_handR_->PlayDeathMotion();
	act_m->SetSideShake(false);
	act_m->SetVerticalShake(false);
	death_state_ = DEATH_ACTION;
}

/**
* @brief 死亡時の動き
* 
* @param[out] act_m アクションマネージャー
*/
void boss::Death::DeathAction(ActionManager* const act_m) {
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

	const bool is_l_death_pos_ = l_pos_.x ==  DEATH_POS_X_ && l_pos_.y <= DEATH_POS_Y_ && l_pos_.z >= HAND_INITIAL_POS_Z_; /**< 左手が死亡座標にいるか */
	const bool is_r_death_pos_ = r_pos_.x == -DEATH_POS_X_ && r_pos_.y <= DEATH_POS_Y_ && r_pos_.z >= HAND_INITIAL_POS_Z_; /**< 右手が死亡座標にいるか */
	const bool is_l_death_rot_ = l_rot_.x >= DEATH_ROT_X_; /**< 左手が死亡回転軸か */
	const bool is_r_death_rot_ = r_rot_.x >= DEATH_ROT_X_; /**< 右手が死亡回転軸か */
	const bool is_l_death_ = is_l_death_pos_ && is_l_death_rot_; /**< 左手が死亡しているか */
	const bool is_r_death_ = is_r_death_pos_ && is_r_death_rot_; /**< 右手が死亡しているか */
	if (is_l_death_ && is_r_death_) {
		act_m->SetVerticalShake(true);
		death_state_ = ACTION_END;
	}
}