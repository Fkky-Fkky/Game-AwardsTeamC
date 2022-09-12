#pragma once

#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAttack.h"

class DoubleSlap : public BossAttack {
public:
	DoubleSlap() {
		action_state_  = HAND_CHECK;
		time_delta_	   = 0.0f;
		r_slap_speed_x_  = 0.0f;
		r_slap_time_y_ = 0.0f;
		l_slap_speed_x_ = 0.0f;
		l_slap_time_y_ = 0.0f;
		wait_time_	   = 0.0f;
		ready_end_r_ = false;
		ready_end_l_ = false;
		atk_end_r_	  = false;
		atk_end_l_	  = false;
		return_end_r_ = false;
		return_end_l_ = false;
		hand_state_	  = false;
		r_pos_  = SimpleMath::Vector3::Zero;
		r_rote_ = SimpleMath::Vector3::Zero;
		l_pos_  = SimpleMath::Vector3::Zero;
		l_rote_ = SimpleMath::Vector3::Zero;
	}

	~DoubleSlap() {};
	virtual void Update(const float deltaTime, const ObjectManager* const obj_m, HandManager* const hand_m);

private:
	void HandCheck(const HandManager* const hand_m);
	void Ready();
	void ReadyR();
	void ReadyL();
	void Attack();
	void SlapR();
	void SlapL();
	void Reset();
	void HandReturn();

	int action_state_;

	float time_delta_;
	float r_slap_speed_x_;
	float r_slap_time_y_;
	float l_slap_speed_x_;
	float l_slap_time_y_;
	float wait_time_;

	bool ready_end_r_;
	bool ready_end_l_;
	bool atk_end_r_;
	bool atk_end_l_;
	bool return_end_r_;
	bool return_end_l_;
	bool hand_state_;

	SimpleMath::Vector3 r_pos_;
	SimpleMath::Vector3 r_rote_;
	SimpleMath::Vector3 l_pos_;
	SimpleMath::Vector3 l_rote_;

	const float L_HAND_DEST_Y_  = 8.0f;
	const float ATTACK_START_TIME_R_ = 1.0f;
	const float WAIT_TIME_MAX_		 = 1.5f;
	const float ADD_SPEED_ = 40.0f;
	const float SLAP_SPEED_MAX_ = 80.0f;
};