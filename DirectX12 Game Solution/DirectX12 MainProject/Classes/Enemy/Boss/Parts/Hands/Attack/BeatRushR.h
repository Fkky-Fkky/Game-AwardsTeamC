#pragma once

#include "Base/pch.h"
#include "Base/dxtk.h"
#include "Classes/Enemy/Boss/Parts/Hands/Attack/BossAttack.h"

class BeatRushR : public BossAttack {

	virtual void Update(const float deltaTime, SimpleMath::Vector3 player_pos, Boss* boss);

};