#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAttack.h"

class BeatRushR : public BossAttack {
public:
	BeatRushR() {
		attack_state = 0;
		r_beat_time = 0.0f;
		l_beat_time = 0.0f;
		r_add_pos = 0.0f;
		l_add_pos = 0.0f;
		time_delta = 0.0f;
		wait_time_ = 0.0f;
		r_hand_up_flag = false;
		l_hand_up_flag = false;
	}
	virtual void Update(const float deltaTime, SimpleMath::Vector3 player_pos, Boss* boss);

private:
	void Ready();
	void Attack();
	void BeatR();
	void BeatL();
	void Reset();

	SimpleMath::Vector3 pos_r;
	SimpleMath::Vector3 rote_r;
	SimpleMath::Vector3 pos_l;
	SimpleMath::Vector3 rote_l;

	int attack_state;
	float r_beat_time;
	float l_beat_time; 
	float r_add_pos;
	float l_add_pos;
	float time_delta;
	float wait_time_;
	bool r_hand_up_flag;
	bool l_hand_up_flag;

	const float R_START_POS_X = -15.0f;
	const float L_START_POS_X = -10.0f;
	const float ROTATION_SPEED = 10.0f;
	const float WAIT_TIME_LIMIT = 1.0f;
	const float BEAT_L_START_TIME = 0.5f;
	const float LIMIT_POS_X = 25.0f;
	const float LIMIT_POS_Y = -1.0f;
	const float RETURN_POS_X = -20.0f;
	const float ADD_POS_NUM = 13.0f;
};