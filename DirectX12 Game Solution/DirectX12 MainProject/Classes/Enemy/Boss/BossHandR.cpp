#include "Classes/Enemy/Boss/BossHandR.h"

void BossHandR::Initialize() {
	BossHand::Initialize(
		SimpleMath::Vector3(INITIAL_POS_X, INITIAL_POS_Y, 0.0f),
		SimpleMath::Vector3(XM_PIDIV4, 5.0f, 0.0f)
	);
	slap_time = 0.0f;
	beat_time = 0.0f;
	time_delta = 0.0f;
	wait_time = 0.0f;
	hand_return_flag = false;
	attack_flag = false;
	getposflag = false;
	boss_action_state = -1;
	player_pos_ = SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	move_pos = SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
}

void BossHandR::LoadAssets() {
	BossHand::LoadAssets(L"Boss/boss_hand_R.X");
}

void BossHandR::Update(const float deltaTime, SimpleMath::Vector3 player_pos) {
	BossHand::Update(deltaTime, player_pos);

	time_delta = deltaTime;

	//if (DXTK->KeyState->Right) {
	//	//r_hand_rote.y += 5.0f * deltaTime;
	//	//position.x += 40.0f * deltaTime;
	//	boss_action_state = 0;
	//}
	//if (DXTK->KeyState->Left) {
	//	//r_hand_rote.y -= 5.0f * deltaTime;
	//	position.x -= 40.0f * deltaTime;
	//}
	//if (DXTK->KeyState->Up) {
	//	//rotation.x += 5.0f * deltaTime;
	//	rotation.x = std::min(rotation.x + 1.0f * time_delta, XM_PIDIV2);
	//}
	//if (DXTK->KeyState->Down) {
	//	//rotation.x -= 5.0f * deltaTime;
	//	rotation.x = std::max(rotation.x - 1.0f * time_delta, -XM_1DIV2PI);
	//}

}

void BossHandR::Render() {
	BossHand::Render();
}

void BossHandR::RightSlap() {
	if (!hand_return_flag) {
		attack_flag = true;
		slap_time += time_delta;
		position.x -= SLAP_SPEED * slap_time - HALF * SLAP_GRAVITY * slap_time * slap_time;
		rotation.x = std::min(rotation.x + 1.0f * time_delta, XM_PIDIV2);
		position.y = std::max(position.y - 10.0f * time_delta, 2.0f);
	}
	else {
		position.x = std::min(position.x + 10.0f * time_delta, INITIAL_POS_X);
		rotation.x = std::max(rotation.x - 10.0f * time_delta, XM_PIDIV4);
		position.y = std::min(position.y + 10.0f * time_delta, INITIAL_POS_Y);
	}


	if (position.x >= 70.0f) {
		position.x = -30.0f;
		hand_return_flag = true;
		attack_flag = false;
	}

	if (position.x >= INITIAL_POS_X && hand_return_flag) {
		position.x = INITIAL_POS_X;
		slap_time = 0.0f;
		hand_return_flag = false;
		//bossattack->SetBossState(0);
	}
}

void BossHandR::RightBeat() {

	switch (boss_action_state)
	{
	case MOVE:
		HandMove();
		break;

	case ATTACK:
		RightBeatAttack();
		break;

	case RETURN_POSITION:
		HandReturn();
		break;

	case ACTION_END:
		boss_action_state = MOVE;
		//bossattack->SetBossState(0);
		break;
	}
}

void BossHandR::HandMove() {
	if (!getposflag) {
		move_pos = player_pos_;
		getposflag = true;
	}

	if (position.x < move_pos.x)
		position.x = std::min(position.x + 10.0f * time_delta, move_pos.x);
	else
		position.x = std::max(position.x - 10.0f * time_delta, move_pos.x);

	if (position.x == move_pos.x)
		boss_action_state = ATTACK;
}

void BossHandR::RightBeatAttack() {
	attack_flag = true;
	beat_time += time_delta;
	position.y += BEAT_SPEED * beat_time - HALF * BEAT_GRAVITY * beat_time * beat_time;
	rotation.x = std::max(rotation.x - 1.0f * time_delta, -XM_1DIV2PI);

	if (position.y <= 0.0f) {
		position.y = 0.0f;
		attack_flag = false;
		boss_action_state = RETURN_POSITION;
	}
}

void BossHandR::HandReturn() {
	wait_time += time_delta;

	if (wait_time >= 2.0f) {
		if (position.x < INITIAL_POS_X)
			position.x = std::min(position.x + 10.0f * time_delta, INITIAL_POS_X);
		else
			position.x = std::max(position.x - 10.0f * time_delta, INITIAL_POS_X);

		position.y = std::min(position.y + 5.0f * time_delta, INITIAL_POS_Y);
		rotation.x = std::min(rotation.x + 1.0f * time_delta, XM_PIDIV4);
	}

	if (position.y >= INITIAL_POS_Y && position.x == INITIAL_POS_X) {
		wait_time = 0.0f;
		beat_time = 0.0f;
		getposflag = false;
		boss_action_state = ACTION_END;
	}
}