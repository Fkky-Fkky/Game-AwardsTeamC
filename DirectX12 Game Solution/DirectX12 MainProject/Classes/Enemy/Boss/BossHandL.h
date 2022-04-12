#pragma once

#include "Classes/Enemy/Boss/BossParts.h"

class BossHandL : public BossParts {
public:
	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime);
	void Render();
	void LeftSlap(BossAttack* bossattack);
	void LeftBeat(BossAttack* bossattack);

private:

	BoundingOrientedBox left_hand_obb;
	DX9::MODEL left_hand_obb_model;

	float slap_time;
	float beat_time;
	float time_delta;
	bool hand_return_flag;

	const float INITIAL_POS_X = 10.0f;
	const float SLAP_SPEED = 11.0f;
	const float SLAP_GRAVITY = 23.0f;
	const float BEAT_SPEED = 23.0f;
	const float BEAT_GRAVITY = 80.0f;
	const float HALF = 0.5f;
};