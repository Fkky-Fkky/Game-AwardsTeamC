#pragma once

#include "Classes/Enemy/Boss/BossParts.h"

class BossHandR : public BossParts {
public:
	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime);
	void Render();
	void RightSlap(BossAttack* bossattack);
	void RightBeat(BossAttack* bossattack);

private:

	BoundingOrientedBox right_hand_obb;
	DX9::MODEL right_hand_obb_model;
	
	float slap_time;
	float beat_time;
	float time_delta;
	float wait_time;
	bool hand_return_flag;
	
	const float INITIAL_POS_X = -10.0f;
	const float INITIAL_POS_Y = 5.0f;
	const float SLAP_SPEED = 1.5f;
	const float SLAP_GRAVITY = 5.0f;
	const float BEAT_SPEED = 1.5f;
	const float BEAT_GRAVITY = 5.0f;
	const float HALF = 0.5f;

};