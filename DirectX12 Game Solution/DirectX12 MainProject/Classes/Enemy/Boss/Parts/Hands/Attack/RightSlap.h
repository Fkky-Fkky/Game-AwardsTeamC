#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAttack.h"

using namespace DirectX;

class RightSlap : public BossAttack {
public:
	RightSlap() {
		slap_time_ = 0.0f;
		hand_return_flag_ = false;
	}
	virtual void Update(const float deltaTime, SimpleMath::Vector3 player_pos, Boss* boss);

private:
	float slap_time_;
	bool hand_return_flag_;
};