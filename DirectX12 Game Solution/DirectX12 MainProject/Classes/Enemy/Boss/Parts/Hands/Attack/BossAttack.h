#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/Parts/Hands/BossHand.h"

using namespace DirectX;

class BossAttack {
public:
	virtual void Initialize(BossHand* boss_handL, BossHand* bosshandR) {
		boss_handL_ = boss_handL;
		boss_handR_ = bosshandR;
	};
	virtual void Update(const float deltaTime) = 0;

protected:
	BossHand* boss_handL_;
	BossHand* boss_handR_;
};