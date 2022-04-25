#pragma once

#include "Classes/Enemy/Boss/Parts/Hands/BossHand.h"

class BossHandL : public BossHand {
public:
	void Initialize();
	void LoadAssets();
	void Update(const float deltaTime, SimpleMath::Vector3 player_pos);
	void Render();

	void LeftSlap();
	void LeftBeat();

	bool GetAttackFlag() { return attack_flag; }
	BoundingOrientedBox GetLHandCollision() { return collision; }
private:


	float slap_time;
	float beat_time;
	float time_delta;
	float wait_time;
	bool hand_return_flag;
	bool attack_flag;

	const float INITIAL_POS_X = 5.0f;
	const float INITIAL_POS_Y = 5.0f;
	
};