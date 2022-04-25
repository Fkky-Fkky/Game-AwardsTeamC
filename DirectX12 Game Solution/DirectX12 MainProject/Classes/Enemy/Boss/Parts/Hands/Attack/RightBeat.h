#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAttack.h"

using namespace DirectX;

class RightBeat : public BossAttack {
public:
	RightBeat() {
		slap_time = 0.0f;
		time_delta = 0.0f;
		beat_time = 0.0f;
		wait_time = 0.0f;
		getposflag = false;
		boss_action_state = 0;
		hand_return_flag = false;
	}
	virtual void Update(const float deltaTime, SimpleMath::Vector3 player_pos);

private:

	void HandMove(SimpleMath::Vector3 player_pos);
	void RightBeatAttack();
	void HandReturn();


	float slap_time;
	float time_delta;
	float beat_time;
	float wait_time;

	bool getposflag;
	bool hand_return_flag;
	SimpleMath::Vector3 pos;
	SimpleMath::Vector3 rote;
	SimpleMath::Vector3 move_pos;

	const float INITIAL_POS_X = -5.0f;
	const float INITIAL_POS_Y = 5.0f;

	int boss_action_state;
	enum BOSS_ACTION_STATE {
		MOVE,
		ATTACK,
		RETURN_POSITION,
		ACTION_END
	};

};