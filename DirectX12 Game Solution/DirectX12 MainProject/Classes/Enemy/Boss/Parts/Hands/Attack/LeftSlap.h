#pragma once

#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAttack.h"

class LeftSlap : public BossAttack {
public:
	LeftSlap() {
		action_state_ = ATTACK;
		slap_time_  = 0.0f;
		time_delta_ = 0.0f;
		is_se_play_ = false;
		pos_  = SimpleMath::Vector3::Zero;
		rote_ = SimpleMath::Vector3::Zero;
	}
	virtual void Update(const float deltaTime, SimpleMath::Vector3 player_pos, Boss* boss);

private:
	void LeftSlapAttack(Boss* boss);
	void Reset();
	void HandReturn();

	int action_state_;

	float slap_time_;
	float time_delta_;

	bool is_se_play_;

	SimpleMath::Vector3 pos_;
	SimpleMath::Vector3 rote_;
};