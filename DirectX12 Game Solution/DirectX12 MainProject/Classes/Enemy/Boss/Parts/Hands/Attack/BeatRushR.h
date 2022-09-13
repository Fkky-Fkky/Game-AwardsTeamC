#pragma once

#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAttack.h"

class BeatRushR : public BossAttack {
public:
	BeatRushR() {
		action_state_ = HAND_CHECK;
		r_beat_time_ = 0.0f;
		l_beat_time_ = 0.0f;
		l_move_dest_x_	 = 0.0f;
		time_delta_	 = 0.0f;
		wait_time_	 = 0.0f;
		r_move_dest_x_ = 0.0f;
		r_hand_up_flag_ = false;
		l_hand_up_flag_ = false;
		is_r_attack_end_ = false;
		is_l_attack_end_ = false;
		is_r_return_end_ = false;
		is_l_return_end_ = false;
	}
	virtual void Update(const float deltaTime, const ObjectManager* const obj_m, HandManager* const hand_m);

private:
	void HandCheck();
	void Ready();
	void Attack(HandManager* const hand_m);
	void BeatR(HandManager* const hand_m);
	void BeatL(HandManager* const hand_m);
	void Reset();
	void HandReturn();

	int action_state_;

	float r_beat_time_;
	float l_beat_time_;
	float r_move_dest_x_;
	float l_move_dest_x_;
	float time_delta_;
	float wait_time_;

	bool r_hand_up_flag_;
	bool l_hand_up_flag_;
	bool is_r_attack_end_;
	bool is_l_attack_end_;
	bool is_r_return_end_;
	bool is_l_return_end_;

	SimpleMath::Vector3 pos_r_;
	SimpleMath::Vector3 rote_r_;
	SimpleMath::Vector3 pos_l_;
	SimpleMath::Vector3 rote_l_;

	const float R_START_POS_X_ = -15.0f;
	const float L_START_POS_X_ = -10.0f;

	const float WAIT_TIME_MAX_  = 0.5f;
	const float BEAT_L_START_TIME_ = 0.5f;
	const float ADD_DISTANCE_ = 13.0f;
};