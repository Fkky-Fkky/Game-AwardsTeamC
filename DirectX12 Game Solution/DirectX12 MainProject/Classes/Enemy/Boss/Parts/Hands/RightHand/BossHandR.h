#pragma once

#include "Classes/Enemy/Boss/Parts/Hands/BossHand.h"

class BossHandR : public BossHand {
public:
	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime);
	void Render();


private:
	const float INITIAL_POS_X = -5.0f;
	const float INITIAL_POS_Y = 5.0f;
};