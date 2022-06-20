#pragma once

#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAttack.h"

class DoubleSlap : public BossAttack {
public:
	DoubleSlap() {
		r_pos_  = SimpleMath::Vector3::Zero;
		r_rote_ = SimpleMath::Vector3::Zero;
		l_pos_  = SimpleMath::Vector3::Zero;
		l_rote_ = SimpleMath::Vector3::Zero;

		action_state_ = READY;

		time_delta_	   = 0.0f;
		r_slap_time_x_ = 0.0f;
		r_slap_time_y_ = 0.0f;
		l_slap_time_x_ = 0.0f;
		l_slap_time_y_ = 0.0f;
		wait_time_	   = 0.0f;

		ready_flag_r_ = false;
		ready_flag_l_ = false;
	}

	~DoubleSlap() {};
	virtual void Update(const float deltaTime, SimpleMath::Vector3 player_pos, Boss* boss);

private:
	void Ready();
	void ReadyR();
	void ReadyL();
	void Attack();
	void SlapR();
	void SlapL();
	void Reset();
	void HandReturn();

	SimpleMath::Vector3 r_pos_;
	SimpleMath::Vector3 r_rote_;
	SimpleMath::Vector3 l_pos_;
	SimpleMath::Vector3 l_rote_;

	int action_state_;

	float time_delta_;
	float r_slap_time_x_;
	float r_slap_time_y_;
	float l_slap_time_x_;
	float l_slap_time_y_;

	float wait_time_;

	bool ready_flag_r_;
	bool ready_flag_l_;

	const float R_HAND_DEST_Y_  = 2.0f;
	const float L_HAND_DEST_Y_  = 8.0f;
	const float ATTACK_START_TIME_R_ = 0.5f;
	const float WAIT_TIME_MAX_		 = 1.0f;
};