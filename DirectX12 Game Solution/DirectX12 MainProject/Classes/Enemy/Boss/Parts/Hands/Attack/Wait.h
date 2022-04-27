#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAttack.h"

class Wait : public BossAttack {
public:
	Wait() {
		wait_time = 0.0f;
		max_wait_time = 0.0f;
	}
	virtual void Update(const float deltaTime, SimpleMath::Vector3 player_pos, bool& attack_flag);

private:
	float wait_time;
	float max_wait_time;
};