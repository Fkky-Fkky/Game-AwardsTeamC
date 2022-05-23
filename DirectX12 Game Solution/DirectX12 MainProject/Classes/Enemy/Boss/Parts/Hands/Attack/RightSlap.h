#pragma once

#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAttack.h"

class RightSlap : public BossAttack {
public:
	RightSlap() {
		action_state_ = ATTACK;
		slap_time_	= 0.0f;
		time_delta_ = 0.0f;
		pos_  = SimpleMath::Vector3::Zero;
		rote_ = SimpleMath::Vector3::Zero;
	}
	virtual void Update(const float deltaTime, SimpleMath::Vector3 player_pos, Boss* boss);

private:
	void RightSlapAttack();
	void Reset();
	void HandReturn();

	int action_state_;

	float slap_time_;
	float time_delta_;

	SimpleMath::Vector3 pos_;
	SimpleMath::Vector3 rote_;
};