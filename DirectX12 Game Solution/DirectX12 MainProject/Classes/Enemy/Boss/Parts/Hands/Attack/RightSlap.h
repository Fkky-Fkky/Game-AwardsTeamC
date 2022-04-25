#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAttack.h"

using namespace DirectX;

class RightSlap : public BossAttack {
public:
	RightSlap() {
		slap_time = 0.0f;
		hand_return_flag = false;
	}
	virtual void Update(const float deltaTime, SimpleMath::Vector3 player_pos);

private:
	float slap_time;
	bool hand_return_flag;
	SimpleMath::Vector3 pos;
	SimpleMath::Vector3 rote;
	const float INITIAL_POS_X = -5.0f;
	const float INITIAL_POS_Y = 5.0f;

};