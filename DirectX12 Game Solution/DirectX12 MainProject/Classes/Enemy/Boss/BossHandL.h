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
	bool GetAttackFlag() { return attack_flag; }
	BoundingOrientedBox GetLHandCollision() { return left_hand_obb; }
private:

	BoundingOrientedBox left_hand_obb;
	DX9::MODEL left_hand_obb_model;

	float slap_time;
	float beat_time;
	float time_delta;
	float wait_time;
	bool hand_return_flag;
	bool attack_flag;

	const float INITIAL_POS_X = 5.0f;
	const float INITIAL_POS_Y = 5.0f;
	const float SLAP_SPEED = 1.5f;
	const float SLAP_GRAVITY = 5.0f;
	const float BEAT_SPEED = 1.5f;
	const float BEAT_GRAVITY = 5.0f;
	const float HALF = 0.5f;
};