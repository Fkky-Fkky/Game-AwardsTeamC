#pragma once

#include "Classes/Enemy/Boss/Parts/Hands/BossHand.h"

class BossHandL : public BossHand {
public:
	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime);
	void Render();
private:
	DX9::SKINNEDMODEL hand_l_;
	const float INITIAL_POS_X = 13.0f;
};