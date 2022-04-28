#pragma once

#include "Classes/Enemy/Boss/Parts/Hands/BossHand.h"

class BossHandL : public BossHand {
public:
	void Initialize();
	void LoadAssets();

private:
	const float INITIAL_POS_X = 13.0f;
};