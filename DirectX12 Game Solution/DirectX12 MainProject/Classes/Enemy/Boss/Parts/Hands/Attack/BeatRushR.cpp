#include "Classes/Enemy/Boss/Parts/Hands/Attack/BeatRushR.h"
#include "Classes/Enemy/Boss/Boss.h"

void BeatRushR::Update(const float deltaTime, SimpleMath::Vector3 player_pos, Boss* boss){
	pos_r  = boss_handR_->GetHandPos();
	rote_r = boss_handR_->GetRotation();
	pos_l  = boss_handL_->GetHandPos();
	rote_l = boss_handL_->GetRotation();

	time_delta = deltaTime;
	switch (attack_state) {
	case READY:
		Ready();
		break;

	case ATTACK:
		Attack();
		break;

	case RESET:
		Reset();
		break;

	case ACTION_END:
		attack_state = READY;
		boss->ActionEnd();
	}

	boss_handR_->SetHandPos(pos_r);
	boss_handR_->SetHandRote(rote_r);
	boss_handL_->SetHandPos(pos_l);
	boss_handL_->SetHandRote(rote_l);
}

void BeatRushR::Ready() {
	pos_r.x = std::max(pos_r.x - MOVE_SPEED_X * time_delta, R_START_POS_X);
	pos_l.x = std::max(pos_l.x - MOVE_SPEED_X * time_delta, L_START_POS_X);
	rote_r.x = std::max(rote_r.x - ROTATION_SPEED * time_delta, -XM_1DIV2PI);
	rote_l.x = std::max(rote_l.x - ROTATION_SPEED * time_delta, -XM_1DIV2PI);
	if (pos_l.x == L_START_POS_X) {
		attack_state = ATTACK;
	}
}

void BeatRushR::Attack() {
	BeatR();

	wait_time = std::min(wait_time + time_delta, WAIT_TIME_LIMIT);
	if (wait_time >= BEAT_L_START_TIME) {
		BeatL();
	}

	if (pos_l.x >= LIMIT_POS_X) {
		attack_state = RESET;
	}
}

void BeatRushR::BeatR() {
	const float MOVE_POS = r_add_pos + R_START_POS_X;

	if (!r_hand_up_flag) {
		boss_handR_->SetAttackFlag(true);
		r_beat_time += time_delta;
		pos_r.y += BEAT_SPEED * r_beat_time - HALF * BEAT_GRAVITY * r_beat_time * r_beat_time;
	}
	else {
		boss_handR_->SetAttackFlag(false);
		pos_r.y = std::min(pos_r.y + MOVE_SPEED_X * time_delta, HAND_INITIAL_POS_Y);
		pos_r.x = std::min(pos_r.x + MOVE_SPEED_X * time_delta, MOVE_POS);
	}

	if (pos_r.y <= LIMIT_POS_Y) {
		pos_r.y  = LIMIT_POS_Y;
		r_hand_up_flag = true;
		r_add_pos += ADD_POS_NUM;
	}

	if (pos_r.y == HAND_INITIAL_POS_Y && 
		pos_r.x == MOVE_POS) {
		r_hand_up_flag = false;
		r_beat_time = 0.0f;
	}
}

void BeatRushR::BeatL() {
	const float MOVE_POS = l_add_pos + L_START_POS_X;

	if (!l_hand_up_flag) {
		boss_handL_->SetAttackFlag(true);
		l_beat_time += time_delta;
		pos_l.y += BEAT_SPEED * l_beat_time - HALF * BEAT_GRAVITY * l_beat_time * l_beat_time;
	}
	else {
		boss_handL_->SetAttackFlag(false);
		pos_l.y = std::min(pos_l.y + MOVE_SPEED_X * time_delta, HAND_INITIAL_POS_Y);
		pos_l.x = std::min(pos_l.x + MOVE_SPEED_X * time_delta, MOVE_POS);
	}

	if (pos_l.y <= LIMIT_POS_Y) {
		pos_l.y  = LIMIT_POS_Y;
		l_hand_up_flag = true;
		l_add_pos += ADD_POS_NUM;
	}

	if (pos_l.y == HAND_INITIAL_POS_Y && 
		pos_l.x == MOVE_POS) {
		l_hand_up_flag = false;
		l_beat_time = 0.0f;
	}
}

void BeatRushR::Reset() {
	boss_handR_->SetAttackFlag(false);
	boss_handL_->SetAttackFlag(false);
	if (pos_l.x >= LIMIT_POS_X) {
		pos_r.x  = RETURN_POS_X;
	}

	pos_r.x = std::min(pos_r.x + MOVE_SPEED_X * time_delta, HAND_R_INITIAL_POS_X);
	pos_l.x = std::max(pos_l.x - MOVE_SPEED_X * time_delta, HAND_L_INITIAL_POS_X);
	pos_r.y = HAND_INITIAL_POS_Y;
	pos_l.y = HAND_INITIAL_POS_Y;
	rote_r.x = XM_PIDIV4;
	rote_l.x = XM_PIDIV4;
	if (pos_r.x == HAND_R_INITIAL_POS_X &&
		pos_l.x == HAND_L_INITIAL_POS_X) {
		attack_state = ACTION_END;
	}
}