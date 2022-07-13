#include "Classes/Enemy/Boss/Parts/Hands/Attack/LeftBeat.h"
#include "Classes/Enemy/Boss/Boss.h"
#include "Classes/Collision/ObjectManager.h"

void LeftBeat::Update(const float deltaTime, ObjectManager* obj_m, Boss* boss) {
	pos_  = boss_handL_->GetHandPos();
	rote_ = boss_handL_->GetRotation();

	time_delta_ = deltaTime;

	switch (boss_action_state_) {
	case HAND_CHECK:	HandCheck(boss);		break;
	case READY:			Ready(obj_m);			break;
	case ATTACK:		LeftBeatAttack(boss);	break;
	case RETURN:		HandReturn();			break;
	case ACTION_END:	boss->ActionEnd();		break;
	}

	boss_handL_->SetHandPos(pos_);
	boss_handL_->SetHandRote(rote_);
}

void LeftBeat::HandCheck(Boss* boss) {	//Žè‚Ìó‘Ô‚ðŠm”F
	hand_state_ = boss->GetHandState();
	(!hand_state_) ? boss_handL_->SetHandMotion(HAND_MOTION::ROCK) : boss_handL_->SetHandMotion(HAND_MOTION::PAPER);		
	boss_action_state_ = READY;
}

void LeftBeat::Ready(ObjectManager* obj_m) { //UŒ‚‚É•K—p‚È•Ï”‚ÌÝ’è
	if (!player_pos_get_flag_) {
		move_dest_ = obj_m->GetPlayerPos();
		player_pos_get_flag_ = true;
	}

	pos_.z = std::max(pos_.z - MOVE_SPEED_Z_ * time_delta_, 0.0f);

	if (pos_.x < move_dest_.x) {
		pos_.x = std::min(pos_.x + MOVE_SPEED_X_ * time_delta_, move_dest_.x);
	}
	else {
		pos_.x = std::max(pos_.x - MOVE_SPEED_X_ * time_delta_, move_dest_.x);
	}

	if (pos_.x == move_dest_.x) {
		boss_action_state_ = ATTACK;
	}
}

void LeftBeat::LeftBeatAttack(Boss* boss) { //’@‚«‚Â‚¯UŒ‚
	boss_handL_->SetAttackFlag(true);
	beat_time_ += time_delta_;
	float beat_ = BEAT_SPEED_* beat_time_ - HALF_ * BEAT_GRAVITY_ * beat_time_ * beat_time_;
	pos_.y += beat_;
	rote_.x = std::max(rote_.x - ROTE_SPEED_ * time_delta_, -XM_1DIV2PI);

	if (pos_.y <= 0.0f) {
		pos_.y  = 0.0f;
		boss->PlayBeatSE();
		boss->PlayBeatEffect(pos_);
		boss_handL_->SetAttackFlag(false);
		(!hand_state_) ? boss_handL_->SetHandMotion(HAND_MOTION::ROCK_BACK) : boss_handL_->SetHandMotion(HAND_MOTION::PAPER_BACK);
		boss_action_state_ = RETURN;
	}
}

void LeftBeat::HandReturn() { //Žè‚ð‰ŠúˆÊ’u‚ÖˆÚ“®
	wait_time_ += time_delta_;

	if (wait_time_ >= WAIT_TIME_MAX_) {
		if (pos_.x < HAND_L_INITIAL_POS_X_) {
			pos_.x = std::min(pos_.x + MOVE_SPEED_X_ * time_delta_, HAND_L_INITIAL_POS_X_);
		}
		else {
			pos_.x = std::max(pos_.x - MOVE_SPEED_X_ * time_delta_, HAND_L_INITIAL_POS_X_);
		}
		pos_.y  = std::min(pos_.y + MOVE_SPEED_Y_ * time_delta_, HAND_INITIAL_POS_Y_);
		pos_.z  = std::min(pos_.z + MOVE_SPEED_Z_ * time_delta_, HAND_INITIAL_POS_Z_);
		rote_.x = std::min(rote_.x + ROTE_SPEED_ * time_delta_, XM_PIDIV4);
	}

	if (pos_.y >= HAND_INITIAL_POS_Y_ &&
		pos_.x == HAND_L_INITIAL_POS_X_) {
		boss_action_state_ = ACTION_END;
	}
}