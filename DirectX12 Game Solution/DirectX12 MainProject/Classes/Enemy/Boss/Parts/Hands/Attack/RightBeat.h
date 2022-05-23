#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAttack.h"

using namespace DirectX;

class RightBeat : public BossAttack {
public:
	RightBeat() {
		time_delta = 0.0f;
		beat_time_ = 0.0f;
		wait_time_ = 0.0f;
		player_pos_get_flag_ = false;
		boss_action_state = 0;
	}
	virtual void Update(const float deltaTime, SimpleMath::Vector3 player_pos, Boss* boss);

private:
	void HandMove(SimpleMath::Vector3 player_pos);
	void RightBeatAttack(Boss* boss);
	void HandReturn();


	float time_delta;
	float beat_time_;
	float wait_time_;

	bool player_pos_get_flag_;
	SimpleMath::Vector3 pos_;
	SimpleMath::Vector3 rote_;
	SimpleMath::Vector3 move_pos;


	int boss_action_state;
	enum BOSS_ACTION_STATE {
		MOVE,
		ATTACK,
		RETURN_POSITION,
		ACTION_END
	};

};