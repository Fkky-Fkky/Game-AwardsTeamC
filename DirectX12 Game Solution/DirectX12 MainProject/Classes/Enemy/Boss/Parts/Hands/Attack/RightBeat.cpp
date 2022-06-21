#include "Classes/Enemy/Boss/Parts/Hands/Attack/RightBeat.h"
#include "Classes/Enemy/Boss/Boss.h"
#include "Classes/Collision/ObjectManager.h"

void RightBeat::Update(const float deltaTime, ObjectManager* obj_m, Boss* boss){
	pos_  = boss_handR_->GetHandPos();
	rote_ = boss_handR_->GetRotation();

	time_delta_ = deltaTime;

	switch (boss_action_state_)
	{
	case READY:		Ready(obj_m);		break;
	case ATTACK:	RightBeatAttack(boss);	break;
	case RETURN:	HandReturn();			break;
	case ACTION_END:
		boss_action_state_ = READY;
		boss->ActionEnd();
		break;
	}

	boss_handR_->SetHandPos(pos_);
	boss_handR_->SetHandRote(rote_);
}

void RightBeat::Ready(ObjectManager* obj_m) {	//UŒ‚‚É•K—p‚È•Ï”‚ÌÝ’è
	if (!player_pos_get_flag_) {
		move_dest_ = obj_m->GetPlayerPos();
		player_pos_get_flag_ = true;
	}

	pos_.z = std::max(pos_.z - MOVE_SPEED_Z_ * time_delta_, 0.0f);

	if (pos_.x < move_dest_.x)
		pos_.x = std::min(pos_.x + MOVE_SPEED_X_ * time_delta_, move_dest_.x);
	else
		pos_.x = std::max(pos_.x - MOVE_SPEED_X_ * time_delta_, move_dest_.x);

	if (pos_.x == move_dest_.x)
		boss_action_state_ = ATTACK;
}

void RightBeat::RightBeatAttack(Boss* boss) {	//’@‚«‚Â‚¯UŒ‚
	boss_handR_->SetAttackFlag(true);
	beat_time_ += time_delta_;
	float beat_ = BEAT_SPEED_ * beat_time_ - HALF_ * BEAT_GRAVITY_ * beat_time_ * beat_time_;
	pos_.y += beat_;
	rote_.x = std::max(rote_.x - ROTE_SPEED_ * time_delta_, -XM_1DIV2PI);

	if (pos_.y <= 0.0f) {
		pos_.y = 0.0f;
		boss->PlayBeatSE();
		boss->PlayBeatEffect(pos_);
		boss_handR_->SetAttackFlag(false);
		boss_action_state_ = RETURN;
	}
}

void RightBeat::HandReturn() {	//Žè‚ð‰ŠúˆÊ’u‚ÖˆÚ“®
	wait_time_ += time_delta_;

	if (wait_time_ >= WAIT_TIME_MAX_) {
		if (pos_.x < HAND_R_INITIAL_POS_X_)
			pos_.x = std::min(pos_.x + MOVE_SPEED_X_ * time_delta_, HAND_R_INITIAL_POS_X_);
		else
			pos_.x = std::max(pos_.x - MOVE_SPEED_X_ * time_delta_, HAND_R_INITIAL_POS_X_);

		pos_.y = std::min(pos_.y + MOVE_SPEED_Y_ * time_delta_, HAND_INITIAL_POS_Y_);
		pos_.z = std::min(pos_.z + MOVE_SPEED_Z_ * time_delta_, HAND_INITIAL_POS_Z_);
		rote_.x = std::min(rote_.x + ROTE_SPEED_ * time_delta_, XM_PIDIV4);
	}

	if (pos_.y >= HAND_INITIAL_POS_Y_ && pos_.x == HAND_R_INITIAL_POS_X_) {
		wait_time_ = 0.0f;
		beat_time_ = 0.0f;

		player_pos_get_flag_ = false;
		boss_action_state_ = ACTION_END;
	}
}