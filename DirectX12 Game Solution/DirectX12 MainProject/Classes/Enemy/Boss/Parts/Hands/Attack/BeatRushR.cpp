#include "Classes/Enemy/Boss/Parts/Hands/Attack/BeatRushR.h"
#include "Classes/Enemy/Boss/Boss.h"

void BeatRushR::Update(const float deltaTime, SimpleMath::Vector3 player_pos, Boss* boss){
	pos_r_  = boss_handR_->GetHandPos();
	rote_r_ = boss_handR_->GetRotation();
	pos_l_  = boss_handL_->GetHandPos();
	rote_l_ = boss_handL_->GetRotation();

	time_delta_ = deltaTime;
	switch (action_state_) {
	case READY:		Ready();		break;
	case ATTACK:	Attack(boss);	break;
	case RESET:		Reset();		break;
	case RETURN:	HandReturn();	break;
	case ACTION_END:
		action_state_ = READY;
		boss->ActionEnd();			break;
	}

	boss_handR_->SetHandPos(pos_r_);
	boss_handR_->SetHandRote(rote_r_);
	boss_handL_->SetHandPos(pos_l_);
	boss_handL_->SetHandRote(rote_l_);
}

void BeatRushR::Ready() {	//両手を(ボスから見て)右側に構える
	pos_r_.x  = std::max(pos_r_.x - MOVE_SPEED_X_ * time_delta_, R_START_POS_X_);
	pos_l_.x  = std::max(pos_l_.x - MOVE_SPEED_X_ * time_delta_, L_START_POS_X_);
	rote_r_.x = std::max(rote_r_.x - ROTATION_SPEED_ * time_delta_, -XM_1DIV2PI);
	rote_l_.x = std::max(rote_l_.x - ROTATION_SPEED_ * time_delta_, -XM_1DIV2PI);
	if (pos_l_.x == L_START_POS_X_) {
		action_state_ = ATTACK;
	}
}

void BeatRushR::Attack(Boss* boss) {	//攻撃関数呼び出し
	BeatR(boss);

	wait_time_ = std::min(wait_time_ + time_delta_, WAIT_TIME_MAX_);
	if (wait_time_ >= WAIT_TIME_MAX_) {
		BeatL(boss);
	}

	if (pos_l_.x >= LIMIT_POS_X_) {
		action_state_ = RESET;
	}
}

void BeatRushR::BeatR(Boss* boss) {	//右手叩きつけ攻撃
	const float MOVE_DEST_ = r_add_pos_ + R_START_POS_X_;

	if (!r_hand_up_flag_) {
		boss_handR_->SetAttackFlag(true);
		r_beat_time_ += time_delta_;
		pos_r_.y += BEAT_SPEED_ * r_beat_time_ - HALF_ * BEAT_GRAVITY_ * r_beat_time_ * r_beat_time_;
	}
	else {
		boss_handR_->SetAttackFlag(false);
		pos_r_.y = std::min(pos_r_.y + MOVE_SPEED_X_ * time_delta_, HAND_INITIAL_POS_Y_);
		pos_r_.x = std::min(pos_r_.x + MOVE_SPEED_X_ * time_delta_, MOVE_DEST_);
	}

	if (pos_r_.y <= LIMIT_POS_Y_) {
		pos_r_.y  = LIMIT_POS_Y_;
		boss->PlayBeatSE();
		boss->PlayBeatEffect(pos_r_);
		r_hand_up_flag_ = true;
		r_add_pos_ += ADD_POS_NUM_;
	}

	if (pos_r_.y == HAND_INITIAL_POS_Y_ && 
		pos_r_.x == MOVE_DEST_) {
		r_hand_up_flag_ = false;
		r_beat_time_ = 0.0f;
	}
}

void BeatRushR::BeatL(Boss* boss) {	//左手叩きつけ攻撃
	const float MOVE_DEST_ = l_add_pos_ + L_START_POS_X_;

	if (!l_hand_up_flag_) {
		boss_handL_->SetAttackFlag(true);
		l_beat_time_ += time_delta_;
		pos_l_.y += BEAT_SPEED_ * l_beat_time_ - HALF_ * BEAT_GRAVITY_ * l_beat_time_ * l_beat_time_;
	}
	else {
		boss_handL_->SetAttackFlag(false);
		pos_l_.y = std::min(pos_l_.y + MOVE_SPEED_X_ * time_delta_, HAND_INITIAL_POS_Y_);
		pos_l_.x = std::min(pos_l_.x + MOVE_SPEED_X_ * time_delta_, MOVE_DEST_);
	}

	if (pos_l_.y <= LIMIT_POS_Y_) {
		pos_l_.y  = LIMIT_POS_Y_;
		boss->PlayBeatSE();
		boss->PlayBeatEffect(pos_l_);
		l_hand_up_flag_ = true;
		l_add_pos_ += ADD_POS_NUM_;
	}

	if (pos_l_.y == HAND_INITIAL_POS_Y_ && 
		pos_l_.x == MOVE_DEST_) {
		l_hand_up_flag_ = false;
		l_beat_time_ = 0.0f;
	}
}

void BeatRushR::Reset() {	//画面外に座標固定
	boss_handR_->SetAttackFlag(false);
	boss_handL_->SetAttackFlag(false);
	pos_r_.x  = -HAND_RETURN_POS_X_;
	pos_l_.x  = HAND_RETURN_POS_X_;
	pos_r_.y  = HAND_INITIAL_POS_Y_;
	pos_l_.y  = HAND_INITIAL_POS_Y_;
	rote_r_.x = XM_PIDIV4;
	rote_l_.x = XM_PIDIV4;
	wait_time_ = 0.0f;
	action_state_ = RETURN;
}

void BeatRushR::HandReturn() {	//画面外から初期位置へ移動
	pos_r_.x = std::min(pos_r_.x + MOVE_SPEED_X_ * time_delta_, HAND_R_INITIAL_POS_X_);
	pos_l_.x = std::max(pos_l_.x - MOVE_SPEED_X_ * time_delta_, HAND_L_INITIAL_POS_X_);

	if (pos_r_.x == HAND_R_INITIAL_POS_X_ &&
		pos_l_.x == HAND_L_INITIAL_POS_X_) {
		action_state_ = ACTION_END;
	}
}