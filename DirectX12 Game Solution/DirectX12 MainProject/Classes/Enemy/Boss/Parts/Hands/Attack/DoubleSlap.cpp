#include "Classes/Enemy/Boss/Parts/Hands/Attack/DoubleSlap.h"
#include "Classes/Enemy/Boss/Parts/Hands/ActionManager.h"
#include "Classes/Object/ObjectManager.h"

/**
* @brief 攻撃処理更新
*
* @param[in] deltaTime 時間
* @param[out] obj_m オブジェクトマネージャー
* @param[out] act_m アクションマネージャー
*/
void boss::DoubleSlap::Update(const float deltaTime, const ObjectManager* const obj_m, ActionManager* const act_m)	{
	r_pos_  = boss_handR_->GetHandPos();
	l_pos_  = boss_handL_->GetHandPos();

	time_delta_ = deltaTime;

	switch (action_state_) {
	case HAND_CHECK:	HandCheck(obj_m);	break;
	case READY:			Ready(act_m);		break;
	case ATTACK:		Attack(act_m);		break;
	case RESET:			Reset();			break;
	case RETURN:		HandReturn();		break;
	case ACTION_END:	act_m->ActionEnd();	break;
	}

	boss_handR_->SetHandPos(r_pos_);
	boss_handL_->SetHandPos(l_pos_);
}

/**
* @brief 手の状態を確認、モーション設定
* 
* @param[out] obj_m オブジェクトマネージャー
*/
void boss::DoubleSlap::HandCheck(const ObjectManager* const obj_m) {
	hand_state_	= obj_m->IsBossHandOpen();
	if (!hand_state_) {
		boss_handR_->SetHandMotion(HAND_MOTION::ROCK);
		boss_handL_->SetHandMotion(HAND_MOTION::ROCK);
	}
	else { 
		boss_handR_->SetHandMotion(HAND_MOTION::PAPER); 
		boss_handL_->SetHandMotion(HAND_MOTION::PAPER);
	}
	
	action_state_ = READY;
}

/**
* @brief 攻撃構え
* 
* @param[out] act_m アクションマネージャー
*/
void boss::DoubleSlap::Ready(ActionManager* const act_m) {
	slap_y_ = SlapY(time_delta_);
	ReadyR();
	ReadyL();

	if (ready_end_r_ && ready_end_l_) {
		act_m->SetVerticalShake(true);
		action_state_ = ATTACK;
	}
}

/**
* @brief 右手構え
*/
void boss::DoubleSlap::ReadyR() {
	r_pos_.y += slap_y_;
	r_pos_.z  = std::max(r_pos_.z  - MOVE_SPEED_Z_ * time_delta_, ATTACK_POS_Z_);
	if (r_pos_.y <= SLAP_POS_Y_) {
		r_pos_.y  = SLAP_POS_Y_;
		ready_end_r_ = true;
	}
}

/**
* @brief 左手構え
*/
void boss::DoubleSlap::ReadyL() {
	l_pos_.y += slap_y_;
	l_pos_.z  = std::max(l_pos_.z  - MOVE_SPEED_Z_ * time_delta_, ATTACK_POS_Z_);
	if (l_pos_.y <= L_HAND_DEST_Y_) {
		l_pos_.y  = L_HAND_DEST_Y_;
		ready_end_l_ = true;
	}
}

/**
* @brief 薙ぎ払い攻撃
* 
* @param[out] act_m アクションマネージャー
*/
void boss::DoubleSlap::Attack(ActionManager* const act_m) {
	wait_time_ = std::min(wait_time_ + time_delta_, WAIT_TIME_MAX_);
	act_m->SetVerticalShake(false);

	if (wait_time_ >= ATTACK_START_TIME_R_) {
		SlapR(act_m);
	}

	if (wait_time_ >= WAIT_TIME_MAX_) {
		SlapL(act_m);
	}

	if (atk_end_r_ && atk_end_l_) {
		action_state_ = RESET;
	}
}

/**
* @brief 右手薙ぎ払い
* 
* @param[out] act_m アクションマネージャー
*/
void boss::DoubleSlap::SlapR(ActionManager* const act_m) {
	boss_handR_->SetAttackFlag(true);
	SlapAttackBase(time_delta_, act_m);
	r_pos_.x = std::min(r_pos_.x + slap_speed_ * time_delta_, HAND_LIMIT_POS_X_);
	if (r_pos_.x >= HAND_LIMIT_POS_X_) {
		atk_end_r_ = true;
		act_m->SetSideShake(false);
	}
}

/**
* @	左手薙ぎ払い
* 
* @param[out] act_m アクションマネージャー
*/
void boss::DoubleSlap::SlapL(ActionManager* const act_m) {
	boss_handL_->SetAttackFlag(true);
	l_slap_speed_x_ = std::min(l_slap_speed_x_ + ADD_SLAP_SPEED_ * time_delta_, SLAP_SPEED_MAX_X_);
	l_pos_.x		= std::max(l_pos_.x - l_slap_speed_x_ * time_delta_, -HAND_LIMIT_POS_X_);
	if (l_pos_.x <= -HAND_LIMIT_POS_X_) {
		atk_end_l_ = true;
	}
}

/**
* @brief それぞれの手を画面の反対へ移動
*/
void boss::DoubleSlap::Reset() {
	r_pos_.x  = -HAND_RETURN_POS_X_;
	r_pos_.y  = HAND_INITIAL_POS_Y_;
	r_pos_.z  = HAND_INITIAL_POS_Z_;
	boss_handR_->SetAttackFlag(false);
	boss_handR_->SetHandMotion(HAND_MOTION::WAIT_MOTION);

	l_pos_.x  = HAND_RETURN_POS_X_;
	l_pos_.y  = HAND_INITIAL_POS_Y_;
	l_pos_.z  = HAND_INITIAL_POS_Z_;
	boss_handL_->SetAttackFlag(false);
	boss_handL_->SetHandMotion(HAND_MOTION::WAIT_MOTION);

	action_state_ = RETURN;
}

/**
* @brief 手を初期座標に戻す
*/
void boss::DoubleSlap::HandReturn() {
	const bool is_r_hand_init_pos_ = r_pos_.x >= HAND_R_INITIAL_POS_X_; /**< 右手が初期座標にいるか */
	const bool is_l_hand_init_pos_ = l_pos_.x <= HAND_L_INITIAL_POS_X_; /**< 左手が初期座標にいるか */

	r_pos_.x = std::min(r_pos_.x + MOVE_SPEED_X_ * time_delta_, HAND_R_INITIAL_POS_X_);
	if (is_r_hand_init_pos_) {
		return_end_r_ = true;
	}

	l_pos_.x = std::max(l_pos_.x - MOVE_SPEED_X_ * time_delta_, HAND_L_INITIAL_POS_X_);
	if (is_l_hand_init_pos_) {
		return_end_l_ = true;
	}	

	if (return_end_r_ && return_end_l_) {
		action_state_ = ACTION_END;
	}
}