#pragma once

#include "Classes/Enemy/Boss/BossAttack.h"

class BossHandL : public BossAttack {
public:
	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime);
	void Render();
private:
	void LeftSlap();
	void LeftBeat();

	BoundingOrientedBox left_hand_obb;
	DX9::MODEL left_hand_obb_model;

	float slap_time;
	float time_delta;
	bool hand_return_flag;

};