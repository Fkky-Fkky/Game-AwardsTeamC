#pragma once

#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAttack.h"

class LeftBeat : public BossAttack {
public:
	LeftBeat() {
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
	virtual void Update(const float deltaTime, const ObjectManager* const obj_m, HandManager* const hand_m);

private:
	void HandCheck(const HandManager* const hand_m);
	void Ready(const ObjectManager* const obj_m);
	void LeftBeatAttack(HandManager* const hand_m);
	void Wait(HandManager* const hand_m);
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