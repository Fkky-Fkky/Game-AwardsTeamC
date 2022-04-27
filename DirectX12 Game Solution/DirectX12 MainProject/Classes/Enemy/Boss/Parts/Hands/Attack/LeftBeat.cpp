#include "Classes/Enemy/Boss/Parts/Hands/Attack/LeftBeat.h"

void LeftBeat::Update(const float deltaTime, SimpleMath::Vector3 player_pos, bool& attack_flag) {
	pos = boss_handL_->GetHandPos();
	rote = boss_handL_->GetRotation();

	time_delta = deltaTime;

	switch (boss_action_state)
	{
	case MOVE:
		HandMove(player_pos);
		break;

	case ATTACK:
		LeftBeatAttack();
		break;

	case RETURN_POSITION:
		HandReturn();
		break;

	case ACTION_END:
		attack_flag = true;
		boss_action_state = MOVE;
		break;
	}

	boss_handL_->SetHandPos(pos);
	boss_handL_->SetHandRote(rote);
}

void LeftBeat::HandMove(SimpleMath::Vector3 player_pos) {
	if (!player_pos_get_flag) {
		move_pos = player_pos;
		player_pos_get_flag = true;
	}

	if (pos.x < move_pos.x)
		pos.x = std::min(pos.x + 10.0f * time_delta, move_pos.x);
	else
		pos.x = std::max(pos.x - 10.0f * time_delta, move_pos.x);

	if (pos.x == move_pos.x)
		boss_action_state = ATTACK;
}

void LeftBeat::LeftBeatAttack() {
	boss_handL_->SetAttackFlag(true);
	beat_time += time_delta;
	pos.y += BEAT_SPEED * beat_time - HALF * BEAT_GRAVITY * beat_time * beat_time;
	rote.x = std::max(rote.x - 1.0f * time_delta, -XM_1DIV2PI);

	if (pos.y <= 0.0f) {
		pos.y = 0.0f;
		boss_handL_->SetAttackFlag(false);
		boss_action_state = RETURN_POSITION;
	}
}

void LeftBeat::HandReturn() {
	wait_time += time_delta;

	if (wait_time >= 2.0f) {
		if (pos.x < HAND_L_INITIAL_POS_X)
			pos.x = std::min(pos.x + 10.0f * time_delta, HAND_L_INITIAL_POS_X);
		else
			pos.x = std::max(pos.x - 10.0f * time_delta, HAND_L_INITIAL_POS_X);

		pos.y = std::min(pos.y + 5.0f * time_delta, HAND_INITIAL_POS_Y);
		rote.x = std::min(rote.x + 1.0f * time_delta, XM_PIDIV4);
	}

	if (pos.y >= HAND_INITIAL_POS_Y && pos.x == HAND_L_INITIAL_POS_X) {
		wait_time = 0.0f;
		beat_time = 0.0f;
		player_pos_get_flag = false;
		boss_action_state = ACTION_END;
	}
}