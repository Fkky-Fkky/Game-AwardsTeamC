#include "Classes/Enemy/Boss/Parts/Hands/Attack/BeatRush.h"
#include "Classes/Enemy/Boss/Parts/Hands/ActionManager.h"

/**
* @brief 攻撃処理更新
* 
* @param[in] deltaTime 時間
* @param[in] obj_m オブジェクトマネージャー
* @param[out] act_m アクションマネージャー
*/
void boss::BeatRush::Update(const float deltaTime, const ObjectManager* const obj_m, ActionManager* const act_m) {
	r_pos_  = boss_handR_->GetHandPos();
	r_rote_ = boss_handR_->GetRotation();
	l_pos_  = boss_handL_->GetHandPos();
	l_rote_ = boss_handL_->GetRotation();

	time_delta_ = deltaTime;
	switch (action_state_) {
	case HAND_CHECK:	HandCheck();		break;
	case READY:			Ready();			break;
	case ATTACK:		Attack(act_m);		break;
	case RESET:			Reset();			break;
	case RETURN:		HandReturn();		break;
	case ACTION_END:	act_m->ActionEnd();	break;
	}

	boss_handR_->SetHandPos(r_pos_);
	boss_handR_->SetHandRote(r_rote_);
	boss_handL_->SetHandPos(l_pos_);
	boss_handL_->SetHandRote(l_rote_);
}

/**
* @brief 手のモーション設定
*/
void boss::BeatRush::HandCheck() {
	boss_handR_->SetHandMotion(HAND_MOTION::ROCK);
	boss_handL_->SetHandMotion(HAND_MOTION::ROCK);
	action_state_ = READY;
}

/**
* @brief 両手を(ボスから見て)右側に構える
*/
void boss::BeatRush::Ready() {
	bool is_r_hand_start_pos_x_ = r_pos_.x  <= R_START_POS_X_;
	bool is_r_hand_start_pos_z_ = r_pos_.z  <= ATTACK_POS_Z_;
	bool is_r_hand_start_rot_	= r_rote_.x >= BEAT_HAND_ROCK_ROT_X_;
	bool r_ready_end_ = is_r_hand_start_pos_x_ && is_r_hand_start_pos_z_ && is_r_hand_start_rot_; 
	r_pos_.x  = std::max(r_pos_.x  - MOVE_SPEED_X_ * time_delta_, R_START_POS_X_);
	r_pos_.z  = std::max(r_pos_.z  - MOVE_SPEED_Z_ * time_delta_, ATTACK_POS_Z_);
	r_rote_.x = std::min(r_rote_.x + ROTE_SPEED_   * time_delta_, BEAT_HAND_ROCK_ROT_X_);
	
	bool is_l_hand_start_pos_x_ = l_pos_.x	<= L_START_POS_X_;
	bool is_l_hand_start_pos_z_ = r_pos_.z	<= ATTACK_POS_Z_;
	bool is_l_hand_start_rot_	= l_rote_.x <= BEAT_HAND_ROCK_ROT_X_;
	bool l_ready_end_ = is_l_hand_start_pos_x_ && is_l_hand_start_pos_z_ && is_l_hand_start_rot_;
	l_pos_.x  = std::max(l_pos_.x  - MOVE_SPEED_X_ * time_delta_, L_START_POS_X_);
	l_pos_.z  = std::max(l_pos_.z  - MOVE_SPEED_Z_ * time_delta_, ATTACK_POS_Z_);
	l_rote_.x = std::min(l_rote_.x + ROTE_SPEED_   * time_delta_, BEAT_HAND_ROCK_ROT_X_);
	

	if (r_ready_end_ && l_ready_end_) {
		action_state_ = ATTACK;
	}
}

/**
* @brief 攻撃関数呼び出し
* 
* @param[out] act_m アクションマネージャー
*/
void boss::BeatRush::Attack(ActionManager* const act_m) {
	wait_time_ = std::min(wait_time_ + time_delta_, WAIT_TIME_MAX_);

	BeatR(act_m);
	if (wait_time_ >= WAIT_TIME_MAX_) {
		BeatL(act_m);
	}

	if (is_r_attack_end_ && is_l_attack_end_) {
		action_state_ = RESET;
	}
}

/**
* @brief 右手叩きつけ攻撃
* 
* @param[out] act_m アクションマネージャー
*/
void boss::BeatRush::BeatR(ActionManager* const act_m) {
	if (!r_hand_up_flag_) {
		boss_handR_->SetAttackFlag(true);
		r_beat_time_ += time_delta_;
		r_pos_.y += BEAT_SPEED_ * r_beat_time_ - HALF_ * BEAT_GRAVITY_ * r_beat_time_ * r_beat_time_;
	}
	else {
		act_m->SetVerticalShake(false);
		boss_handR_->SetAttackFlag(false);
		r_pos_.y = std::min(r_pos_.y + MOVE_SPEED_X_ * time_delta_, HAND_INITIAL_POS_Y_);
		r_pos_.x = std::min(r_pos_.x + MOVE_SPEED_X_ * time_delta_, r_move_dest_x_);
	}

	if (r_pos_.y <= HAND_ROCK_LIMIT_POS_Y_) {
		r_pos_.y  = HAND_ROCK_LIMIT_POS_Y_;
		act_m->SetVerticalShake(true);
		act_m->PlayBeatSE();
		act_m->PlayBeatEffect(SimpleMath::Vector3(r_pos_.x, r_pos_.y - HAND_ROCK_LIMIT_POS_Y_, r_pos_.z));
		r_hand_up_flag_ = true;
		r_move_dest_x_ = std::min(r_pos_.x + ADD_DISTANCE_, HAND_RETURN_POS_X_);
	}

	if (r_pos_.y == HAND_INITIAL_POS_Y_ &&
		r_pos_.x >= r_move_dest_x_) {	//手が上に上がった時
		r_hand_up_flag_ = false;
		r_beat_time_ = 0.0f;
	}
	is_r_attack_end_ = r_pos_.x >= HAND_RETURN_POS_X_;
}

/**
* @breif 左手叩きつけ攻撃
* 
* @param[out] act_m アクションマネージャー
*/
void boss::BeatRush::BeatL(ActionManager* const act_m) {
	if (!l_hand_up_flag_) {
		boss_handL_->SetAttackFlag(true);
		l_beat_time_ += time_delta_;
		l_pos_.y += BEAT_SPEED_ * l_beat_time_ - HALF_ * BEAT_GRAVITY_ * l_beat_time_ * l_beat_time_;
	}
	else {
		act_m->SetVerticalShake(false);
		boss_handL_->SetAttackFlag(false);
		l_pos_.y = std::min(l_pos_.y + MOVE_SPEED_X_ * time_delta_, HAND_INITIAL_POS_Y_);
		l_pos_.x = std::min(l_pos_.x + MOVE_SPEED_X_ * time_delta_, l_move_dest_x_);
	}

	if (l_pos_.y <= HAND_ROCK_LIMIT_POS_Y_) {
		l_pos_.y  = HAND_ROCK_LIMIT_POS_Y_;
		act_m->SetVerticalShake(true);
		act_m->PlayBeatSE();
		act_m->PlayBeatEffect(SimpleMath::Vector3(l_pos_.x, l_pos_.y - HAND_ROCK_LIMIT_POS_Y_, l_pos_.z));
		l_hand_up_flag_ = true;
		l_move_dest_x_ = std::min(l_pos_.x + ADD_DISTANCE_, HAND_RETURN_POS_X_);
	}

	if (l_pos_.y == HAND_INITIAL_POS_Y_ && 
		l_pos_.x >= l_move_dest_x_) {
		l_hand_up_flag_ = false;
		l_beat_time_ = 0.0f;
	}
	is_l_attack_end_ = l_pos_.x >= HAND_RETURN_POS_X_;
}

/**
* @brief 手を画面外へ移動
*/
void boss::BeatRush::Reset() {
	boss_handR_->SetAttackFlag(false);
	boss_handR_->SetHandMotion(HAND_MOTION::WAIT_MOTION);
	r_pos_.x  = -HAND_RETURN_POS_X_;
	r_pos_.y  = HAND_INITIAL_POS_Y_;
	r_pos_.z  = HAND_INITIAL_POS_Z_;
	r_rote_.x = HAND_INITIAL_ROT_X_;
	
	boss_handL_->SetAttackFlag(false);
	boss_handL_->SetHandMotion(HAND_MOTION::WAIT_MOTION);
	l_pos_.x  = HAND_RETURN_POS_X_;
	l_pos_.y  = HAND_INITIAL_POS_Y_;
	l_pos_.z  = HAND_INITIAL_POS_Z_;
	l_rote_.x = HAND_INITIAL_ROT_X_;
	action_state_ = RETURN;
}

/**
* @brief 画面外から手を初期位置へ移動
*/
void boss::BeatRush::HandReturn() {
	r_pos_.x = std::min(r_pos_.x + MOVE_SPEED_X_ * time_delta_, HAND_R_INITIAL_POS_X_);
	is_r_return_end_ = r_pos_.x >= HAND_R_INITIAL_POS_X_;

	l_pos_.x = std::max(l_pos_.x - MOVE_SPEED_X_ * time_delta_, HAND_L_INITIAL_POS_X_);
	is_l_return_end_ = l_pos_.x <= HAND_L_INITIAL_POS_X_;
	
	if (is_r_return_end_ && is_l_return_end_) {
		action_state_ = ACTION_END;
	}
}