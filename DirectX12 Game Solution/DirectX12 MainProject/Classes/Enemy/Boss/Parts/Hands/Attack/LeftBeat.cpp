#include "Classes/Enemy/Boss/Parts/Hands/Attack/LeftBeat.h"
#include "Classes/Enemy/Boss/Boss.h"

void LeftBeat::Update(const float deltaTime, SimpleMath::Vector3 player_pos, Boss* boss){
	pos_  = boss_handL_->GetHandPos();
	rote_ = boss_handL_->GetRotation();

	time_delta_ = deltaTime;

	switch (boss_action_state_)
	{
	case MOVE:
		HandMove(player_pos);
		break;

	case ATTACK:
		LeftBeatAttack(boss);
		break;

	case RETURN_POSITION:
		HandReturn();
		break;

	case ACTION_END:
		boss_action_state_ = MOVE;
		boss->ActionEnd();
		break;
	}

	boss_handL_->SetHandPos(pos_);
	boss_handL_->SetHandRote(rote_);
}

void LeftBeat::HandMove(SimpleMath::Vector3 player_pos) {
	if (!player_pos_get_flag_) {
		move_pos_ = player_pos;
		player_pos_get_flag_ = true;
	}

	pos_.z = std::max(pos_.z - 10.0f * time_delta_, 0.0f);

	if (pos_.x < move_pos_.x)
		pos_.x = std::min(pos_.x + MOVE_SPEED_X_ * time_delta_, move_pos_.x);
	else
		pos_.x = std::max(pos_.x - MOVE_SPEED_X_ * time_delta_, move_pos_.x);

	if (pos_.x == move_pos_.x)
		boss_action_state_ = ATTACK;
}

void LeftBeat::LeftBeatAttack(Boss* boss) {
	boss_handL_->SetAttackFlag(true);
	beat_time_ += time_delta_;
	pos_.y += BEAT_SPEED_ * beat_time_ - HALF_ * BEAT_GRAVITY_ * beat_time_ * beat_time_;
	rote_.x = std::max(rote_.x - ROTE_SPEED_ * time_delta_, -XM_1DIV2PI);

	if (pos_.y <= 0.0f) {
		pos_.y = 0.0f;
		boss->PlayBeatSE();
		DX12Effect.PlayOneShot("shock", pos_);
		boss_handL_->SetAttackFlag(false);
		boss_action_state_ = RETURN_POSITION;
	}
}

void LeftBeat::HandReturn() {
	wait_time_ += time_delta_;

	if (wait_time_ >= 0.2f) {
		if (pos_.x < HAND_L_INITIAL_POS_X_)
			pos_.x = std::min(pos_.x + MOVE_SPEED_X_ * time_delta_, HAND_L_INITIAL_POS_X_);
		else
			pos_.x = std::max(pos_.x - MOVE_SPEED_X_ * time_delta_, HAND_L_INITIAL_POS_X_);

		pos_.y  = std::min(pos_.y + MOVE_SPEED_Y_ * time_delta_, HAND_INITIAL_POS_Y_);
		pos_.z  = std::min(pos_.z + 10.0f * time_delta_, HAND_INITIAL_POS_Z_);
		rote_.x = std::min(rote_.x + ROTE_SPEED_ * time_delta_, XM_PIDIV4);
	}

	if (pos_.y >= HAND_INITIAL_POS_Y_ && pos_.x == HAND_L_INITIAL_POS_X_) {
		wait_time_ = 0.0f;
		beat_time_ = 0.0f;
		player_pos_get_flag_ = false;
		boss_action_state_ = ACTION_END;
	}
}