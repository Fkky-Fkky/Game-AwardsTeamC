#include "Classes/Enemy/Boss/Parts/Hands/Attack/RightSlap.h"
#include "Classes/Enemy/Boss/Parts/Hands/ActionManager.h"
#include "Classes/Object/ObjectManager.h"

/**
* @brief 攻撃処理更新
*
* @param[in] deltaTime 時間
* @param[in] obj_m オブジェクトマネージャー
* @param[out] act_m アクションマネージャー
*/
void boss::RightSlap::Update(const float deltaTime, const ObjectManager* const obj_m, ActionManager* const act_m) {
	pos_  = boss_handR_->GetHandPos();
	
	time_delta_ = deltaTime;
	switch (action_state_) {
	case HAND_CHECK:	HandCheck(obj_m);		break;
	case READY:			Ready(act_m);			break;
	case WAIT:			Wait(act_m);			break;
	case ATTACK:		RightSlapAttack(act_m);	break;
	case RESET:			Reset();				break;
	case RETURN:		HandReturn();			break;
	case ACTION_END:	act_m->ActionEnd();		break;
	}

	boss_handR_->SetHandPos(pos_);
}

/**
* @brief 手の状態を確認
*
* @param[in] obj_m オブジェクトマネージャー
*/
void boss::RightSlap::HandCheck(const ObjectManager* const obj_m) {
	hand_state_ = obj_m->IsBossHandOpen();
	(!hand_state_) ? boss_handR_->SetHandMotion(HAND_MOTION::ROCK) : boss_handR_->SetHandMotion(HAND_MOTION::PAPER);
	action_state_ = READY;
}

/**
* @brief 攻撃構え
*
* @param[out] act_m アクションマネージャー
*/
void boss::RightSlap::Ready(ActionManager* const act_m) {
	pos_.y += SlapY(time_delta_);
	pos_.z  = std::max(pos_.z  - MOVE_SPEED_Z_ * time_delta_, ATTACK_POS_Z_);
	if (pos_.y <= SLAP_POS_Y_) {
		pos_.y  = SLAP_POS_Y_;
		act_m->SetVerticalShake(true);
		action_state_ = WAIT;
	}
}

/**
* @brief 待機
*
* @param[aut] act_m アクションマネージャー
*/
void boss::RightSlap::Wait(ActionManager* const act_m) {
	act_m->SetVerticalShake(false);
	wait_time_ = std::min(wait_time_ + time_delta_, WAIT_TIME_MAX_);
	if (wait_time_ >= WAIT_TIME_MAX_) {
		action_state_ = ATTACK;
	}
}

/**
* @brief 右手薙ぎ払い攻撃
*
* @param[out] act_m アクションマネージャー
*/
void boss::RightSlap::RightSlapAttack(ActionManager* const act_m) {
	boss_handR_->SetAttackFlag(true);
	SlapAttackBase(time_delta_, act_m);
	pos_.x = std::min(pos_.x + slap_speed_ * time_delta_, HAND_LIMIT_POS_X_);

	if (pos_.x >= HAND_LIMIT_POS_X_) {
		act_m->SetSideShake(false);
		action_state_ = RESET;
	}
}

/**
* @brief　手を画面の反対側に移動
*/
void boss::RightSlap::Reset() {
	boss_handR_->SetAttackFlag(false);
	boss_handR_->SetHandMotion(HAND_MOTION::WAIT_MOTION);
	pos_.x  = -HAND_RETURN_POS_X_;
	pos_.y  = HAND_INITIAL_POS_Y_;
	pos_.z  = HAND_INITIAL_POS_Z_;
	action_state_ = RETURN;
}

/**
* @brief 初期位置へ移動
*/
void boss::RightSlap::HandReturn() {
	pos_.x = std::min(pos_.x + MOVE_SPEED_X_ * time_delta_, HAND_R_INITIAL_POS_X_);
	if (pos_.x >= HAND_R_INITIAL_POS_X_ ) {
		action_state_ = ACTION_END;
	}
}