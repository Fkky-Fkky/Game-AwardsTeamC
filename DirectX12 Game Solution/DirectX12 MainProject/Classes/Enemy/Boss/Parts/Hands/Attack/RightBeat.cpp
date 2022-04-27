#include "Classes/Enemy/Boss/Parts/Hands/Attack/RightBeat.h"

void RightBeat::Update(const float deltaTime, SimpleMath::Vector3 player_pos){
	pos  = boss_handR_->GetHandPos();
	rote = boss_handR_->GetRotation();
	time_delta = deltaTime;
	switch (boss_action_state)
	{
	case MOVE:
		HandMove(player_pos);
		break;

	case ATTACK:
		RightBeatAttack();
		break;

	case RETURN_POSITION:
		HandReturn();
		break;

	case ACTION_END:
		boss_action_state = MOVE;
		break;
	}

	boss_handR_->SetHandPos(pos);
	boss_handR_->SetHandRote(rote);
}

void RightBeat::HandMove(SimpleMath::Vector3 player_pos) {
	if (!getposflag) {
		move_pos = player_pos;
		getposflag = true;
	}

	if (pos.x < move_pos.x)
		pos.x = std::min(pos.x + 10.0f * time_delta, move_pos.x);
	else
		pos.x = std::max(pos.x - 10.0f * time_delta, move_pos.x);

	if (pos.x == move_pos.x)
		boss_action_state = ATTACK;
}

void RightBeat::RightBeatAttack() {
	boss_handR_->SetAttackFlag(true);
	beat_time += time_delta;
	pos.y += BEAT_SPEED * beat_time - HALF * BEAT_GRAVITY * beat_time * beat_time;
	rote.x = std::max(rote.x - 1.0f * time_delta, -XM_1DIV2PI);

	if (pos.y <= 0.0f) {
		pos.y = 0.0f;
		boss_handR_->SetAttackFlag(false);
		boss_action_state = RETURN_POSITION;
	}
}

void RightBeat::HandReturn() {
	wait_time += time_delta;

	if (wait_time >= 2.0f) {
		if (pos.x < HAND_R_INITIAL_POS_X)
			pos.x = std::min(pos.x + 10.0f * time_delta, HAND_R_INITIAL_POS_X);
		else
			pos.x = std::max(pos.x - 10.0f * time_delta, HAND_R_INITIAL_POS_X);

		pos.y = std::min(pos.y + 5.0f * time_delta, HAND_R_INITIAL_POS_Y);
		rote.x = std::min(rote.x + 1.0f * time_delta, XM_PIDIV4);
	}

	if (pos.y >= HAND_R_INITIAL_POS_Y && pos.x == HAND_R_INITIAL_POS_X) {
		wait_time = 0.0f;
		beat_time = 0.0f;
		getposflag = false;
		boss_action_state = ACTION_END;
	}
}