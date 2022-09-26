#include "Classes/Enemy/Boss/Parts/Hands/Attack/LeftBeat.h"
#include "Classes/Enemy/Boss/Parts/Hands/ActionManager.h"
#include "Classes/Object/ObjectManager.h"

/**
* @brief 攻撃処理更新
*
* @param[in] deltaTime 時間
* @param[out] obj_m オブジェクトマネージャー
* @param[out] act_m アクションマネージャー
*/
void boss::LeftBeat::Update(const float deltaTime, const ObjectManager* const obj_m, ActionManager* const act_m) {
	pos_  = boss_handL_->GetHandPos();
	rote_ = boss_handL_->GetRotation();

	time_delta_ = deltaTime;

	switch (boss_action_state_) {
	case HAND_CHECK:	HandCheck(obj_m);		break;
	case READY:			Ready(obj_m);			break;
	case ATTACK:		LeftBeatAttack(act_m);	break;
	case WAIT:			Wait(act_m);			break;
	case RETURN:		HandReturn();			break;
	case ACTION_END:	act_m->ActionEnd();		break;
	}

	boss_handL_->SetHandPos(pos_);
	boss_handL_->SetHandRote(rote_);
}

/**
* @brief 手の状態を確認
* 
* @param[out] obj_m オブジェクトマネージャー
*/
void boss::LeftBeat::HandCheck(const ObjectManager* const obj_m) {
	hand_state_ = obj_m->IsBossHandOpen();
	if (!hand_state_) {
		boss_handL_->SetHandMotion(HAND_MOTION::ROCK);
		limit_pos_y_ = HAND_ROCK_LIMIT_POS_Y_;
	}
	else {
		boss_handL_->SetHandMotion(HAND_MOTION::PAPER);
	}
	
	boss_action_state_ = READY;
}

/**
* @brief プレイヤーの座標に手を移動させる
* 
* @param[out] obj_m オブジェクトマネージャー
*/
void boss::LeftBeat::Ready(const ObjectManager* const obj_m) {
	const SimpleMath::Vector3 move_dest_ = obj_m->GetPlayerPos();
	const float DEST_SPEED_X_ = (is_player_pos_arrival_) ? CHASE_SPEED_ : MOVE_SPEED_X_; /**< 追跡するスピード */
	ready_time_  = std::min(ready_time_ + time_delta_, READY_TIME_MAX_);
	if (ready_time_ <= CHASE_PLAYER_TIME_) {
		if (pos_.x < move_dest_.x) {
			pos_.x = std::min(pos_.x + DEST_SPEED_X_ * time_delta_, move_dest_.x);
		}
		else {
			pos_.x = std::max(pos_.x - DEST_SPEED_X_ * time_delta_, move_dest_.x);
		}
	}

	if (pos_.x == move_dest_.x) {
		is_player_pos_arrival_ = true;
	}

	pos_.z  = std::max(pos_.z  - MOVE_SPEED_Z_ * time_delta_, ATTACK_POS_Z_);
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

/**
* @brief 叩きつけ攻撃
* 
* @param[out] act_m アクションマネージャー
*/
void boss::LeftBeat::LeftBeatAttack(ActionManager* const act_m) {
	boss_handL_->SetAttackFlag(true);
	beat_time_ += time_delta_;
	const float beat_ = BEAT_SPEED_ * beat_time_ - HALF_ * BEAT_GRAVITY_ * beat_time_ * beat_time_;
	pos_.y += beat_;

	if (pos_.y <= limit_pos_y_) {
		pos_.y  = limit_pos_y_;
		act_m->PlayBeatSE();
		act_m->PlayBeatEffect(SimpleMath::Vector3(pos_.x, pos_.y - limit_pos_y_, pos_.z));
		act_m->SetVerticalShake(true);
		boss_handL_->SetAttackFlag(false);
		boss_action_state_ = WAIT;
	}
}

/**
* @brief 攻撃後硬直
* 
* @param[out] act_m アクションマネージャー
*/
void boss::LeftBeat::Wait(ActionManager* const act_m) {
	act_m->SetVerticalShake(false);
	wait_time_ += time_delta_;
	if (wait_time_ >= WAIT_TIME_MAX_) {
		(!hand_state_) ? boss_handL_->SetHandMotion(HAND_MOTION::ROCK_BACK) : boss_handL_->SetHandMotion(HAND_MOTION::PAPER_BACK);
		boss_action_state_ = RETURN;
	}
}

/**
* @brief 手を初期位置へ移動
*/
void boss::LeftBeat::HandReturn() {
	if (pos_.x < HAND_L_INITIAL_POS_X_) {
		pos_.x = std::min(pos_.x + MOVE_SPEED_X_ * time_delta_, HAND_L_INITIAL_POS_X_);
	}
	else {
		pos_.x = std::max(pos_.x - MOVE_SPEED_X_ * time_delta_, HAND_L_INITIAL_POS_X_);
	}
	pos_.y  = std::min(pos_.y + MOVE_SPEED_Y_ * time_delta_, HAND_INITIAL_POS_Y_);
	pos_.z  = std::min(pos_.z + MOVE_SPEED_Z_ * time_delta_, HAND_INITIAL_POS_Z_);
	
	if (!hand_state_) {
		rote_.x = std::max(rote_.x - ROTE_SPEED_ * time_delta_, HAND_INITIAL_ROT_X_);
	}
	else {
		rote_.x = std::min(rote_.x + ROTE_SPEED_ * time_delta_, HAND_INITIAL_ROT_X_);
	}

	if (pos_.y >= HAND_INITIAL_POS_Y_ &&
		pos_.x == HAND_L_INITIAL_POS_X_) {
		boss_action_state_ = ACTION_END;
	}
}