#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAttack.h"

using namespace DirectX;

class LeftSlap : public BossAttack {
public:
	LeftSlap() {
		slap_time = 0.0f;
		hand_return_flag = false;
	}
	virtual void Update(const float deltaTime, SimpleMath::Vector3 player_pos, Boss* boss);

private:
	float slap_time;
	bool hand_return_flag;
};