#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAttack.h"

using namespace DirectX;

class LeftBeat : public BossAttack {
public:
	LeftBeat() {
		time_delta = 0.0f;
		beat_time = 0.0f;
		wait_time = 0.0f;
		player_pos_get_flag = false;
		boss_action_state = 0;
	}
	virtual void Update(const float deltaTime, SimpleMath::Vector3 player_pos, bool& attack_flag);

private:
	void HandMove(SimpleMath::Vector3 player_pos);
	void LeftBeatAttack();
	void HandReturn();


	float time_delta;
	float beat_time;
	float wait_time;

	bool player_pos_get_flag;
	SimpleMath::Vector3 pos;
	SimpleMath::Vector3 rote;
	SimpleMath::Vector3 move_pos;


	int boss_action_state;
	enum BOSS_ACTION_STATE {
		MOVE,
		ATTACK,
		RETURN_POSITION,
		ACTION_END
	};
};