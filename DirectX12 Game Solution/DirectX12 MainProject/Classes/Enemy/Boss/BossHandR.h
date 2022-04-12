#pragma once

#include "Classes/Enemy/Boss/BossAttack.h"

class BossHandR : public BossAttack {
public:
	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime);
	void Render();
private:

	void RightSlap();
	void RightBeat();

	BoundingOrientedBox right_hand_obb;
	DX9::MODEL right_hand_obb_model;

};