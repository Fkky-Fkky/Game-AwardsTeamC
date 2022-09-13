#pragma once

#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAttack.h"

class LeftSlap : public BossAttack {
public:
	LeftSlap() {
		action_state_ = HAND_CHECK;
		time_delta_   = 0.0f;
		slap_time_x_  = 0.0f;
		slap_time_y_  = 0.0f;
		wait_time_    = 0.0f;
		slap_speed_ = 0.0f;
		hand_state_	  = false;
		is_se_play_   = false;
		pos_  = SimpleMath::Vector3::Zero;
		rote_ = SimpleMath::Vector3::Zero;
	}
	virtual void Update(const float deltaTime, const ObjectManager* const obj_m, HandManager* const hand_m);

private:
	void HandCheck(const HandManager* const hand_m);
	void Ready(HandManager* const hand_m);
	void Wait(HandManager* const hand_m);
	void LeftSlapAttack(HandManager* const hand_m);
	void Reset();
	void HandReturn();

	int action_state_;
	
	float time_delta_;
	float slap_time_x_;
	float slap_time_y_;
	float wait_time_;
	float slap_speed_;
	bool hand_state_;
	bool is_se_play_;

	SimpleMath::Vector3 pos_;
	SimpleMath::Vector3 rote_;
};