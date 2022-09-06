#pragma once

#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAttack.h"

class RightBeat : public BossAttack {
public:
	RightBeat() {
		boss_action_state_ = HAND_CHECK;
		time_delta_ = 0.0f;
		beat_time_  = 0.0f;
		wait_time_  = 0.0f;
		ready_time_ = 0.0f;
		limit_pos_y_ = 0.0f;
		hand_state_ = false;
		pos_  = SimpleMath::Vector3::Zero;
		rote_ = SimpleMath::Vector3::Zero;
	}
	virtual void Update(const float deltaTime, const ObjectManager* const obj_m, Boss* const boss);

private:
	void HandCheck(const Boss* const boss);
	void Ready(const ObjectManager* const obj_m);
	void RightBeatAttack(const Boss* const boss);
	void Wait();
	void HandReturn();

	int boss_action_state_;

	float time_delta_;
	float beat_time_;
	float wait_time_;
	float ready_time_;
	float limit_pos_y_;

	bool hand_state_;
	
	SimpleMath::Vector3 pos_;
	SimpleMath::Vector3 rote_;

	const float CHASE_PLAYER_TIME_ = 2.0f;
	const float READY_TIME_MAX_	   = 3.0f;
	const float WAIT_TIME_MAX_	   = 1.5f;
};