#pragma once

#include "Classes/Enemy/Boss/Parts/Hands/BossHand.h"

class BossHandR : public BossHand {
public:
	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime, SimpleMath::Vector3 player_pos);
	void Render();

	void RightSlap();
	void RightBeat();

private:
	void HandMove();
	void RightBeatAttack();
	void HandReturn();
	
	float slap_time;
	float beat_time;
	float time_delta;
	float wait_time;
	bool hand_return_flag;
	bool getposflag;

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