#pragma once

#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAttack.h"

class BeatRushR : public BossAttack {
public:
	BeatRushR() {
		action_state_ = HAND_CHECK;
		r_beat_time_ = 0.0f;
		l_beat_time_ = 0.0f;
		r_add_pos_	 = 0.0f;
		l_add_pos_	 = 0.0f;
		time_delta_	 = 0.0f;
		wait_time_	 = 0.0f;
		r_ready_end_ = false;
		l_ready_end_ = false;
		r_hand_up_flag_ = false;
		l_hand_up_flag_ = false;
		is_r_hand_broke_ = false;
		is_l_hand_broke_ = false;
		hand_state_		 = false;
	}
	virtual void Update(const float deltaTime, ObjectManager* obj_m, Boss* boss);

private:
	void HandCheck(Boss* boss);
	void Ready();
	void Attack(Boss* boss);
	void BeatR(Boss* boss);
	void BeatL(Boss* boss);
	void Reset();
	void HandReturn();

	int action_state_;

	float r_beat_time_;
	float l_beat_time_; 
	float r_add_pos_;
	float l_add_pos_;
	float time_delta_;
	float wait_time_;

	bool r_hand_up_flag_;
	bool l_hand_up_flag_;
	bool r_ready_end_;
	bool l_ready_end_;
	bool is_r_hand_broke_;
	bool is_l_hand_broke_;
	bool hand_state_;

	SimpleMath::Vector3 pos_r_;
	SimpleMath::Vector3 rote_r_;
	SimpleMath::Vector3 pos_l_;
	SimpleMath::Vector3 rote_l_;

	const float R_START_POS_X_ = -15.0f;
	const float L_START_POS_X_ = -10.0f;
	const float LIMIT_POS_X_   = 30.0f;
	const float LIMIT_POS_Y_   = -1.0f;

	const float ROTATION_SPEED_ = 10.0f;
	const float WAIT_TIME_MAX_  = 0.5f;
	const float BEAT_L_START_TIME_ = 0.5f;
	const float ADD_POS_NUM_ = 13.0f;
};