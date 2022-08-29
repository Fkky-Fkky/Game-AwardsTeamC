#include "Classes/Enemy/Boss/Parts/Hands/Attack/RightBeat.h"
#include "Classes/Enemy/Boss/Boss.h"
#include "Classes/Collision/ObjectManager.h"

void RightBeat::Update(const float deltaTime, ObjectManager* obj_m, Boss* boss){
	pos_  = boss_handR_->GetHandPos();
	rote_ = boss_handR_->GetRotation();

	time_delta_ = deltaTime;

	switch (boss_action_state_)	{
	case HAND_CHECK:	HandCheck(boss);		break;
	case READY:			Ready(obj_m);			break;
	case ATTACK:		RightBeatAttack(boss);	break;
	case WAIT:			Wait();					break;
	case RETURN:		HandReturn();			break;
	case ACTION_END:	boss->ActionEnd();		break;
	}

	boss_handR_->SetHandPos(pos_);
	boss_handR_->SetHandRote(rote_);
}

void RightBeat::HandCheck(Boss* boss) {	//手の状態を確認
	hand_state_ = boss->GetHandState();
	if (!hand_state_) {
		boss_handR_->SetHandMotion(HAND_MOTION::ROCK);
		limit_pos_y_ = HAND_ROCK_LIMIT_POS_Y_;
	}
	else {
		boss_handR_->SetHandMotion(HAND_MOTION::PAPER);
	}
	boss_action_state_ = READY;
}

void RightBeat::Ready(ObjectManager* obj_m) {	//プレイヤーの座標に手を移動させる
	SimpleMath::Vector3 move_dest_ = obj_m->GetPlayerPos();

	ready_time_ = std::min(ready_time_ + time_delta_, READY_TIME_MAX_);
	if (ready_time_ <= CHASE_PLAYER_TIME_) {
		if (pos_.x < move_dest_.x) {
			pos_.x = std::min(pos_.x + MOVE_SPEED_X_ * time_delta_, move_dest_.x);
		}
		else {
			pos_.x = std::max(pos_.x - MOVE_SPEED_X_ * time_delta_, move_dest_.x);
		}
	}

	pos_.z  = std::max(pos_.z -  MOVE_SPEED_Z_ * time_delta_, 0.0f);
	if (!hand_state_) {
		rote_.x = std::min(rote_.x + ROTE_SPEED_ * time_delta_, BEAT_HAND_ROCK_ROT_X_);
	}
	else {
		rote_.x = std::max(rote_.x - ROTE_SPEED_ * time_delta_, 0.0f);
	}

	if (ready_time_ >= READY_TIME_MAX_) {
		boss_action_state_ = ATTACK;
	}
}

void RightBeat::RightBeatAttack(Boss* boss) {	//叩きつけ攻撃
	boss_handR_->SetAttackFlag(true);
	beat_time_ += time_delta_;
	float beat_ = BEAT_SPEED_ * beat_time_ - HALF_ * BEAT_GRAVITY_ * beat_time_ * beat_time_;
	pos_.y += beat_;

	if (pos_.y <= limit_pos_y_) {
		pos_.y  = limit_pos_y_;
		boss->PlayBeatSE();
		boss->PlayBeatEffect(SimpleMath::Vector3(pos_.x, pos_.y - limit_pos_y_, pos_.z));
		boss_handR_->SetShakeFlag(true);
		boss_handR_->SetAttackFlag(false);
		boss_action_state_ = WAIT;
	}
}

void RightBeat::Wait() {	//硬直
	boss_handR_->SetShakeFlag(false);
	wait_time_ += time_delta_;
	if (wait_time_ >= WAIT_TIME_MAX_) {
		(!hand_state_) ? boss_handR_->SetHandMotion(HAND_MOTION::ROCK_BACK) : boss_handR_->SetHandMotion(HAND_MOTION::PAPER_BACK);
		boss_action_state_ = RETURN;
	}
}

void RightBeat::HandReturn() {	//手を初期位置へ移動
	if (pos_.x < HAND_R_INITIAL_POS_X_) {
		pos_.x = std::min(pos_.x + MOVE_SPEED_X_ * time_delta_, HAND_R_INITIAL_POS_X_);
	}
	else {
		pos_.x = std::max(pos_.x - MOVE_SPEED_X_ * time_delta_, HAND_R_INITIAL_POS_X_);
	}
	pos_.y  = std::min(pos_.y  + MOVE_SPEED_Y_ * time_delta_, HAND_INITIAL_POS_Y_);
	pos_.z  = std::min(pos_.z  + MOVE_SPEED_Z_ * time_delta_, HAND_INITIAL_POS_Z_);
	
	if (!hand_state_) {
		rote_.x = std::max(rote_.x - ROTE_SPEED_ * time_delta_, HAND_INITIAL_ROT_X_);
	}
	else {
		rote_.x = std::min(rote_.x + ROTE_SPEED_ * time_delta_, HAND_INITIAL_ROT_X_);
	}

	if (pos_.y >= HAND_INITIAL_POS_Y_ &&
		pos_.x == HAND_R_INITIAL_POS_X_) {
		boss_action_state_ = ACTION_END;
	}
}