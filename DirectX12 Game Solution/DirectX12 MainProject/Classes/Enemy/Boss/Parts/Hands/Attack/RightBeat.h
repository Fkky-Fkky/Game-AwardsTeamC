#pragma once

#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAttack.h"

class RightBeat : public BossAttack {
public:
	RightBeat() {
		boss_action_state_ = READY;
		time_delta_ = 0.0f;
		beat_time_  = 0.0f;
		wait_time_  = 0.0f;
		player_pos_get_flag_ = false;
		pos_	   = SimpleMath::Vector3::Zero;
		rote_	   = SimpleMath::Vector3::Zero;
		move_dest_ = SimpleMath::Vector3::Zero;
	}
	virtual void Update(const float deltaTime, ObjectManager* obj_m, Boss* boss);

private:
	void Ready(ObjectManager* obj_m);
	void RightBeatAttack(Boss* boss);
	void HandReturn();

	int boss_action_state_;

	float time_delta_;
	float beat_time_;
	float wait_time_;

	bool player_pos_get_flag_;
	
	SimpleMath::Vector3 pos_;
	SimpleMath::Vector3 rote_;
	SimpleMath::Vector3 move_dest_;

	const float WAIT_TIME_MAX_ = 0.2f;
};