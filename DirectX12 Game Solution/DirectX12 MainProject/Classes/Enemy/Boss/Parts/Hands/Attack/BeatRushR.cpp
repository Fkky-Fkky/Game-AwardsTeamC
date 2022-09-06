#include "Classes/Enemy/Boss/Parts/Hands/Attack/BeatRushR.h"
#include "Classes/Enemy/Boss/Boss.h"

void BeatRushR::Update(const float deltaTime, const ObjectManager* const obj_m, Boss* const boss){
	pos_r_  = boss_handR_->GetHandPos();
	rote_r_ = boss_handR_->GetRotation();
	pos_l_  = boss_handL_->GetHandPos();
	rote_l_ = boss_handL_->GetRotation();

	time_delta_ = deltaTime;
	switch (action_state_) {
	case HAND_CHECK:	HandCheck(boss);	break;
	case READY:			Ready();			break;
	case ATTACK:		Attack(boss);		break;
	case RESET:			Reset();			break;
	case RETURN:		HandReturn();		break;
	case ACTION_END:	boss->ActionEnd();	break;
	}

	boss_handR_->SetHandPos(pos_r_);
	boss_handR_->SetHandRote(rote_r_);
	boss_handL_->SetHandPos(pos_l_);
	boss_handL_->SetHandRote(rote_l_);
}

void BeatRushR::HandCheck(const Boss* const boss) {	//手の状態を確認
	is_r_hand_broke_ = boss_handR_->GetHandHp() <= 0;
	is_l_hand_broke_ = boss_handL_->GetHandHp() <= 0;
	boss_handR_->SetHandMotion(HAND_MOTION::ROCK);
	boss_handL_->SetHandMotion(HAND_MOTION::ROCK);
	action_state_ = READY;
}

void BeatRushR::Ready() {	//両手を(ボスから見て)右側に構える
	if (is_r_hand_broke_) {
		r_ready_end_ = true;
	}
	else {
		bool is_r_hand_start_pos_x_ = pos_r_.x  <= R_START_POS_X_;
		bool is_r_hand_start_pos_z_ = pos_r_.z  <= 0.0f;
		bool is_r_hand_start_rot_	= rote_r_.x >= BEAT_HAND_ROCK_ROT_X_;
		pos_r_.x  = std::max(pos_r_.x  - MOVE_SPEED_X_ * time_delta_, R_START_POS_X_);
		pos_r_.z  = std::max(pos_r_.z  - MOVE_SPEED_Z_ * time_delta_, 0.0f);
		rote_r_.x = std::min(rote_r_.x + ROTE_SPEED_   * time_delta_, BEAT_HAND_ROCK_ROT_X_);
		r_ready_end_ = is_r_hand_start_pos_x_ && is_r_hand_start_pos_z_ && is_r_hand_start_rot_;
	}

	if (is_l_hand_broke_) {
		l_ready_end_ = true;
	}
	else {
		bool is_l_hand_start_pos_x_ = pos_l_.x  <= L_START_POS_X_;
		bool is_l_hand_start_pos_z_ = pos_r_.z	<= 0.0f;
		bool is_l_hand_start_rot_	= rote_l_.x <= BEAT_HAND_ROCK_ROT_X_;
		pos_l_.x  = std::max(pos_l_.x  - MOVE_SPEED_X_ * time_delta_, L_START_POS_X_);
		pos_l_.z  = std::max(pos_l_.z  - MOVE_SPEED_Z_ * time_delta_, 0.0f);
		rote_l_.x = std::min(rote_l_.x + ROTE_SPEED_   * time_delta_, BEAT_HAND_ROCK_ROT_X_);
		l_ready_end_ = is_l_hand_start_pos_x_ && is_l_hand_start_pos_z_ && is_l_hand_start_rot_;
	}

	if (r_ready_end_ && l_ready_end_) {
		action_state_ = ATTACK;
	}
}

void BeatRushR::Attack(const Boss* const boss) {	//攻撃関数呼び出し
	wait_time_ = std::min(wait_time_ + time_delta_, WAIT_TIME_MAX_);

	BeatR(boss);
	if (wait_time_ >= WAIT_TIME_MAX_) {
		BeatL(boss);
	}

	if (is_r_attack_end_ && is_l_attack_end_) {
		action_state_ = RESET;
	}
}

void BeatRushR::BeatR(const Boss* const boss) {	//右手叩きつけ攻撃
	if (is_r_hand_broke_) {
		is_r_attack_end_ = true;
		return;
	}
	if (!r_hand_up_flag_) {
		boss_handR_->SetAttackFlag(true);
		r_beat_time_ += time_delta_;
		pos_r_.y += BEAT_SPEED_ * r_beat_time_ - HALF_ * BEAT_GRAVITY_ * r_beat_time_ * r_beat_time_;
	}
	else {
		boss_handR_->SetVerticalShakeFlag(false);
		boss_handR_->SetAttackFlag(false);
		pos_r_.y = std::min(pos_r_.y + MOVE_SPEED_X_ * time_delta_, HAND_INITIAL_POS_Y_);
		pos_r_.x = std::min(pos_r_.x + MOVE_SPEED_X_ * time_delta_, r_move_dest_x_);
	}

	if (pos_r_.y <= HAND_ROCK_LIMIT_POS_Y_) {
		pos_r_.y  = HAND_ROCK_LIMIT_POS_Y_;
		boss_handR_->SetVerticalShakeFlag(true);
		boss->PlayBeatSE();
		boss->PlayBeatEffect(SimpleMath::Vector3(pos_r_.x, pos_r_.y - HAND_ROCK_LIMIT_POS_Y_, pos_r_.z));
		r_hand_up_flag_ = true;
		r_move_dest_x_ = std::min(pos_r_.x + ADD_DISTANCE_, HAND_RETURN_POS_X_);
	}

	if (pos_r_.y == HAND_INITIAL_POS_Y_ &&
		pos_r_.x >= r_move_dest_x_) {	//手が上に上がった時
		r_hand_up_flag_ = false;
		r_beat_time_ = 0.0f;
	}
	is_r_attack_end_ = pos_r_.x >= HAND_RETURN_POS_X_;
}

void BeatRushR::BeatL(const Boss* const boss) {	//左手叩きつけ攻撃
	if (is_l_hand_broke_) {
		is_l_attack_end_ = true;
		return;
	}
	if (!l_hand_up_flag_) {
		boss_handL_->SetAttackFlag(true);
		l_beat_time_ += time_delta_;
		pos_l_.y += BEAT_SPEED_ * l_beat_time_ - HALF_ * BEAT_GRAVITY_ * l_beat_time_ * l_beat_time_;
	}
	else {
		boss_handL_->SetVerticalShakeFlag(false);
		boss_handL_->SetAttackFlag(false);
		pos_l_.y = std::min(pos_l_.y + MOVE_SPEED_X_ * time_delta_, HAND_INITIAL_POS_Y_);
		pos_l_.x = std::min(pos_l_.x + MOVE_SPEED_X_ * time_delta_, l_move_dest_x_);
	}

	if (pos_l_.y <= HAND_ROCK_LIMIT_POS_Y_) {
		pos_l_.y  = HAND_ROCK_LIMIT_POS_Y_;
		boss_handL_->SetVerticalShakeFlag(true);
		boss->PlayBeatSE();
		boss->PlayBeatEffect(SimpleMath::Vector3(pos_l_.x, pos_l_.y - HAND_ROCK_LIMIT_POS_Y_, pos_l_.z));
		l_hand_up_flag_ = true;
		l_move_dest_x_ = std::min(pos_l_.x + ADD_DISTANCE_, HAND_RETURN_POS_X_);
	}

	if (pos_l_.y == HAND_INITIAL_POS_Y_ && 
		pos_l_.x >= l_move_dest_x_) {
		l_hand_up_flag_ = false;
		l_beat_time_ = 0.0f;
	}
	is_l_attack_end_ = pos_l_.x >= HAND_RETURN_POS_X_;
}

void BeatRushR::Reset() {	//手を画面外へ移動
	boss_handR_->SetAttackFlag(false);
	boss_handR_->SetHandMotion(HAND_MOTION::WAIT_MOTION);
	pos_r_.x  = -HAND_RETURN_POS_X_;
	pos_r_.y  = HAND_INITIAL_POS_Y_;
	pos_r_.z  = HAND_INITIAL_POS_Z_;
	rote_r_.x = HAND_INITIAL_ROT_X_;
	
	boss_handL_->SetAttackFlag(false);
	boss_handL_->SetHandMotion(HAND_MOTION::WAIT_MOTION);
	pos_l_.x  = HAND_RETURN_POS_X_;
	pos_l_.y  = HAND_INITIAL_POS_Y_;
	pos_l_.z  = HAND_INITIAL_POS_Z_;
	rote_l_.x = HAND_INITIAL_ROT_X_;
	action_state_ = RETURN;
}

void BeatRushR::HandReturn() {	//画面外から初期位置へ移動
	if (is_r_hand_broke_) {
		is_r_return_end_ = true;
	}
	else {
		pos_r_.x = std::min(pos_r_.x + MOVE_SPEED_X_ * time_delta_, HAND_R_INITIAL_POS_X_);
		is_r_return_end_ = pos_r_.x >= HAND_R_INITIAL_POS_X_;
	}

	if (is_l_hand_broke_) {
		is_l_return_end_ = true;
	}
	else {
		pos_l_.x = std::max(pos_l_.x - MOVE_SPEED_X_ * time_delta_, HAND_L_INITIAL_POS_X_);
		is_l_return_end_ = pos_l_.x <= HAND_L_INITIAL_POS_X_;
	}
	
	if (is_r_return_end_ && is_l_return_end_) {
		action_state_ = ACTION_END;
	}
}